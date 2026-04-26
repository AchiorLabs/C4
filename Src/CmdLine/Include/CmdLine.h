#ifndef ACHIOR_LABS_CMD_LINE_H
#define ACHIOR_LABS_CMD_LINE_H



struct CmdLineArgument;

#include "../../Main.h"
#include "CmdLineArgumentList.h"


enum CmdLineArgumentType
{
    CMD_LINE_ARGUMENT_FLAG,
    CMD_LINE_ARGUMENT_STRING,
};

union CmdLineArgumentValue
{
    bool flag;
    char *string;
};

struct CmdLineArgument
{
    enum CmdLineArgumentType type;
    char *short_name;
    char *long_name;
    char *description;
    bool is_active;
    union CmdLineArgumentValue value;
};

bool CmdLineArgumentNew(struct CmdLineArgument *self,enum CmdLineArgumentType type,char *short_name,char *long_name,char *description);


struct CmdLineArgumentParser
{
    char *name;
    char *description;
    char *version;
    struct CmdLineArgumentList arguments;
    struct BumpAllocator *bump;
};

bool CmdLineArgumentParserNew(struct CmdLineArgumentParser *self,char *name,char *description,char *version,struct BumpAllocator *bump);

bool CmdLineArgumentParserAddArgument(struct CmdLineArgumentParser *self,struct CmdLineArgument argument);

bool CmdLineArgumentParserParse(struct CmdLineArgumentParser *self,int argc,char **argv);


void CmdLineArgumentParserFatal(struct CmdLineArgumentParser *self,char *str, char * argument_option);

struct CmdLineArgument CmdLineArgumentParserGet(struct CmdLineArgumentParser *self,char *long_name);

#endif
