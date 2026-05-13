#include "Include/Output.h"




bool OutputNew(struct Output *self,struct LinkedList modules,struct C4COptions options,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(bump))
    {
        return false;
    }

    ACHIOR_LABS_WRITE_STRUCT_PTR(self,modules,modules);
    ACHIOR_LABS_WRITE_STRUCT_PTR(self,options,options);
    ACHIOR_LABS_WRITE_STRUCT_PTR(self,bump,bump);

    OutputModules(self);

    return true;
}




bool OutputModules(struct Output *self)
{
    ACHIOR_LABS_STRUCT_INIT(struct C4CTarget,target);

    target = self->options.target;

    ACHIOR_LABS_WRITE_STRUCT_PTR(self,buildFileHandle,ACHIOR_LABS_FOPEN("Makefile","w"));
    
    mkdir("build",0777);
    
    switch(target.arch)
    {
        case C4C_TARGET_ARCH_NONE:
        {
            switch(target.os)
            {
                case C4C_TARGET_OS_NONE:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_LINUX:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_WINDOWS:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_BAREMETAL:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }

            }
            break;
        }
        case C4C_TARGET_ARCH_X86_64:
        {
            switch(target.os)
            {
                case C4C_TARGET_OS_NONE:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_LINUX:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            ACHIOR_LABS_PTR_INIT(char,flags);
                            
                            flags = "CFLAGS = -O0 -I /usr/include -I CFiles";

                            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"%s\n",flags);
                            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"CC = gcc \n");
                            
                            GenerateMakefile(self,self->modules);

                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_WINDOWS:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_BAREMETAL:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            ACHIOR_LABS_PTR_INIT(char,prefix);
                            ACHIOR_LABS_PTR_INIT(char,flags);

                            prefix = "PREFIX = $(HOME)/opt/cross/bin/i686-elf-";
                            flags  = "CFLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Wno-cpp  -nostdlib -nostartfiles -nodefaultlibs -O0 -fno-pic -fno-pie -ffixed-r14  -I $(HOME)/opt/cross/include -I CFiles";

                            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"%s\n\n",prefix);
                            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"%s\n\n",flags);
                            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"CC = $(HOME)/opt/cross/bin/i686-elf-gcc \n");
                            
                            GenerateMakefileBaremetal(self,self->modules);
                            break;
                        }

                    }
                    break;
                }

            }
            break;
        }
        case C4C_TARGET_ARCH_ARM:
        {
            switch(target.os)
            {
                case C4C_TARGET_OS_NONE:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_LINUX:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_WINDOWS:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_BAREMETAL:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }

            }
            break;
        }
        case C4C_TARGET_ARCH_AARCH64:
        {
            switch(target.os)
            {
                case C4C_TARGET_OS_NONE:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_LINUX:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_WINDOWS:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }
                case C4C_TARGET_OS_BAREMETAL:
                {
                    switch(target.assembler)
                    {
                        case C4C_TARGET_ASSEMBLER_NONE:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_NASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GAS:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_MASM:
                        {
                            break;
                        }
                        case C4C_TARGET_ASSEMBLER_GNUC:
                        {
                            break;
                        }

                    }
                    break;
                }

            }
            break;
        }
        
    }

    ACHIOR_LABS_FCLOSE(self->buildFileHandle);
}




bool GenerateMakefileBaremetal(struct Output *self,struct LinkedList modules)
{
    ACHIOR_LABS_VAR_INIT(u64,moduleLength);
    ACHIOR_LABS_PTR_INIT(struct Module,module);
    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,asmFiles);
    ACHIOR_LABS_VAR_INIT(u64,asmFileLength);
    ACHIOR_LABS_PTR_INIT(char,asmFileName);

    moduleLength = ACHIOR_LABS_READ_STRUCT(modules,len);

    // --- object list ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"OBJ = \\\n");

    asmFiles      = self->options.output.asmFiles;
    asmFileLength = asmFiles.len;

    for(u64 i = 0; i < asmFileLength; i++)
    {
        asmFileName = LinkedListAt(&asmFiles,i);

        if(ACHIOR_LABS_ZERO(i))
        {
            continue;   
        }

        ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tbuild/%s.o",asmFileName);
        ACHIOR_LABS_FPRINTF(self->buildFileHandle," \\\n");
    }



    for (u64 i = 0; i < moduleLength; i++)
    {
        module = LinkedListAt(&modules,i);

        ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tbuild/%s/%s.o",ACHIOR_LABS_READ_STRUCT_PTR(module,directory),ACHIOR_LABS_READ_STRUCT_PTR(module,fileName));

        if (ACHIOR_LABS_LESS(i,moduleLength - 1))
        {
            ACHIOR_LABS_FPRINTF(self->buildFileHandle," \\\n");
        }
        else
        {
            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\n");
        }
    }

    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\n");

    // --- targets ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"all: loader1.bin os.bin\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\trm -rf kernel.bin\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tdd if=loader1.bin >> kernel.bin\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tdd if=os.bin >> kernel.bin\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tchmod u+x kernel.bin\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tdd if=/dev/zero bs=512 count=100 >> kernel.bin\n\n\n");

    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"os.bin: $(OBJ)\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t$(PREFIX)ld -g -relocatable $(OBJ) -o build/kernelfull.o\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t$(PREFIX)gcc -T linker.ld -o $@ -ffreestanding -O0 -nostdlib build/kernelfull.o\n\n\n");

    for(u64 i = 0; i < asmFileLength; i++)
    {
        asmFileName = LinkedListAt(&asmFiles,i);

        if(ACHIOR_LABS_ZERO(i))
        {
            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"%s.bin: asm/%s.asm\n",asmFileName,asmFileName);
            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tnasm -f bin $< -o $@\n\n\n");
            continue;
        }

        ACHIOR_LABS_FPRINTF(self->buildFileHandle,"build/%s.o: asm/%s.asm\n",asmFileName,asmFileName);
        ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tnasm -f elf -g $< -o $@\n\n\n");
    }


    

    


    // --- compile rule ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"build/%%.o: CFiles/%%.c\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t@mkdir -p $(dir $@)\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t$(PREFIX)gcc $(CFLAGS) -c $< -o $@\n\n");


    // --- clean ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"clean:\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\trm -rf loader1.bin os.bin CFiles Makefile\n");

    // --- clean all---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"cleanall:\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\trm -rf build app Makefile CFiles\n");
    

    return true;
}







bool GenerateMakefile(struct Output *self,struct LinkedList modules)
{

    ACHIOR_LABS_VAR_INIT(u64,moduleLength);
    ACHIOR_LABS_PTR_INIT(struct Module,module);

    moduleLength = ACHIOR_LABS_READ_STRUCT(modules,len);

    // --- object list ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"OBJ = \\\n");


    
    for (u64 i = 0; i < moduleLength; i++)
    {
        module = LinkedListAt(&modules,i);

        ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\tbuild/%s/%s.o",ACHIOR_LABS_READ_STRUCT_PTR(module,directory),ACHIOR_LABS_READ_STRUCT_PTR(module,fileName));

        if (ACHIOR_LABS_LESS(i,moduleLength - 1))
        {
            ACHIOR_LABS_FPRINTF(self->buildFileHandle," \\\n");
        }
        else
        {
            ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\n");
        }
    }

    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\n");

    // --- targets ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"all: app\n\n");

    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"app: $(OBJ)\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t$(CC) $(CFLAGS) $^ -o $@\n\n");

    // --- compile rule ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"build/%%.o: CFiles/%%.c\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t@mkdir -p $(dir $@)\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\t$(CC) $(CFLAGS) -c $< -o $@\n\n");


    // --- clean ---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"clean:\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\trm -rf Makefile CFiles\n");

    // --- clean all---
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"cleanall:\n");
    ACHIOR_LABS_FPRINTF(self->buildFileHandle,"\trm -rf build app Makefile CFiles\n");



    return true;
}

