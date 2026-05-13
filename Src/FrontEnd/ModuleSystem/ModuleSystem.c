#include "Include/ModuleSystem.h"



bool ModuleNew(struct Module *self,struct String fullPath,struct ASTProgram *ast,struct HashMap imports,struct HashMap symbols)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->fullPath = fullPath;
    self->ast      = ast;
    self->imports  = imports;
    self->symbols  = symbols;

    return true;
}



bool ModuleImportNew(struct ModuleImport *self,struct Token alias,struct String targetPath,struct Module *target)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->alias      = alias;
    self->targetPath = targetPath;
    self->target     = target;

    return true;
}



bool ModuleRegistryNew(struct ModuleRegistry *self,struct HashMap modules)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->modules = modules;

    return true;
}




bool FileTreeNodeNew(struct FileTreeNode *self,enum FileTreeNodeType type,struct String name,struct String fullPath,struct LinkedList children)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->type     = type;
    self->name     = name;
    self->fullPath = fullPath;
    self->children = children;

    return true;
}



bool ModuleSystemNew(struct ModuleSystem *self,struct BumpAllocator *bump,struct C4CFrontEndOptions *options)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->bump    = bump;
    self->options = options;

    ModuleSystemDiscoverFiles(self);


    return true;
}


struct String StringFromCString(struct ModuleSystem *self, const char *text)
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

    const char *lastSlash = strrchr(path, '/');

    /*
    Linux/macOS uses '/'
    Windows may use '\\'
    */

    const char *lastBackslash = strrchr(path, '\\');

    if (lastBackslash != NULL && (lastSlash == NULL || lastBackslash > lastSlash))
    {
        lastSlash = lastBackslash;
    }

    const char *baseName;

    if (lastSlash == NULL)
    {
        baseName = path;
    }
    else
    {
        baseName = lastSlash + 1;
    }

    return StringFromCString(self, baseName);
}


char *JoinPath(struct ModuleSystem *self,const char *parent, const char *child)
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
    ACHIOR_LABS_MEMCPY(result + index, parent, parentLength);
    index += parentLength;

    /* add separator if needed */
    if (needsSlash)
    {
        result[index] = '/';
        index++;
    }

    /* copy child */
    ACHIOR_LABS_MEMCPY(result + index, child, childLength);
    index += childLength;

    /* null terminator */
    result[index] = '\0';

    return result;
}


bool EndsWith(const char *str, const char *suffix)
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

    return strcmp(strSuffix, suffix) == 0;
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
        if (stat(fullPathName, &statBuffer) != 0)
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
    ModuleSystemFileTreeNodePrint(fileTree,0);
    self->registry                = ModuleSystemCreateModuleRegistry(self,fileTree);

    ModuleSystemCollectAllImports(self,fileTree);
    ModuleSystemResolveAllImports(self);
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
        printf("[DIR ]\t%s (%s)\n", node->name.data, node->fullPath.data);
        for(u64 i = 0; i < node->children.len; i++)
        {
            struct FileTreeNode *child = LinkedListAt(&node->children,i);
            ModuleSystemFileTreeNodePrint(child, depth + 1);
        }
    }
    else
    {
        printf("[FILE]\t%s (%s)\n", node->name.data, node->fullPath.data);
    }
}



struct String ModuleSystemFilePathToModulePath(struct ModuleSystem *self,const char *filePath)
{
    struct String pathString = {0};

    if (self == NULL || filePath == NULL)
    {
        return pathString;
    }

    const char *start = filePath;

    if (strncmp(filePath, "src/", 4) == 0)
    {
        start = filePath + 4;
    }

    size_t len = strlen(start);

    if (len >= 3 && strcmp(start + len - 3, ".c4") == 0)
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

    StringNew(&pathString, len + extra + 1, self->bump);

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


struct Module *ModuleSystemCreateModule(struct ModuleSystem *self,const char *filePath)
{
    struct Module *module = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Module,1);
    if(ACHIOR_LABS_NULL(self))
    {
        return module;
    }

    struct String fullPath  = ModuleSystemFilePathToModulePath(self,filePath);
    struct ASTProgram *ast  = ModuleSystemParseFile(self,filePath);
    struct HashMap imports;
    struct HashMap symbols; 


    HashMapNew(&imports,10,self->bump);
    HashMapNew(&symbols,10,self->bump);
    ModuleNew(module,fullPath,ast,imports,symbols);


    return module;
}


char *ReadFileToString(char *file_name,struct BumpAllocator *bump);

struct ASTProgram *ModuleSystemParseFile(struct ModuleSystem *self,char *filePath)
{
    struct C4CFrontEndOptions *options = self->options;
    struct BumpAllocator *bump         = self->bump;

    char *fileSource                   = ReadFileToString(filePath,bump);

    struct Lexer lexer;
	LexerNew(&lexer,filePath,fileSource,bump);



    
	if(ACHIOR_LABS_TRUE(options->emit_tokens))
	{
		char buf[ACHIOR_LABS_STRLEN(filePath) + 10];
		ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%s.%s",filePath,"c4tok");
		
		LexerPrintTokens(&lexer,buf);
	}

	LexerPrintErrors(&lexer);
	
	if(ACHIOR_LABS_TRUE(options->lex_only) || ACHIOR_LABS_TRUE(lexer.has_errors))
	{
		options->lex_only = true;
		return NULL;
	}


	struct Parser parser;
	ParserNew(&parser,filePath,lexer.tokens,bump);

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

    if(ACHIOR_LABS_TRUE(parser.hasErrors))
	{
        puts("--------------------------------- ERROR -------------------------------");
    }
        */

    puts("--------------------------------------------ParseFile done ------------------------------------------------------");
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
        struct String moduleKey = ModuleSystemFilePathToModulePath(self,node->fullPath.data);

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
    HashMapNew(&modules, 64, self->bump);

    ModuleRegistryNew(registry,modules);

    ModuleSystemBuildModulesFromFileTree(self,root,registry);
    return registry;
}



struct String ModuleSystemPathFromList(struct ModuleSystem *self,struct LinkedList list)
{
    struct String path;
    StringNew(&path,10,self->bump);

    for(u64 i = 0; i < list.len; i++)
    {
        char *name = LinkedListAt(&list,i);
        StringPushBack(&path,name);

        if(ACHIOR_LABS_LESS(i,list.len - 1))
        {
            StringPushBack(&path,"::");
        }
    }

    return path;
}





bool ModuleSystemCollectImports(struct ModuleSystem *self,struct Module *module)
{
    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(module->ast))
    {
        return false;
    }


    for(u64 i = 0; i < module->ast->decls.len; i++)
    {
        struct ASTDeclaration *decl = LinkedListAt(&module->ast->decls,i);
        if(ACHIOR_LABS_NOT_EQUAL(decl->type,AST_DECLARATION_USE))
        {
            continue;
        }


        struct ASTUseDecl *useDecl  = (struct ASTUseDecl *)decl->decl;
        struct ModuleImport *import = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleImport,1);
        struct String fullPath      = ModuleSystemPathFromList(self,useDecl->path);

        ModuleImportNew(import,useDecl->alias,fullPath,NULL);

        HashMapAdd(&module->imports,useDecl->alias.value.data,useDecl->alias.value.size,import);
    }
}




bool ModuleSystemCollectAllImports(struct ModuleSystem *self,struct FileTreeNode *fileTree)
{
    struct FileTreeNode *newFileTree = fileTree;

    for(u64 i = 0; i < self->registry->modules.capacity; i++)
    {
        for (struct HashNode *node = self->registry->modules.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct Module *module   = (struct Module *)node->value;
            if(ACHIOR_LABS_NOT_NULL(module))
            {
                //StringPrintln(&module->fullPath);
            }

            ModuleSystemCollectImports(self,module);
        }
    }
}







bool ModuleSystemResolveImports(struct ModuleSystem *self,struct Module *module)
{

    for(u64 i = 0; i < module->imports.capacity; i++)
    {
        for (struct HashNode *node = module->imports.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct ModuleImport *import = (struct ModuleImport *)node->value;
            if(ACHIOR_LABS_NOT_NULL(import))
            {
                //StringPrintln(&module->fullPath);
            }

            struct Module *target = HashMapGet(&self->registry->modules,import->targetPath.data,import->targetPath.size);

            if (target == NULL)
            {
                // error: unknown module
                continue;
            }

            import->target = target;

        }
    }
}




bool ModuleSystemResolveAllImports(struct ModuleSystem *self)
{

    for(u64 i = 0; i < self->registry->modules.capacity; i++)
    {
        for (struct HashNode *node = self->registry->modules.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct Module *module   = (struct Module *)node->value;
            if(ACHIOR_LABS_NOT_NULL(module))
            {
                //StringPrintln(&module->fullPath);
            }

            ModuleSystemResolveImports(self,module);
        }
    }
}



