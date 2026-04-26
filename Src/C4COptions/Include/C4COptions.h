#ifndef ACHIOR_LABS_C4C_OPTIONS_H
#define ACHIOR_LABS_C4C_OPTIONS_H

#include "../../Include/Include.h"



enum C4CEmitType
{
    C4C_EMIT_NONE,
    C4C_EMIT_LIBRARY,
    C4C_EMIT_EXECUTABLE,
};



enum C4CTargetArchitecture
{
    C4C_TARGET_ARCH_NONE,
    C4C_TARGET_ARCH_X86_64,
    C4C_TARGET_ARCH_ARM,
    C4C_TARGET_ARCH_AARCH64,
};

enum C4CTargetOS
{
    C4C_TARGET_OS_NONE,
    C4C_TARGET_OS_LINUX,
    C4C_TARGET_OS_WINDOWS,
    C4C_TARGET_OS_BAREMETAL,
};

enum C4CAssemblySyntax
{
    C4C_ASM_SYNTAX_NONE,
    C4C_ASM_SYNTAX_NASM,
    C4C_ASM_SYNTAX_GAS,
    C4C_ASM_SYNTAX_MASM,
};




struct C4CTarget
{
    enum C4CTargetArchitecture arch;
    enum C4CTargetOS os;
    enum C4CAssemblySyntax asm_syntax;
};


bool C4CTargetNew(struct C4CTarget *self,enum C4CTargetArchitecture arch,enum C4CTargetOS os,enum C4CAssemblySyntax asm_syntax);




struct C4CFrontEndOptions
{
    char *input_file_name;
    char *input_file_source;
    char *output_file_name;
    bool emit_tokens;
    bool emit_ast;
    bool lex_only;
    bool parse_only;
    u64 global_counter;
};


bool C4CFrontEndOptionsNew(struct C4CFrontEndOptions *self,char *input_file_name,char *input_file_source,char *output_file_name,bool emit_tokens,bool emit_ast,bool lex_only,bool parse_only,u64 global_counter);




struct C4COptimization
{
    bool none;
    bool constant_folding;
    bool unreachable_code_elimination;
    bool copy_propagation;
    bool dead_store_elimination;
    bool dead_code_elimination;
};

bool C4COptimizationNew(struct C4COptimization *self,bool none,bool constant_folding,bool unreachable_code_elimination,bool copy_propagation,bool dead_store_elimination,bool dead_code_elimination);

struct C4CMiddleEndOptions
{
    struct C4COptimization optimization;
    bool emit_c;
    bool emit_c4il;
    bool emit_cfg;
    bool verify_c4il;
    u64 global_counter;
    char *output_file_name;
    bool c4il_only;
};

bool C4CMiddleEndOptionsNew(struct C4CMiddleEndOptions *self,struct C4COptimization optimization,bool emit_c,bool emit_c4il,bool emit_cfg,bool verify_c4il,u64 global_counter,char *output_file_name,bool c4il_only);


struct C4CX86Options
{
    bool use_red_zone;
    bool omit_frame_pointer;
    bool position_independent;
};

bool C4CX86OptionsNew(struct C4CX86Options *self,bool use_red_zone,bool omit_frame_pointer,bool position_independent);


struct C4CBackendOptions
{
    bool emit_asm;
    bool compile_only;
    bool assemble_only;
    struct C4CX86Options x86_64;
    u64 global_counter;
    char *output_file_name;
};

bool C4CBackendOptionsNew(struct C4CBackendOptions *self,bool emit_asm,bool compile_only,bool assemble_only,struct C4CX86Options x86_64,u64 global_counter,char *output_file_name);

struct C4COutputOptions
{
    enum C4CEmitType emit_type;
    char *output_file_name;
};

bool C4COutputOptionsNew(struct C4COutputOptions *self,enum C4CEmitType emit_type,char *output_file_name);


struct C4COptions
{
    struct C4CTarget target;
    struct C4CFrontEndOptions frontend;
    struct C4CMiddleEndOptions middleend;
    struct C4CBackendOptions backend;
    struct C4COutputOptions output;
};


bool C4COptionsNew(struct C4COptions *self,struct C4CTarget target,struct C4CFrontEndOptions frontend,struct C4CMiddleEndOptions middleend,struct C4CBackendOptions backend,struct C4COutputOptions output);


struct C4CCompiler
{
    struct C4COptions options;
    struct BumpAllocator *bump;
    char *input_file;
};

bool C4CCompilerNew(struct C4CCompiler *self,struct C4COptions options,struct BumpAllocator *bump,char *input_file);

#endif
