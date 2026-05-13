#include "Include/ModuleSystem.h"
#include "../IdentifierResolution/Include/IdentifierResolution.h"
#include "../TypeChecking/Include/TypeChecking.h"

bool ModuleSystemNew(struct ModuleSystem *self,struct DiagnosticEngine *engine,struct BumpAllocator *bump,struct C4CFrontEndOptions *options)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->bump    = bump;
    self->options = options;
    self->engine  = engine;

    LinkedListNew(&self->order,self->bump);

    ModuleSystemDiscoverFiles(self);


    return true;
}


struct String StringFromCString(struct ModuleSystem *self,const char *text)
{
    struct String string = {0};

    if (self == NULL || text == NULL)
    {
        return string;
    }

    u64 length = ACHIOR_LABS_STRLEN(text);
    StringNew(&string,length + 1,self->bump);
    StringPushBack(&string,text);

    return string;
}


struct String GetBaseName(struct ModuleSystem *self,const char *path)
{
    struct String string = {0};
    if (self == NULL || path == NULL)
    {
        return string;
    }

    const char *lastSlash = strrchr(path,'/');

    
    // Linux/macOS uses '/'
    // Windows may use '\\'

    const char *lastBackslash = strrchr(path,'\\');

    if (lastBackslash != NULL && (lastSlash == NULL || lastBackslash > lastSlash))
    {
        lastSlash = lastBackslash;
    }

    const char *baseName = NULL;

    if (lastSlash == NULL)
    {
        baseName = path;
    }
    else
    {
        baseName = lastSlash + 1;
    }

    return StringFromCString(self,baseName);
}


char *JoinPath(struct ModuleSystem *self,const char *parent,const char *child)
{
    if (parent == NULL || child == NULL)
    {
        return NULL;
    }

    u64 parentLength = ACHIOR_LABS_STRLEN(parent);
    u64 childLength  = ACHIOR_LABS_STRLEN(child);

   

    bool needsSlash = true;

    if (parentLength > 0)
    {
        char last = parent[parentLength - 1];

        if (last == '/' || last == '\\')
        {
            needsSlash = false;
        }
    }

    u64 totalLength = parentLength + childLength + (needsSlash ? 1 : 0) + 1;
    char *result    = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,totalLength);

    if (result == NULL)
    {
        return NULL;
    }

    u64 index = 0;

    /* copy parent */
    ACHIOR_LABS_MEMCPY(result + index,parent,parentLength);
    index += parentLength;

    /* add separator if needed */
    if (needsSlash)
    {
        result[index] = '/';
        index++;
    }

    /* copy child */
    ACHIOR_LABS_MEMCPY(result + index,child,childLength);
    index += childLength;

    /* null terminator */
    result[index] = '\0';

    return result;
}


bool EndsWith(const char *str,const char *suffix)
{
    if (str == NULL || suffix == NULL)
    {
        return false;
    }

    size_t strLen = strlen(str);
    size_t suffixLen = strlen(suffix);

    if (suffixLen > strLen)
    {
        return false;
    }

    const char *strSuffix = str + (strLen - suffixLen);

    return strcmp(strSuffix,suffix) == 0;
}





struct FileTreeNode *ModuleSystemDiscoverDirectory(struct ModuleSystem *self,const char *path)
{
    struct FileTreeNode *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct FileTreeNode,1);

    struct String name     = GetBaseName(self,path);
    struct String fullPath = StringFromCString(self,path);
    struct LinkedList children;
    LinkedListNew(&children,self->bump);

    FileTreeNodeNew(node,FILE_TREE_NODE_DIRECTORY,name,fullPath,children);


    DIR *directoryFd      = opendir(path);

    if (ACHIOR_LABS_NULL(directoryFd))
    {
        return node;
    }

    struct dirent *dirent = NULL;

    while(true)
    {
        dirent = readdir(directoryFd);
        if(ACHIOR_LABS_NULL(dirent))
        {
            break;
        }

        if (dirent->d_name[0] == '.')
        {
            continue;
        }
        

        char *fullPathName = JoinPath(self,path,dirent->d_name);

        struct stat statBuffer;
        if (stat(fullPathName,&statBuffer) != 0)
        {
            continue;
        }

        if(S_ISDIR(statBuffer.st_mode))
        {
            struct FileTreeNode *child = ModuleSystemDiscoverDirectory(self,fullPathName);
            LinkedListPushBack(&node->children,child);
        }
        else if(EndsWith(dirent->d_name,".c4"))
        {
            struct String name     = StringFromCString(self,dirent->d_name);
            struct String fullPath = StringFromCString(self,fullPathName);
            struct LinkedList children;
            LinkedListNew(&children,self->bump);

            struct FileTreeNode *child = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct FileTreeNode,1);
            FileTreeNodeNew(child,FILE_TREE_NODE_FILE,name,fullPath,children);
            LinkedListPushBack(&node->children,child);
        }

    }

    closedir(directoryFd);

    return node;
}





void ModuleSystemDiscoverFiles(struct ModuleSystem *self)
{
    struct FileTreeNode *fileTree = ModuleSystemDiscoverDirectory(self,"src");
    //ModuleSystemFileTreeNodePrint(fileTree,0);
    self->registry                = ModuleSystemCreateModuleRegistry(self,fileTree);

    ModuleSystemCollectAllImports(self,fileTree);
    ModuleSystemResolveAllImports(self);

    if (!ModuleSystemBuildTopologicalOrder(self))
    {
        printf("Compilation aborted due to import cycle.\n");
        return;
    }

    //ModuleSystemPrintModules(self);
    ModuleSystemRegisterAllSymbols(self);
    ModuleSystemResolveSymbolAllIdentifiers(self);

    ModuleSystemTypeCheckAll(self);
}




void ModuleSystemFileTreeNodePrint(struct FileTreeNode *node,int depth)
{
    if (node == NULL)
    {
        return;
    }

    /* indentation */
    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }

    if(ACHIOR_LABS_EQUAL(depth,1))
    {
        printf("\t");
    }
    else if(ACHIOR_LABS_GREATER(depth,0))
    {
        printf("\t");
    }

    /* print node name */
    if (node->type == FILE_TREE_NODE_DIRECTORY)
    {
        printf("[DIR ]\t%s (%s)\n",node->name.data,node->fullPath.data);
        for(u64 i = 0; i < node->children.len; i++)
        {
            struct FileTreeNode *child = LinkedListAt(&node->children,i);
            ModuleSystemFileTreeNodePrint(child,depth + 1);
        }
    }
    else
    {
        printf("[FILE]\t%s (%s)\n",node->name.data,node->fullPath.data);
    }
}



struct String ModuleSystemFilePathToModulePath(struct BumpAllocator *bump,const char *filePath)
{
    struct String pathString = {0};

    if (bump == NULL || filePath == NULL)
    {
        return pathString;
    }

    const char *start = filePath;

    if (strncmp(filePath,"src/",4) == 0)
    {
        start = filePath + 4;
    }

    size_t len = strlen(start);

    if (len >= 3 && strcmp(start + len - 3,".c4") == 0)
    {
        len -= 3;
    }

    /* count extra chars needed for :: */
    size_t extra = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (start[i] == '/' || start[i] == '\\')
        {
            extra++;
        }
    }

    StringNew(&pathString,len + extra + 1,bump);

    size_t j = 0;
    for (size_t i = 0; i < len; i++)
    {
        char c = start[i];

        if (c == '/' || c == '\\')
        {
            pathString.data[j++] = ':';
            pathString.data[j++] = ':';
        }
        else
        {
            pathString.data[j++] = c;
        }
    }

    pathString.data[j] = '\0';
    pathString.size = j;

    return pathString;
}


bool ModuleSystemSplitPath(struct BumpAllocator *bump,const char *path,char **directory,char **fileName)
{

    const char *lastSlash = strrchr(path,'/');

    if (lastSlash)
    {
        u64 directoryLength = (u64)(lastSlash - path);
        *directory          = ACHIOR_LABS_ARENA_ALLOC(bump,char,directoryLength + 1);

        ACHIOR_LABS_STRNCPY(*directory,path,directoryLength);
        (*directory)[directoryLength] = '\0';

        u64 fileNameLength  = ACHIOR_LABS_STRLEN(lastSlash + 1);
        *fileName           = ACHIOR_LABS_ARENA_ALLOC(bump,char,fileNameLength + 1);


        ACHIOR_LABS_STRNCPY(*fileName,lastSlash + 1,fileNameLength);
        (*fileName)[fileNameLength] = '\0';
    }
    else
    {
        *directory = NULL;

        u64 fileNameLength  = ACHIOR_LABS_STRLEN(path);
        *fileName           = ACHIOR_LABS_ARENA_ALLOC(bump,char,fileNameLength + 1);

        ACHIOR_LABS_STRNCPY(*fileName,path,fileNameLength);
        (*fileName)[fileNameLength] = '\0';
    }


    u64 length = ACHIOR_LABS_STRLEN(*fileName);

    char *dot = strrchr(*fileName,'.');
    if (dot && ACHIOR_LABS_STRCMP(dot,".c4") == 0)
    {
        *dot = '\0';
    }

    return true;
}

struct Module *ModuleSystemCreateModule(struct ModuleSystem *self,const char *filePath)
{
    struct Module *module = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Module,1);
    if(ACHIOR_LABS_NULL(self))
    {
        return module;
    }

    ACHIOR_LABS_PTR_INIT(char,fileSource);

    struct String fullPath  = ModuleSystemFilePathToModulePath(self->bump,filePath);
    struct ASTProgram *ast  = ModuleSystemParseFile(self,filePath,fullPath.data,&fileSource);
    char *workingDirectory  = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,256);
    char *directory         = NULL;
    char *fileName          = NULL;
    struct HashMap imports;
    struct HashMap symbols;

    getcwd(workingDirectory,256);
    ModuleSystemSplitPath(self->bump,filePath,&directory,&fileName);


    HashMapNew(&imports,10,self->bump);
    HashMapNew(&symbols,10,self->bump);
    ModuleNew(module,fullPath,ast,workingDirectory,directory,fileName,imports,symbols);

    module->moduleName   = (char *)filePath;
    module->moduleSource = fileSource;
    module->sourceLength = ACHIOR_LABS_STRLEN(fileSource);

    return module;
}


char *ReadFileToString(char *file_name,struct BumpAllocator *bump);

struct ASTProgram *ModuleSystemParseFile(struct ModuleSystem *self,const char *filePath,char *fullPath,char **fileSource)
{
    struct C4CFrontEndOptions *options = self->options;
    struct BumpAllocator *bump         = self->bump;

    *fileSource                   = ReadFileToString((char *)filePath,bump);

    struct Lexer lexer;
	LexerNew(&lexer,(char *)filePath,*fileSource,self->engine,bump);



    
	if(ACHIOR_LABS_TRUE(options->emit_tokens))
	{
		char buf[ACHIOR_LABS_STRLEN(filePath) + 10];
		ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%s.%s",filePath,"c4tok");
		
		LexerPrintTokens(&lexer,buf);
	}

	
	if(ACHIOR_LABS_TRUE(options->lex_only) || ACHIOR_LABS_TRUE(lexer.hasErrors))
	{
		options->lex_only = true;
		return NULL;
	}


	struct Parser parser;
	ParserNew(&parser,(char *)filePath,lexer.fileSource,lexer.tokens,self->engine,bump);

    /*
    if(ACHIOR_LABS_TRUE(options->emit_ast))
	{
		char buf[ACHIOR_LABS_STRLEN(filePath) + 10];
		ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%s.%s",filePath,"c4ast");

		struct ASTPrint astPrint;
		ASTPrintNew(&astPrint,parser.astProgram,buf);
		ASTPrintProgram(&astPrint,parser.astProgram);


		//struct TreeWalker treeWalker;
		//TreeWalkerNew(&treeWalker,parser.astProgram,buf);
		//TreeWalkerProgram(&treeWalker,parser.astProgram);
	}
    */


    if(ACHIOR_LABS_TRUE(parser.hasErrors))
	{
        puts("--------------------------------- ERROR -------------------------------");
    }

    struct IdentifierResolution resolver;
	IdentifierResolutionNew(&resolver,fullPath,parser.fileSource,parser.astProgram,options->global_counter,self->engine,bump);

	options->global_counter = resolver.globalCounter;

    


    //puts("--------------------------------------------ParseFile done ------------------------------------------------------");
    return parser.astProgram;
}





void ModuleSystemBuildModulesFromFileTree(struct ModuleSystem *self,struct FileTreeNode *node,struct ModuleRegistry *registry)
{
    if (self == NULL || node == NULL || registry == NULL)
    {
        return;
    }

    /* FILE → create module */
    if (node->type == FILE_TREE_NODE_FILE)
    {
        struct Module *module   = ModuleSystemCreateModule(self,node->fullPath.data);
        struct String moduleKey = ModuleSystemFilePathToModulePath(self->bump,node->fullPath.data);

        HashMapAdd(&registry->modules,moduleKey.data,moduleKey.size,module);

        return;
    }


    for(u64 i = 0; i < node->children.len; i++)
    {
        struct FileTreeNode *child = LinkedListAt(&node->children,i);
        ModuleSystemBuildModulesFromFileTree(self,child,registry);
    }

}



struct ModuleRegistry *ModuleSystemCreateModuleRegistry(struct ModuleSystem *self,struct FileTreeNode *root)
{
    struct ModuleRegistry *registry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleRegistry,1);

    struct HashMap modules;
    HashMapNew(&modules,64,self->bump);

    ModuleRegistryNew(registry,modules);

    ModuleSystemBuildModulesFromFileTree(self,root,registry);
    return registry;
}


