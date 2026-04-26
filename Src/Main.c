#include "Main.h"




char *ReadFileToString(char *file_name,struct BumpAllocator *bump)
{
    FILE *fin = ACHIOR_LABS_FOPEN(file_name, "rb");
    
    if( ACHIOR_LABS_NULL(fin))
    {
        ACHIOR_LABS_PERROR("fopen failed ");
	    return NULL;
    }

    ACHIOR_LABS_FSEEK(fin, 0, SEEK_END);
    i64 size = ACHIOR_LABS_FTELL(fin);
    ACHIOR_LABS_FSEEK(fin,0,SEEK_SET);

    char *file_source = ACHIOR_LABS_ARENA_ALLOC(bump,char,size + 1);
    if ( ACHIOR_LABS_NULL(file_source))
    {
        ACHIOR_LABS_RETURN_DEFER(defer);
    }

    ACHIOR_LABS_FREAD(file_source, 1, size, fin);
    file_source[size] = '\0';

defer:
    ACHIOR_LABS_FCLOSE(fin);
    return file_source;
}





struct CmdLineArgumentParser MainSetUpCmdLineArguments(int argc,char **argv,struct BumpAllocator *bump)
{
    struct CmdLineArgumentParser parser;
    CmdLineArgumentParserNew(&parser,"c4c","c4c compiler toolchain","0.0.0 [alpha]",bump);



    struct CmdLineArgument argument;
    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_STRING,"i","input","Input C4 source file");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_STRING,"t","target","Target backend ((x86_64-linux-nasm, x86_64-windows-msvc, etc)");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_STRING,"o","output","Output file name");
    CmdLineArgumentParserAddArgument(&parser,argument);





    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"emit-asm","Emit assembly");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"emit-c4il","Emit C4 IL");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"emit-c","Emit C Code");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"emit-ast","Emit AST");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"emit-tokens","Emit tokens");
    CmdLineArgumentParserAddArgument(&parser,argument);






    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"lex-only","Only do lexical analysis");
    CmdLineArgumentParserAddArgument(&parser,argument);

    

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"parse-only","Only do syntax analysis");
    CmdLineArgumentParserAddArgument(&parser,argument);

    


    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"c-only","Only do generate the c code");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"c4il-only","Only do generate the c4il IR");
    CmdLineArgumentParserAddArgument(&parser,argument);


    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"verify-c4il","Verify C4 IL");
    CmdLineArgumentParserAddArgument(&parser,argument);

    
    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"compile-only","Only do generate the assembly");
    CmdLineArgumentParserAddArgument(&parser,argument);


    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"assemble-only","Only do assemble generated assembly");
    CmdLineArgumentParserAddArgument(&parser,argument);

    
    
    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"fomit-frame-pointer","Omit frame pointer");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"fno-red-zone","Disable red zone");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"fPIC","Position independent code");
    CmdLineArgumentParserAddArgument(&parser,argument);



    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"library","produce a library");
    CmdLineArgumentParserAddArgument(&parser,argument);


    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,NULL,"executable","produce an executable");
    CmdLineArgumentParserAddArgument(&parser,argument);


    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,"h","help","Display this help Message");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentNew(&argument,CMD_LINE_ARGUMENT_FLAG,"v","version","Show the Compiler version");
    CmdLineArgumentParserAddArgument(&parser,argument);

    CmdLineArgumentParserParse(&parser,argc,argv);


    return parser;
}





char *MainGetDesription(struct CmdLineArgumentParser *self,char *long_name)
{
    struct CmdLineArgument argument = CmdLineArgumentParserGet(self,long_name);
    return argument.is_active ? argument.description : NULL;
}

char *MainGetValueString(struct CmdLineArgumentParser *self,char *long_name)
{
    struct CmdLineArgument argument = CmdLineArgumentParserGet(self,long_name);
    return argument.is_active ? argument.value.string : NULL;
}



bool MainGetValueFlag(struct CmdLineArgumentParser *self,char *long_name)
{
    struct CmdLineArgument argument = CmdLineArgumentParserGet(self,long_name);
    return argument.is_active ? argument.value.flag : false;
}






struct C4CCompiler MainSetUpC4COptions(struct CmdLineArgumentParser *parser,struct BumpAllocator *bump)
{
    char *input_file_name = NULL;
    input_file_name = MainGetValueString(parser,"input");
    if(ACHIOR_LABS_NULL(input_file_name))
    {
        MainFatal("no input file given : must provide an input file",bump);
    }

    char *input_file_source = ReadFileToString(input_file_name,bump);

    char *output_file_name = NULL;
    output_file_name = MainGetValueString(parser,"output");
    if(ACHIOR_LABS_NULL(output_file_name))
    {
        MainFatal("no output file given : must provide an output file",bump);
    }

    bool emit_tokens = MainGetValueFlag(parser,"emit-tokens");
    bool emit_ast    = MainGetValueFlag(parser,"emit-ast");
    bool lex_only    = MainGetValueFlag(parser,"lex-only");
    bool parse_only  = MainGetValueFlag(parser,"parse-only");


    
    struct C4CFrontEndOptions frontend_options;
    C4CFrontEndOptionsNew(&frontend_options,input_file_name,input_file_source,output_file_name,emit_tokens,emit_ast,lex_only,parse_only,0);

    bool none                         = true; //MainGetValueFlag(parser,"");;
    bool constant_folding             = false; //MainGetValueFlag(parser,"");;
    bool unreachable_code_elimination = false; //MainGetValueFlag(parser,"");
    bool copy_propagation             = false; //MainGetValueFlag(parser,"");;
    bool dead_store_elimination       = false; //MainGetValueFlag(parser,"");;
    bool dead_code_elimination        = false; //MainGetValueFlag(parser,"");;


    struct C4COptimization C4COptimization;
    C4COptimizationNew(&C4COptimization,none,constant_folding,unreachable_code_elimination,copy_propagation,dead_store_elimination,dead_code_elimination);


    bool emit_c      = MainGetValueFlag(parser,"emit-c");
    bool emit_c4il   = MainGetValueFlag(parser,"emit-c4il");
    bool emit_cfg    = false; //MainGetValueFlag(parser,"");;
    bool verify_c4il = false; //MainGetValueFlag(parser,"");;
    bool c4il_only   = MainGetValueFlag(parser,"c4il-only");

    struct C4CMiddleEndOptions middleend_options;
    C4CMiddleEndOptionsNew(&middleend_options,C4COptimization,emit_c,emit_c4il,emit_cfg,verify_c4il,0,output_file_name,c4il_only);


    bool emit_asm          = MainGetValueFlag(parser,"emit-asm");
    bool compile_only      = MainGetValueFlag(parser,"compile-only");
    bool assemble_only     = MainGetValueFlag(parser,"assemble-only");
    struct C4CX86Options x86_64_options;

    struct C4CBackendOptions backend_options;
    C4CBackendOptionsNew(&backend_options,emit_asm,compile_only,assemble_only,x86_64_options,0,output_file_name);


    bool library          = MainGetValueString(parser,"library");

    bool executable       = MainGetValueString(parser,"executable");

    if(ACHIOR_LABS_TRUE(library) && ACHIOR_LABS_TRUE(executable))
    {
        MainFatal("cannot produce an executable and a library at the same time",bump);
    }


    enum C4CEmitType emit_type = C4C_EMIT_NONE;
    

    if(ACHIOR_LABS_TRUE(library))
    {
        backend_options.emit_asm = true;
        emit_type = C4C_EMIT_LIBRARY;
    }
    else if(ACHIOR_LABS_TRUE(executable))
    { 
        backend_options.emit_asm = true;
        emit_type = C4C_EMIT_EXECUTABLE;
    }

    
    struct C4COutputOptions output_options;
    C4COutputOptionsNew(&output_options,emit_type,output_file_name);

    struct C4CTarget C4CTarget;

    struct C4COptions C4COptions;
    C4COptionsNew(&C4COptions,C4CTarget,frontend_options,middleend_options,backend_options,output_options);


    struct C4CCompiler C4CCompiler;
    C4CCompilerNew(&C4CCompiler,C4COptions,bump,input_file_name);

    return C4CCompiler;
}







static void MainPrintSpaces(int count)
{
    for(int i = 0; i < count; i++)
    {
        putchar(' ');
    }
}

static int MainFormatOption(char *buffer, size_t size, struct CmdLineArgument *arg)
{
    int written = 0;

    if(arg->short_name)
    {
        written += ACHIOR_LABS_SNPRINTF(buffer + written, size - written, "-%s", arg->short_name);

        if(arg->long_name)
            written += ACHIOR_LABS_SNPRINTF(buffer + written, size - written, ", ");
    }

    if(arg->long_name)
    {
        written += ACHIOR_LABS_SNPRINTF(buffer + written, size - written, "--%s", arg->long_name);
    }

    if(arg->type == CMD_LINE_ARGUMENT_STRING)
    {
        written += ACHIOR_LABS_SNPRINTF(buffer + written, size - written, " <%s>",
                            arg->long_name ? arg->long_name : "value");
    }

    return written;
}



void MainPrintHelp(struct CmdLineArgumentParser *parser)
{
    ACHIOR_LABS_PRINTF("c4c version 0.0.0\n");
    ACHIOR_LABS_PRINTF("%s\n\n", parser->description);

    ACHIOR_LABS_PRINTF("USAGE\n");
    ACHIOR_LABS_PRINTF("    %s [OPTIONS] <input>\n\n", parser->name);

    ACHIOR_LABS_PRINTF("DESCRIPTION\n");
    ACHIOR_LABS_PRINTF("    %s\n\n", "Compiles C4 source files into target-specific binaries.");

    ACHIOR_LABS_PRINTF("OPTIONS\n");

    // First pass: compute max width
    int max_width = 0;
    for(int i = 0; i < parser->arguments.size; i++)
    {
        char buffer[256];
        int len = MainFormatOption(buffer, sizeof(buffer), &parser->arguments.data[i]);
        if(len > max_width) max_width = len;
    }

    // Second pass: print aligned
    for(int i = 0; i < parser->arguments.size; i++)
    {
        struct CmdLineArgument *arg = &parser->arguments.data[i];

        char buffer[256];
        int len = MainFormatOption(buffer, sizeof(buffer), arg);

        ACHIOR_LABS_PRINTF("    %s", buffer);
        MainPrintSpaces(max_width - len + 4); // padding
        ACHIOR_LABS_PRINTF("%s\n", arg->description);
    }

    ACHIOR_LABS_PRINTF("\nEXAMPLES\n\n");

    ACHIOR_LABS_PRINTF("    Compile using long flags:\n");
    ACHIOR_LABS_PRINTF("        c4c --input main.c4 --output main --target x86_64-linux-nasm\n\n");

    ACHIOR_LABS_PRINTF("    Compile using short flags:\n");
    ACHIOR_LABS_PRINTF("        c4c -i main.c4 -o main -t x86_64-windows-mingw\n\n");

    ACHIOR_LABS_PRINTF("REPORTING BUGS\n");
    ACHIOR_LABS_PRINTF("    https://github.com/c4-lang/c4/issues\n");
}



void MainPrintVersion(struct CmdLineArgumentParser *parser)
{
    if(ACHIOR_LABS_NULL(parser))
    {
        return;
    }

    ACHIOR_LABS_PRINTF("%s version %s\n", parser->name,parser->version);
}




int main(int argc,char **argv)
{
    int status = 0;
    struct BumpAllocator bump;
    BumpAllocatorNew(&bump,10000000);
 
    
    struct CmdLineArgumentParser parser = MainSetUpCmdLineArguments(argc,argv,&bump);
    

    bool help    = MainGetValueFlag(&parser,"help");
	bool version = MainGetValueFlag(&parser,"version");
	

	if(help == true || argc == 1)
	{
		MainPrintHelp(&parser);
		status = 0;
        ACHIOR_LABS_RETURN_DEFER(end);
	}
	else if(version == true)
	{
		MainPrintVersion(&parser);
		status = 0;
        ACHIOR_LABS_RETURN_DEFER(end);
	}


    struct C4CCompiler C4CCompiler = MainSetUpC4COptions(&parser,&bump);
    if(ACHIOR_LABS_NULL(C4CCompiler.options.frontend.input_file_source))
    {
        status = -1;
        ACHIOR_LABS_RETURN_DEFER(end);
    }
    
    DriverRun(&C4CCompiler);
    puts("compiler success");

end:
    BumpAllocatorFree(&bump);
    return status;
}



void MainFatal(char *str,struct BumpAllocator *bump)
{
    log_error("%s\n %C{bold_red}compilation terminated%C{reset}",str);
    BumpAllocatorFree(bump);
    exit(2);
}
