
#include "Include/C4COptions.h"



bool C4CTargetNew(struct C4CTarget *self,enum C4CTargetArchitecture arch,enum C4CTargetOS os,enum C4CTargetAssembler assembler)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->arch      = arch;
    self->os        = os;
    self->assembler = assembler;

    return true;
}



bool C4CFrontEndOptionsNew(struct C4CFrontEndOptions *self,char *input_file_name,char *input_file_source,char *output_file_name,bool emit_tokens,bool emit_ast,bool lex_only,bool parse_only,u64 global_counter)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->input_file_name   = input_file_name;
    self->input_file_source = input_file_source;
    self->output_file_name  = output_file_name;
    self->emit_tokens       = emit_tokens;
    self->emit_ast          = emit_ast;
    self->lex_only          = lex_only;
    self->parse_only        = parse_only;
    self->global_counter    = global_counter;

    return true;
}



bool C4COptimizationNew(struct C4COptimization *self,bool none,bool constant_folding,bool unreachable_code_elimination,bool copy_propagation,bool dead_store_elimination,bool dead_code_elimination)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->none                               = none;
    self->constant_folding                   = constant_folding;
    self->unreachable_code_elimination       = unreachable_code_elimination;
    self->copy_propagation                   = copy_propagation;
    self->dead_store_elimination             = dead_store_elimination;
    self->dead_code_elimination              = dead_code_elimination;

    return true;
}


bool C4CMiddleEndOptionsNew(struct C4CMiddleEndOptions *self,struct C4COptimization optimization,bool emit_c,bool emit_c4il,bool emit_cfg,bool verify_c4il,u64 global_counter,char *output_file_name,bool c4il_only)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->optimization        = optimization;
    self->emit_c              = emit_c;
    self->emit_c4il           = emit_c4il;
    self->emit_cfg            = emit_cfg;
    self->verify_c4il         = verify_c4il;
    self->global_counter      = global_counter;
    self->output_file_name    = output_file_name;
    self->c4il_only           = c4il_only;

    return true;
}



bool C4CX86OptionsNew(struct C4CX86Options *self,bool use_red_zone,bool omit_frame_pointer,bool position_independent)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->use_red_zone         = use_red_zone;
    self->omit_frame_pointer   = omit_frame_pointer;
    self->position_independent = position_independent;

    return true;
}


bool C4CBackendOptionsNew(struct C4CBackendOptions *self,bool emit_asm,bool compile_only,bool assemble_only,struct C4CX86Options x86_64,u64 global_counter,char *output_file_name)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->emit_asm          = emit_asm;
    self->compile_only      = compile_only;
    self->assemble_only     = assemble_only;
    self->x86_64            = x86_64;
    self->global_counter    = global_counter;
    self->output_file_name  = output_file_name;

    return true;
}
bool C4COutputOptionsNew(struct C4COutputOptions *self,enum C4CEmitType emit_type,char *output_file_name)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->emit_type        = emit_type;
    self->output_file_name = output_file_name;

    return true;
}




bool C4COptionsNew(struct C4COptions *self,struct C4CTarget target,struct C4CFrontEndOptions frontend,struct C4CMiddleEndOptions middleend,struct C4CBackendOptions backend,struct C4COutputOptions output)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->target    = target;
    self->frontend  = frontend;
    self->middleend = middleend;
    self->backend   = backend;
    self->output    = output;
}


bool C4CCompilerNew(struct C4CCompiler *self,struct C4COptions options,struct BumpAllocator *bump,char *input_file)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->options       = options;
    self->bump          = bump;
    self->input_file    = input_file;

    return true;
}
