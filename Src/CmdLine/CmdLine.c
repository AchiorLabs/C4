#include "Include/CmdLine.h"


bool CmdLineArgumentNew(struct CmdLineArgument *self,enum CmdLineArgumentKind kind,char *shortName,char *longName,char *description)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->kind        = kind;
    self->shortName   = shortName;
    self->longName    = longName;
    self->description = description;
    self->isActive    = false;
    

    return true;
}



bool CmdLineArgumentParserNew(struct CmdLineArgumentParser *self,char *name,char *description,char *version,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->name        = name;
    self->description = description;
    self->version     = version;
    self->bump        = bump;

    LinkedListNew(&self->arguments,self->bump);

    return true;;
}

bool CmdLineArgumentParserAddArgument(struct CmdLineArgumentParser *self,struct CmdLineArgument *argument)
{
    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(argument))
    {
        return false;
    }

    LinkedListPushBack(&self->arguments,argument);

    return true;
}



struct CmdLineArgument *CmdLineArgumentParserGet(struct CmdLineArgumentParser *self,char *longName)
{
    ACHIOR_LABS_PTR_INIT(struct CmdLineArgument,argument);
    ACHIOR_LABS_VAR_INIT(u64,argumentLength);

    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(longName))
    {
        ACHIOR_LABS_RETURN_DEFER(failure);
    }


    argumentLength = self->arguments.len;

    for(u64 i = 0; i < argumentLength; i++)
    {
        argument = LinkedListAt(&self->arguments,i);

        if(ACHIOR_LABS_STRCMP(argument->longName,longName) == 0)
        {
            return argument;
        }
    }

failure:
    return NULL;
}

bool CmdLineArgumentParserParse(struct CmdLineArgumentParser *self,int argc,char **argv)
{
    ACHIOR_LABS_VAR_INIT(u64,argumentLength);
    ACHIOR_LABS_PTR_INIT(struct CmdLineArgument,argument);
    ACHIOR_LABS_PTR_INIT(char,arg);


    for(int i = 1; i < argc; i++)
    {
        arg = argv[i];

        if(arg[0] == '-')
        {
            if(ACHIOR_LABS_STRLEN(arg) > 1 && arg[1] == '-')
            {
                arg += 2;
                argumentLength = self->arguments.len;

                for(u64 j = 0; j < argumentLength; j++)
                {
                    argument = LinkedListAt(&self->arguments,j);

                    if(ACHIOR_LABS_STRCMP(argument->longName,arg) == 0)
                    {
                        switch(argument->kind)
                        {
                            case CMD_LINE_ARGUMENT_FLAG:
                            {
                                argument->isActive  = true;
                                argument->value.flag = true;
                                break;
                            }
                            case CMD_LINE_ARGUMENT_STRING:
                            {
                                if(i + 1 >= argc || argv[i+1][0] == '-')
                                {
                                    // expected an argument after a value option
                                    CmdLineArgumentParserFatal(self,"expected an argument after a value option --%s",arg);
                                }

                                argument->isActive    = true;
                                argument->value.string = argv[++i];
                                break;
                            }
                            case CMD_LINE_ARGUMENT_LIST:
                            {
                                if(i + 1 >= argc || argv[i][0] == '-')
                                {
                                    //CmdLineArgumentParserFatal(self,"expected list after --%s",arg);
                                }

                                argument->isActive = true;

                                CmdLineSplitComma(&argument->value.list,argv[i + 1],self->bump);

                                for(u64 i = 0; i < argument->value.list.len; i++)
                                {
                                    char *tmp = LinkedListAt(&argument->value.list,i);
                                }

                                i++; // consume value
                                break;
                            }
                            default:
                            {
                                CmdLineArgumentParserFatal(self,"unsupported argument kind",NULL);
                            }
                        }
                    }
                }
            }
            else
            {
                arg += 1;
                argumentLength = self->arguments.len;

                for(u64 j = 0; j < argumentLength; j++)
                {
                    argument = LinkedListAt(&self->arguments,j);

                    if(ACHIOR_LABS_NOT_NULL(argument->shortName) && ACHIOR_LABS_STRCMP(argument->shortName,arg) == 0)
                    {
                        switch(argument->kind)
                        {
                            case CMD_LINE_ARGUMENT_FLAG:
                            {
                                argument->isActive  = true;
                                argument->value.flag = true;
                                break;
                            }
                            case CMD_LINE_ARGUMENT_STRING:
                            {
                                if(i + 1 >= argc || argv[i+1][0] == '-')// Catches missing arguments even when in between arguments
                                {
                                    // expected an argument after a value option
                                    //Prints the string with missing arguments
                                    CmdLineArgumentParserFatal(self,"expected an argument after a value option -%s \n",arg);
                                }

                                argument->isActive     = true;
                                argument->value.string = argv[++i];
                                break;
                            }
                            case CMD_LINE_ARGUMENT_LIST:
                            {
                                if(i + 1 >= argc || argv[i][0] == '-')
                                {
                                    CmdLineArgumentParserFatal(self,"expected list after -%s",arg);
                                }

                                argument->isActive = true;

                                CmdLineSplitComma(&argument->value.list,argv[i + 1],self->bump);

                                i++;
                                break;
                            }
                            default:
                            {
                                CmdLineArgumentParserFatal(self,"unsupported argument kind %s\n",NULL);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            //We are sussposed to set the help flag so as to show usage
            argument             = LinkedListAt(&self->arguments,0);
            argument->isActive   = true;
            argument->value.flag = true;
        }
    }
}




void CmdLineSplitComma(struct LinkedList *out, char *input, struct BumpAllocator *bump)
{
    char *start = input;

    for(char *p = input; ; p++)
    {
        if(*p == ',' || *p == '\0')
        {
            u64 len = p - start;

            char *token = ACHIOR_LABS_ARENA_ALLOC(bump, char, len + 1);

            for(u64 i = 0; i < len; i++)
                token[i] = start[i];

            token[len] = '\0';

            LinkedListPushBack(out, token);

            if(*p == '\0')
                break;

            start = p + 1;
        }
    }
}


void CmdLineArgumentParserFatal(struct CmdLineArgumentParser *self,char *str,char *option)
{
    ACHIOR_LABS_PRINTF(str,option);
    exit(1);
}






struct CmdLineArgument *C4MakeCmdLineArgument(struct BumpAllocator *bump,enum CmdLineArgumentKind kind,char *shortName,char *longName,char *description)
{
    if(ACHIOR_LABS_NULL(bump))
    {
        return NULL;
    }

    struct CmdLineArgument *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct CmdLineArgument,1);
    CmdLineArgumentNew(node,kind,shortName,longName,description);

    LinkedListNew(&node->value.list,bump);

    return node;
}