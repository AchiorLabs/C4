#include "Include/CmdLine.h"


bool CmdLineArgumentNew(struct CmdLineArgument *self,enum CmdLineArgumentType type,char *short_name,char *long_name,char *description)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->type           = type;
    self->short_name     = short_name;
    self->long_name      = long_name;
    self->description    = description;
    self->is_active      = false;

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

    CmdLineArgumentListNew(&self->arguments,10,self->bump);

    return true;;
}

bool CmdLineArgumentParserAddArgument(struct CmdLineArgumentParser *self,struct CmdLineArgument argument)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    CmdLineArgumentListPushBack(&self->arguments,argument);

    return true;
}



struct CmdLineArgument CmdLineArgumentParserGet(struct CmdLineArgumentParser *self,char *long_name)
{
    if(ACHIOR_LABS_NULL(self))
    {
        ACHIOR_LABS_RETURN_DEFER(failure);
    }

    for(u64 i = 0; i < self->arguments.size; i++)
    {
        if(ACHIOR_LABS_STRCMP(self->arguments.data[i].long_name,long_name) == 0)
        {
            return self->arguments.data[i];
        }
    }

failure:
    return (struct CmdLineArgument){};
}

bool CmdLineArgumentParserParse(struct CmdLineArgumentParser *self,int argc,char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        char *arg = argv[i];

        if(arg[0] == '-')
        {
            if(ACHIOR_LABS_STRLEN(arg) > 1 && arg[1] == '-')
            {
                arg += 2;
                for(u64 j = 0; j < self->arguments.size; j++)
                {
                    struct CmdLineArgument argument = self->arguments.data[j];

                    if(ACHIOR_LABS_STRCMP(argument.long_name,arg) == 0)
                    {
                        switch(argument.type)
                        {
                            case CMD_LINE_ARGUMENT_FLAG:
                            {
                                self->arguments.data[j].is_active  = true;
                                self->arguments.data[j].value.flag = true;
                                break;
                            }
                            case CMD_LINE_ARGUMENT_STRING:
                            {
                                if(i + 1 >= argc || argv[i+1][0] == '-')
                                {
                                    // expected an argument after a value option
                                    CmdLineArgumentParserFatal(self,"expected an argument after a value option --%s", arg);
                                }

                                self->arguments.data[j].is_active    = true;
                                self->arguments.data[j].value.string = argv[++i];
                                break;
                            }
                            default:
                            {
                                CmdLineArgumentParserFatal(self,"unsupported argument type", NULL);
                            }
                        }
                    }
                }
            }
            else
            {
                arg += 1;
                for(u64 j = 0; j < self->arguments.size; j++)
                {
                    struct CmdLineArgument argument = self->arguments.data[j];

                    if(ACHIOR_LABS_NOT_NULL(argument.short_name) && ACHIOR_LABS_STRCMP(argument.short_name,arg) == 0)
                    {
                        switch(argument.type)
                        {
                            case CMD_LINE_ARGUMENT_FLAG:
                            {
                                self->arguments.data[j].is_active  = true;
                                self->arguments.data[j].value.flag = true;
                                break;
                            }
                            case CMD_LINE_ARGUMENT_STRING:
                            {
                                if(i + 1 >= argc || argv[i+1][0] == '-')// Catches missing arguments even when in between arguments
                                {
                                    // expected an argument after a value option
                                    //Prints the string with missing arguments
                                    CmdLineArgumentParserFatal(self,"expected an argument after a value option -%s \n", arg);
                                }

                                self->arguments.data[j].is_active  = true;
                                self->arguments.data[j].value.string = argv[++i];
                                break;
                            }
                            default:
                            {
                                CmdLineArgumentParserFatal(self,"unsupported argument type %s\n", NULL);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            //We are sussposed to set the help flag so as to show usage
            self->arguments.data[0].is_active = true;
            self->arguments.data[0].value.flag = true;
        }
    }
}







void CmdLineArgumentParserFatal(struct CmdLineArgumentParser *self,char *str, char *argument_option)
{
    ACHIOR_LABS_PRINTF(str, argument_option);
    exit(1);
}
