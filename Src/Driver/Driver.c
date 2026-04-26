#include "Include/Driver.h"



bool DriverRun(struct C4CCompiler *c4c)
{
	struct Parser parser = FrontEndDriverRun(&c4c->options.frontend,c4c->bump);

	if(ACHIOR_LABS_TRUE(c4c->options.frontend.lex_only) || ACHIOR_LABS_TRUE(c4c->options.frontend.parse_only))
	{
		return true;
	}

	struct ASTProgram *program = parser.astProgram;
	MiddleEndDriverRun(&c4c->options.middleend,program,c4c->bump);

	return true;
}

