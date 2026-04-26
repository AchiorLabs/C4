#include "Include/Driver.h"



void MiddleEndDriverRun(struct C4CMiddleEndOptions *options,struct ASTProgram *program,struct BumpAllocator *bump)
{
	if(ACHIOR_LABS_TRUE(options->emit_c))
	{
		char buf[ACHIOR_LABS_STRLEN(options->output_file_name) + 7];
		ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%s.%s",options->output_file_name,"c");

		struct ASTToC C;
		ASTToCNew(&C,program,buf,bump);
	}
}