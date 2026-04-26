#include "Include/Driver.h"




struct Parser FrontEndDriverRun(struct C4CFrontEndOptions *options,struct BumpAllocator *bump)
{
    struct Lexer lexer;
	LexerNew(&lexer,options->input_file_name,options->input_file_source,bump);



	if(ACHIOR_LABS_TRUE(options->emit_tokens))
	{
		char buf[ACHIOR_LABS_STRLEN(options->output_file_name) + 7];
		ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%s.%s",options->output_file_name,"c4tok");
		
		LexerPrintTokens(&lexer,buf);
	}

	LexerPrintErrors(&lexer);
	
	if(ACHIOR_LABS_TRUE(options->lex_only) || ACHIOR_LABS_TRUE(lexer.has_errors))
	{
		options->lex_only = true;
		return (struct Parser){};
	}


	struct Parser parser;
	ParserNew(&parser,options->input_file_name,lexer.tokens,bump);
	

	if(ACHIOR_LABS_TRUE(options->emit_ast))
	{
		char buf[ACHIOR_LABS_STRLEN(options->output_file_name) + 7];
		ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%s.%s",options->output_file_name,"c4ast");

		struct ASTPrint astPrint;
		ASTPrintNew(&astPrint,parser.astProgram,buf);
		ASTPrintProgram(&astPrint,parser.astProgram);


		//struct TreeWalker treeWalker;
		//TreeWalkerNew(&treeWalker,parser.astProgram,buf);
		//TreeWalkerProgram(&treeWalker,parser.astProgram);
	}


	if(ACHIOR_LABS_TRUE(options->parse_only) || ACHIOR_LABS_TRUE(parser.hasErrors))
	{
		options->parse_only = true;
		return parser;
	}

	return parser;
}
