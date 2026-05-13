#include "Include/Driver.h"



bool DriverRun(struct C4CCompiler *c4c)
{
	ACHIOR_LABS_STRUCT_INIT(struct DiagnosticEngine,engine);
	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,modules);
	ACHIOR_LABS_STRUCT_INIT(struct Output,output);

	DiagnosticEngineNew(&engine,100,c4c->bump);

	modules = FrontEndDriverRun(&c4c->options.frontend,&engine,c4c->bump);

	if(ACHIOR_LABS_TRUE(c4c->options.frontend.lex_only) || ACHIOR_LABS_TRUE(c4c->options.frontend.parse_only))
	{
		return true;
	}


	if(ACHIOR_LABS_TRUE(engine.hasErrors))
	{
		DiagnosticEngineEmit(&engine);
		return false;
	}

	MiddleEndDriverRun(&c4c->options.middleend,modules,c4c->bump);


	OutputNew(&output,modules,c4c->options,c4c->bump);

	return true;
}

