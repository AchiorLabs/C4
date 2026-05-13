#ifndef ACHIOR_LABS_CMD_LINE_H
#define ACHIOR_LABS_CMD_LINE_H


#include "../../Support/Include/Types.h"
#include "../../Support/Include/Utils.h"
#include "../../Support/Include/BumpAllocator.h"
#include "../../Support/Include/String.h"
#include "../../Support/Include/List.h"
#include "../../Support/Include/Log.h"


enum CmdLineArgumentKind
{
    CMD_LINE_ARGUMENT_FLAG,
    CMD_LINE_ARGUMENT_STRING,
    CMD_LINE_ARGUMENT_LIST,
};

union CmdLineArgumentValue
{
    bool flag;
    char *string;
    struct LinkedList list;
};

struct CmdLineArgument
{
    enum CmdLineArgumentKind kind;
    char *shortName;
    char *longName;
    char *description;
    bool isActive;
    union CmdLineArgumentValue value;
};

bool CmdLineArgumentNew(struct CmdLineArgument *self,enum CmdLineArgumentKind kind,char *shortName,char *longName,char *description);

struct CmdLineArgument *C4MakeCmdLineArgument(struct BumpAllocator *bump,enum CmdLineArgumentKind kind,char *shortName,char *longName,char *description);

struct CmdLineArgumentParser
{
    char *name;
    char *description;
    char *version;
    struct LinkedList arguments;
    struct BumpAllocator *bump;
};

bool CmdLineArgumentParserNew(struct CmdLineArgumentParser *self,char *name,char *description,char *version,struct BumpAllocator *bump);

bool CmdLineArgumentParserAddArgument(struct CmdLineArgumentParser *self,struct CmdLineArgument *argument);

bool CmdLineArgumentParserParse(struct CmdLineArgumentParser *self,int argc,char **argv);


void CmdLineSplitComma(struct LinkedList *out, char *input, struct BumpAllocator *bump);

void CmdLineArgumentParserFatal(struct CmdLineArgumentParser *self,char *str, char *option);

struct CmdLineArgument *CmdLineArgumentParserGet(struct CmdLineArgumentParser *self,char *longName);

#endif
