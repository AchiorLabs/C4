#include "Include/ASTToC.h"

void MakeDirectoryRecursive(const char *path)
{
    ACHIOR_LABS_ARRAY_INIT(char,tmp,1024);
    ACHIOR_LABS_SNPRINTF(tmp,ACHIOR_LABS_SIZEOF(tmp),"%s",path);

    for (char *p = tmp + 1; *p; p++)
    {
        if (*p == '/')
        {
            *p = '\0';
            mkdir(tmp, 0777);
            *p = '/';
        }
    }

    mkdir(tmp, 0777);
}


bool ASTToCNew(struct ASTToC *self,struct LinkedList modules,char *fileName,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->modules = modules;
    self->bump    = bump;

    if(ACHIOR_LABS_NULL(self->cFileHandle))
    {
        return false;
    }


    //puts("============== C TRANSPILER =========================");

    mkdir("CFiles",0777);

    ACHIOR_LABS_VAR_INIT(u64,moduleLength);
    ACHIOR_LABS_PTR_INIT(struct Module,module);
    ACHIOR_LABS_VAR_INIT(u64,size);

    moduleLength = ACHIOR_LABS_READ_STRUCT(modules,len);


    for(u64 i = 0; i < modules.len; i++)
    {
        module = LinkedListAt(&modules,i);
        size   = module->fullPath.size + 100;

        char directory[size];
        ACHIOR_LABS_MEMSET(directory,0,size);
        ACHIOR_LABS_SNPRINTF(directory,size,"CFiles/%s",module->directory);

        MakeDirectoryRecursive(directory);

        ACHIOR_LABS_PTR_INIT(char,cFileName);
        ACHIOR_LABS_PTR_INIT(char,hFileName);

        cFileName = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,size);

        ACHIOR_LABS_MEMSET(cFileName,0,size);
        ACHIOR_LABS_SNPRINTF(cFileName,size,"%s/%s.c",directory,module->fileName);

        
        hFileName = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,size);
        
        ACHIOR_LABS_MEMSET(hFileName,0,size);
        ACHIOR_LABS_SNPRINTF(hFileName,size,"%s/%s.h",directory,module->fileName);

        self->cFileHandle = ACHIOR_LABS_FOPEN(cFileName,"w");
        self->hFileHandle = ACHIOR_LABS_FOPEN(hFileName,"w");


        if(ACHIOR_LABS_NULL(self->cFileHandle) || ACHIOR_LABS_NULL(self->hFileHandle))
        {
            continue;
        }

        ACHIOR_LABS_SNPRINTF(cFileName,size,"%s.c",module->fileName);
        ACHIOR_LABS_SNPRINTF(hFileName,size,"%s.h",module->fileName);

        self->cFileName = cFileName;
        self->hFileName = hFileName;


        ACHIOR_LABS_FPRINTF(self->hFileHandle,"#ifndef %s_h\n",module->fileName);
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"#define %s_h\n",module->fileName);
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"#include <AchiorLabs/C4/Types.h>\n#include \"%s/%s\"\n\n",module->directory,self->hFileName);
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"#include <AchiorLabs/C4/Types.h>\n\n");

        ASTToCProgram(self,module->ast);

        ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n#endif\n");
    }

    
    //puts("============== C TRANSPILER Complete =========================");

    return true;
}


void ASTToCProgram(struct ASTToC *self,struct ASTProgram *program)
{
    if( ACHIOR_LABS_NULL(program))
    {
        return;
    }
    
    ACHIOR_LABS_VAR_INIT(u64,declarationLength);

    declarationLength = program->decls.len;
    
    for(u64 i = 0; i < declarationLength; i++)
    {
		ASTToCDecl(self,LinkedListAt(&program->decls,i));
	}

    ACHIOR_LABS_FCLOSE(self->cFileHandle);

}


void ASTToCDecl(struct ASTToC *self,struct ASTDeclaration *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


	switch(ASTDECLARATION_GET_KIND(*decl))
	{
		case AST_DECLARATION_USE:
		{
			ASTToCUseDecl(self,ASTDECLARATION_GET_DECL(*decl));
			break;
		}
		case AST_DECLARATION_ENUM:
		{
			ASTToCEnumDecl(self,ASTDECLARATION_GET_DECL(*decl));
			break;
		}
		case AST_DECLARATION_STRUCT:
		{
			ASTToCStructDecl(self,ASTDECLARATION_GET_DECL(*decl),true);
			break;
		}
		case AST_DECLARATION_UNION:
		{
			ASTToCStructDecl(self,ASTDECLARATION_GET_DECL(*decl),false);
			break;
		}
		case AST_DECLARATION_IMPL:
		{
			ASTToCImplDecl(self,ASTDECLARATION_GET_DECL(*decl));
			break;
		}
		case AST_DECLARATION_SUM:
		{
			ASTToCSumDecl(self,ASTDECLARATION_GET_DECL(*decl));
			break;
		}
		case AST_DECLARATION_FUNCTION:
		{
			ASTToCFunctionDecl(self,ASTDECLARATION_GET_DECL(*decl));
			break;
		}
		case AST_DECLARATION_VARIABLE:
		{
			ASTToCVariableDecl(self,ASTDECLARATION_GET_DECL(*decl));
			break;
		}
		default:
		{
			break;
		}
	}

}


void ASTToCIdentifier(struct ASTToC *self,struct Token *ident,bool cFile)
{
    if(ACHIOR_LABS_TRUE(cFile))
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"%s",TOKEN_GET_VALUE_DATA(*ident));
    }
    else
    {
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"%s",TOKEN_GET_VALUE_DATA(*ident));
    }
}




void ASTToCVariableDecl(struct ASTToC *self,struct ASTVariableDecl *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);
    ACHIOR_LABS_VAR_INIT(u64,arrayBufferLength);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,size);
    
    LinkedListNew(&arrayBuffer,self->bump);

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"extern ");

    if(ACHIOR_LABS_TRUE(stmt->isConstant))
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"const ");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"const ");
    }


    ASTToCType(self,stmt->type,&arrayBuffer,true);
    ASTToCType(self,stmt->type,&arrayBuffer,false);

    ASTToCIdentifier(self,stmt->ident,true);
    ASTToCIdentifier(self,stmt->ident,false);


    arrayBufferLength = arrayBuffer.len;

    for(u64 i = 0; i < arrayBufferLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"[");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"[");

        size = LinkedListAt(&arrayBuffer,i);

        ASTToCExpression(self,size,true);
        ASTToCExpression(self,size,false);

        ACHIOR_LABS_FPRINTF(self->cFileHandle,"]");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"]");
    }


    if(ACHIOR_LABS_NOT_NULL(stmt->init))
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle," = ");
        //ACHIOR_LABS_FPRINTF(self->hFileHandle," = ");

        ASTToCVariableDeclInit(self,stmt->init,true);
        //ASTToCVariableDeclInit(self,stmt->init,false);
    }

    ACHIOR_LABS_FPRINTF(self->cFileHandle,";\n");
    ACHIOR_LABS_FPRINTF(self->hFileHandle,";\n");
}




void ASTToCUseDecl(struct ASTToC *self,struct ASTUseDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct Module,module);

    module = decl->import->target;

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"#include  \"%s/%s.h\"\n",module->directory,module->fileName);
}




void ASTToCEnumDecl(struct ASTToC *self,struct ASTEnumDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    ACHIOR_LABS_VAR_INIT(u64,constantLength);
    ACHIOR_LABS_PTR_INIT(struct ASTEnumConstant,constant);

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\nenum ");
    ASTToCIdentifier(self,decl->ident,false);
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n{");

    constantLength = decl->constants.len;

    for(u64 i = 0; i < constantLength; i++)
    {
        constant = LinkedListAt(&decl->constants,i);
        ASTToCEnumConstant(self,constant);
    }

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n};\n");
}







void ASTToCEnumConstant(struct ASTToC *self,struct ASTEnumConstant  *constant)
{
    if( ACHIOR_LABS_NULL(constant))
    {
        return;
    }

    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);


    LinkedListNew(&arrayBuffer,self->bump);

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\t");
    ASTToCIdentifier(self,constant->constant,false);
    
    if(ACHIOR_LABS_NOT_NULL(constant->expr))
    {
        ACHIOR_LABS_FPRINTF(self->hFileHandle," = ");
        ASTToCExpression(self,constant->expr,false);
    }

    ACHIOR_LABS_FPRINTF(self->hFileHandle,",");
}






void ASTToCStructDecl(struct ASTToC *self,struct ASTStructDecl *decl,bool isStruct)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    ACHIOR_LABS_VAR_INIT(u64,propertyLength);
    ACHIOR_LABS_PTR_INIT(struct ASTStructProperty,property);


    if(ACHIOR_LABS_TRUE(isStruct))
    {
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"\nstruct ");
    }
    else
    {
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"\nunion ");
    }

    
    ASTToCIdentifier(self,decl->ident,false);
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n{");


    propertyLength = decl->properties.len;

    for(u64 i = 0; i < propertyLength; i++)
    {
        property = LinkedListAt(&decl->properties,i);
        ASTToCStructProperty(self,property);
    }

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n};\n");

}



void ASTToCStructProperty(struct ASTToC *self,struct ASTStructProperty *property)
{
    if( ACHIOR_LABS_NULL(property))
    {
        return;
    }

    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);
    ACHIOR_LABS_VAR_INIT(u64,arrayBufferLength);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,size);

    LinkedListNew(&arrayBuffer,self->bump);

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\t");

    ASTToCType(self,property->type,&arrayBuffer,false);
    ASTToCIdentifier(self,property->ident,false);


    arrayBufferLength = arrayBuffer.len;

    for(u64 i = 0; i < arrayBufferLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"[");

        size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size,false);

        ACHIOR_LABS_FPRINTF(self->hFileHandle,"]");
    }

    ACHIOR_LABS_FPRINTF(self->hFileHandle,";");
}




void ASTToCImplDecl(struct ASTToC *self,struct ASTImplDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    ACHIOR_LABS_VAR_INIT(u64,methodLength);
    ACHIOR_LABS_PTR_INIT(struct ASTFunctionDecl,method);

    methodLength = decl->methods.len;

    
    for(u64 i = 0; i < methodLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n");

        method = LinkedListAt(&decl->methods,i);
        ASTToCFunctionDecl(self,method);

        ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n");
    }
}






void ASTToCSumDecl(struct ASTToC *self,struct ASTSumDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    ASTToCSumEnum(self,TOKEN_GET_VALUE_DATA(*(decl->ident)),decl->variants);
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\nstruct ");
    
    ASTToCIdentifier(self,decl->ident,false);

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n{");
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\tenum %sTag tag;\n",TOKEN_GET_VALUE_DATA(*(decl->ident)));

    ASTToCSumVariants(self,decl->variants);

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n};\n");

}


char *ASTToCCapitalizeString(struct ASTToC *self,char *source)
{
    ACHIOR_LABS_VAR_INIT(u64,length);
    ACHIOR_LABS_PTR_INIT(char,destination);

    length      = ACHIOR_LABS_STRLEN(source);
    destination = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,length + 1); 

    for(u64 i = 0; i < length; i++)
    {
        destination[i] = ACHIOR_LABS_TOUPPER(source[i]);
    }

    destination[length] = '\0';

    return destination;
}


void ASTToCSumEnum(struct ASTToC *self,char *ident,struct LinkedList variants)
{
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\nenum %sTag\n{\n",ident);

    ACHIOR_LABS_VAR_INIT(u64,variantLength);
    ACHIOR_LABS_PTR_INIT(struct ASTSumVariant,variant);

    variantLength = variants.len;

    for(u64 i = 0; i < variantLength; i++)
    {
        variant = LinkedListAt(&variants,i);

        ACHIOR_LABS_FPRINTF(self->hFileHandle,"\t%s_TAG_%s,\n",ASTToCCapitalizeString(self,ident),ASTToCCapitalizeString(self,TOKEN_GET_VALUE_DATA(*(variant->ident))));
        break;
    }

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"};\n");
}




void ASTToCSumVariants(struct ASTToC *self,struct LinkedList variants)
{
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\tunion\n\t{");

    ACHIOR_LABS_VAR_INIT(u64,variantLength);
    ACHIOR_LABS_PTR_INIT(struct ASTSumVariant,variant);
    ACHIOR_LABS_PTR_INIT(struct ASTType,type);
    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);

    variantLength = variants.len;

    for(u64 i = 0; i < variantLength; i++)
    {
        variant = LinkedListAt(&variants,i);

        switch(variant->kind)
        {
            case AST_SUM_VARIANT_UNIT:
            {
                type = LinkedListAt(&variant->fields,0);
                
                ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\t\t");
                ASTToCType(self,type,&arrayBuffer,false);

                ACHIOR_LABS_FPRINTF(self->hFileHandle," ");
                ASTToCIdentifier(self,variant->ident,false);
                
                ACHIOR_LABS_FPRINTF(self->hFileHandle,";");
                break;
            }
            case AST_SUM_VARIANT_TUPLE:
            {
                ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\n\t\tstruct\n\t\t{");

                ACHIOR_LABS_VAR_INIT(u64,variantFieldLength);

                variantFieldLength = variant->fields.len;

                for(u64 i = 0; i < variantFieldLength; i++)
                {
                    type = LinkedListAt(&variant->fields,i);
                
                    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\t\t\t");
                    ASTToCType(self,type,&arrayBuffer,false);

                    ACHIOR_LABS_FPRINTF(self->hFileHandle," field%lu;",i);
                }

                ACHIOR_LABS_FPRINTF(self->hFileHandle,"\t\t\n\t\t}%s;",TOKEN_GET_VALUE_DATA(*(variant->ident)));
                break;
            }
            case AST_SUM_VARIANT_STRUCT:
            {
                break;
            }
        }
    }

    ACHIOR_LABS_FPRINTF(self->hFileHandle,"\n\t}data;");
}





void ASTToCFunctionDecl(struct ASTToC *self,struct ASTFunctionDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    
    if(ACHIOR_LABS_NOT_NULL(decl->attributes) && ACHIOR_LABS_TRUE(decl->attributes->isStatic))
    {
        
    }
	

    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);
    ACHIOR_LABS_VAR_INIT(u64,arrayBufferLength);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,size);
    
    LinkedListNew(&arrayBuffer,self->bump);

    ASTToCType(self,decl->returnType,&arrayBuffer,true);
    ASTToCType(self,decl->returnType,&arrayBuffer,false);

    ACHIOR_LABS_FPRINTF(self->cFileHandle," ");
    ACHIOR_LABS_FPRINTF(self->hFileHandle," ");

    ASTToCIdentifier(self,decl->ident,true);
    ASTToCIdentifier(self,decl->ident,false);


    arrayBufferLength = arrayBuffer.len;

    for(u64 i = 0; i < arrayBufferLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"[");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"[");


        size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size,true);
        ASTToCExpression(self,size,false);

        
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"]");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"]");
    }


    ACHIOR_LABS_FPRINTF(self->cFileHandle,"(");
    ACHIOR_LABS_FPRINTF(self->hFileHandle,"(");

    for(u64 i = 0; i < decl->arguments.len; i++)
    {
        ASTToCFunctionArgument(self,LinkedListAt(&decl->arguments,i));

        if(ACHIOR_LABS_LESS(i,decl->arguments.len - 1))
        {
            ACHIOR_LABS_FPRINTF(self->cFileHandle,",");
            ACHIOR_LABS_FPRINTF(self->hFileHandle,",");
        }
    }

    if(ACHIOR_LABS_TRUE(decl->hasVariableArguments))
    {
        if(ACHIOR_LABS_GREATER(decl->arguments.len,0))
        {
            ACHIOR_LABS_FPRINTF(self->cFileHandle,",...");
            ACHIOR_LABS_FPRINTF(self->hFileHandle,",...");
        }
        else
        {
            ACHIOR_LABS_FPRINTF(self->cFileHandle,"...");
            ACHIOR_LABS_FPRINTF(self->hFileHandle,"...");   
        }
    }

    ACHIOR_LABS_FPRINTF(self->cFileHandle,")");
    ACHIOR_LABS_FPRINTF(self->hFileHandle,");\n\n");

    if(ACHIOR_LABS_NOT_NULL(decl->block))
    {
        ASTToCBlockStmt(self,decl->block,"");
    }
    else
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,";\n\n");
    }
    
}



void ASTToCFunctionArgument(struct ASTToC *self,struct ASTFunctionArgument *argument)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }

    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);
    ACHIOR_LABS_VAR_INIT(u64,arrayBufferLength);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,size);
    
    LinkedListNew(&arrayBuffer,self->bump);

    ASTToCType(self,argument->type,&arrayBuffer,true);
    ASTToCType(self,argument->type,&arrayBuffer,false);

    ASTToCIdentifier(self,argument->ident,true);
    ASTToCIdentifier(self,argument->ident,false);


    arrayBufferLength = arrayBuffer.len;

    for(u64 i = 0; i < arrayBufferLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"[");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"[");

        size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size,true);
        ASTToCExpression(self,size,false);

        ACHIOR_LABS_FPRINTF(self->cFileHandle,"]");
        ACHIOR_LABS_FPRINTF(self->hFileHandle,"]");
    }
}



void ASTToCType(struct ASTToC *self,struct ASTType *type,struct LinkedList *arrayBuffer,bool cFile)
{
    if( ACHIOR_LABS_NULL(type))
    {
        return;
    }


    ACHIOR_LABS_PTR_INIT(FILE,handle);

    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    switch(type->dataType)
    {
        case AST_DATA_TYPE_VOID:
        {
            ACHIOR_LABS_FPRINTF(handle,"void ");
            break;
        }
        case AST_DATA_TYPE_CHAR:
        {
            ACHIOR_LABS_FPRINTF(handle,"char ");
            break;
        }
        case AST_DATA_TYPE_I8:
        {
            ACHIOR_LABS_FPRINTF(handle,"i8 ");
            break;
        }
        case AST_DATA_TYPE_I16:
        {
            ACHIOR_LABS_FPRINTF(handle,"i16 ");
            break;
        }
        case AST_DATA_TYPE_I32:
        {
            ACHIOR_LABS_FPRINTF(handle,"i32 ");
            break;
        }
        case AST_DATA_TYPE_I64:
        {
            ACHIOR_LABS_FPRINTF(handle,"i64 ");
            break;
        }
        case AST_DATA_TYPE_ISIZE:
        {
            ACHIOR_LABS_FPRINTF(handle,"size_t ");
            break;
        }
        case AST_DATA_TYPE_U8:
        {
            ACHIOR_LABS_FPRINTF(handle,"u8 ");
            break;
        }
        case AST_DATA_TYPE_U16:
        {
            ACHIOR_LABS_FPRINTF(handle,"u16 ");
            break;
        }
        case AST_DATA_TYPE_U32:
        {
            ACHIOR_LABS_FPRINTF(handle,"u32 ");
            break;
        }
        case AST_DATA_TYPE_U64:
        {
            ACHIOR_LABS_FPRINTF(handle,"u64 ");
            break;
        }
        case AST_DATA_TYPE_USIZE:
        {
            ACHIOR_LABS_FPRINTF(handle,"ssize_t ");
            break;
        }
        case AST_DATA_TYPE_STRING:
        {
            ACHIOR_LABS_FPRINTF(handle,"char *");
            break;
        }
        case AST_DATA_TYPE_POINTER:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTPointerType,pointerType);
            pointerType = type->type;

            ASTToCType(self,pointerType->type,arrayBuffer,cFile);
            ACHIOR_LABS_FPRINTF(handle,"*");
            break;
        }
        case AST_DATA_TYPE_ARRAY:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTArrayType,arrayType);
            arrayType = type->type;

            LinkedListPushBack(arrayBuffer,arrayType->size);
            ASTToCType(self,arrayType->type,arrayBuffer,cFile);
            break;
        }
        case AST_DATA_TYPE_ENUM:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTStructType,structType);
            structType = type->type;

            ACHIOR_LABS_FPRINTF(handle,"enum ");
            ASTToCIdentifier(self,structType->ident,cFile);

            ACHIOR_LABS_FPRINTF(handle," ");
            break;
        }
        case AST_DATA_TYPE_STRUCT:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTStructType,structType);
            structType = type->type;

            ACHIOR_LABS_FPRINTF(handle,"struct ");
            ASTToCIdentifier(self,structType->ident,cFile);

            ACHIOR_LABS_FPRINTF(handle," ");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(handle,"%d [type] - ",type->dataType);
            ACHIOR_LABS_FPRINTF(handle,"unknown-type");
        }
    }	    
}

void ASTToCBlockStmt(struct ASTToC *self,struct ASTBlockStmt *block,char *tab)
{
    ACHIOR_LABS_VAR_INIT(u64,stmtLength);
    char newTab[ACHIOR_LABS_STRLEN(tab) + 2];
    ACHIOR_LABS_SNPRINTF(newTab,ACHIOR_LABS_STRLEN(tab) + 2,"%s\t",tab);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n%s{",tab);
    

    stmtLength = block->stmts.len;

    for(u64 i = 0; i < stmtLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n%s\t",tab);
        ASTToCStmt(self,LinkedListAt(&block->stmts,i),newTab);
    }

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n%s}\n",tab);
}


void ASTToCStmt(struct ASTToC *self,struct ASTStatement *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

	switch(ASTSTATEMENT_GET_KIND(*stmt))
	{
		case AST_STATEMENT_RETURN:
		{
            ASTToCReturnStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_LOOP:
		{
            ASTToCLoopStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_WHILE:
		{
            ASTToCWhileStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_BREAK:
		{
            ASTToCBreakStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_CONTINUE:
		{
            ASTToCContinueStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_IF:
		{
            ASTToCIfStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_VAR_DECL:
		{
            ASTToCVariableDeclStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_EXPRESSION:
		{
            ASTToCExpressionStmt(self,stmt->stmt,tab);
			break;
		}
		default:
		{
			break;
		}
	}

}





void ASTToCExpressionStmt(struct ASTToC *self,struct ASTExpression *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ASTToCExpression(self,stmt,true);
    ACHIOR_LABS_FPRINTF(self->cFileHandle,";");
}



void ASTToCVariableDeclStmt(struct ASTToC *self,struct ASTVariableDecl *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arrayBuffer);
    ACHIOR_LABS_VAR_INIT(u64,arrayBufferLength);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,size);
    
    LinkedListNew(&arrayBuffer,self->bump);

    if(ACHIOR_LABS_TRUE(stmt->isConstant))
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"const ");
    }


    ASTToCType(self,stmt->type,&arrayBuffer,true);
    ASTToCIdentifier(self,stmt->ident,true);


    arrayBufferLength = arrayBuffer.len;

    for(u64 i = 0; i < arrayBufferLength; i++)
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"[");
        size = LinkedListAt(&arrayBuffer,i);

        ASTToCExpression(self,size,true);
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"]");
    }


    if(ACHIOR_LABS_NOT_NULL(stmt->init))
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle," = ");
        ASTToCVariableDeclInit(self,stmt->init,true);
    }

    ACHIOR_LABS_FPRINTF(self->cFileHandle,";");
}



void ASTToCVariableDeclInit(struct ASTToC *self,struct ASTVariableDeclInit *init,bool cFile)
{
    if( ACHIOR_LABS_NULL(init))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    switch(ASTVARIABLEDECLINIT_GET_INITKIND(*init))
    {
        case AST_VAR_DECL_INIT_SINGLE_INIT:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclSingleInit,singleInit);
            singleInit = init->init;

            ASTToCExpression(self,singleInit->expr,cFile);
            break;
        }
        case AST_VAR_DECL_INIT_ARRAY_INIT:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclArrayInit,arrayInit);
            ACHIOR_LABS_VAR_INIT(u64,elementLength);
            ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclInit,tmpInit);

            arrayInit     = init->init;
            elementLength = arrayInit->elements.len;

            ACHIOR_LABS_FPRINTF(self->cFileHandle,"{");

            for(u64 i = 0; i < elementLength; i++)
            {
                tmpInit = LinkedListAt(&arrayInit->elements,i);
                ASTToCVariableDeclInit(self,tmpInit,cFile);

                if(ACHIOR_LABS_LESS(i,elementLength - 1))
                {
                    ACHIOR_LABS_FPRINTF(handle,",");
                }
            }

            ACHIOR_LABS_FPRINTF(handle,"}");

            break;
        }
    }

}



void ASTToCIfStmt(struct ASTToC *self,struct ASTIfStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ACHIOR_LABS_VAR_INIT(u64,elifLength);
    ACHIOR_LABS_PTR_INIT(struct ASTIfElif,Elif);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"if(");
    ASTToCExpression(self,stmt->expr,true);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,")");
    ASTToCBlockStmt(self,stmt->block,tab);


    elifLength = stmt->elifs.len;

    for(u64 i = 0; i < elifLength; i++)
    {
        Elif = LinkedListAt(&stmt->elifs,i);
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"%selse if(",tab);

        ASTToCExpression(self,Elif->expr,true);
        ACHIOR_LABS_FPRINTF(self->cFileHandle,")");
        
        ASTToCBlockStmt(self,Elif->block,tab);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->elseBlock))
    {
        ACHIOR_LABS_FPRINTF(self->cFileHandle,"%selse",tab);
        ASTToCBlockStmt(self,stmt->elseBlock->block,tab);
    }

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n");
}


void ASTToCContinueStmt(struct ASTToC *self,struct ASTContinueStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->cFileHandle,"continue;");
}



void ASTToCBreakStmt(struct ASTToC *self,struct ASTBreakStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->cFileHandle,"break;");
}


void ASTToCWhileStmt(struct ASTToC *self,struct ASTWhileStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->cFileHandle,"while(");
    ASTToCExpression(self,stmt->expr,true);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,")");
    ASTToCBlockStmt(self,stmt->block,tab);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n");
}



void ASTToCLoopStmt(struct ASTToC *self,struct ASTLoopStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->cFileHandle,"while(true)");
    ASTToCBlockStmt(self,stmt->block,tab);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"\n");
}



void ASTToCReturnStmt(struct ASTToC *self,struct ASTReturnStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ACHIOR_LABS_FPRINTF(self->cFileHandle,"return ");
    ASTToCExpression(self,stmt->expr,true);

    ACHIOR_LABS_FPRINTF(self->cFileHandle,";");
}



void ASTToCExpression(struct ASTToC *self,struct ASTExpression *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    
	switch(ASTEXPRESSION_GET_KIND(*expr))
    {
        case AST_EXPRESSION_LITERAL:
        {
            ASTToCLiteralExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_VARIABLE:
        {
            ASTToCVariableExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PAREN:
        {
            ASTToCParenExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            ASTToCUnaryExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_BINARY:
        {
            ASTToCBinaryExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_ASSIGNMENT:
        {
            ASTToCAssignmentExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_CAST:
        {
            ASTToCCastExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_FUNCTION_CALL:
        {
            ASTToCFunctionCallExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_ADDRESS_OF:
        {
            ASTToCAddressOfExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PTR_READ:
        {
            ASTToCPtrReadExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PTR_WRITE:
        {
            ASTToCPtrWriteExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PTR_OFFSET:
        {
            ASTToCPtrOffsetExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PTR_BYTE_OFFSET:
        {
            ASTToCPtrByteOffsetExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PTR_ADVANCE:
        {
            ASTToCPtrAdvanceExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PTR_DIFF:
        {
            ASTToCPtrDiffExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_SUBSCRIPT:
        {
            ASTToCSubscriptExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_AS_PTR:
        {
            ASTToCAsPtrExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_LEN:
        {
            ASTToCLenExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_STRUCT_ACCESS:
        {
            ASTToCStructAccessExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_STRUCT_POINTER_ACCESS:
        {
            ASTToCStructPointerAccessExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_METHOD:
        {
            ASTToCMethodExpr(self,expr->expr,cFile);
            break;
        }
        case AST_EXPRESSION_PATH:
        {
            ASTToCPathExpr(self,expr->expr,cFile);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->cFileHandle,"unknown expression ");
            break;
        }
    }
}



void ASTToCPathExpr(struct ASTToC *self,struct ASTPathExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    

    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ASTToCIdentifier(self,expr->symbol->ident,cFile);

    if(ACHIOR_LABS_EQUAL(expr->symbol->kind,MODULE_SYMBOL_ENUM))
    {
        ASTToCIdentifier(self,LinkedListAt(&expr->path,expr->path.len - 1),cFile);
    }

    if(ACHIOR_LABS_TRUE(expr->isFunction))
    {
        ACHIOR_LABS_PTR_INIT(struct ASTExpression,argument);
        ACHIOR_LABS_VAR_INIT(u64,argumentLength);

        argumentLength = expr->arguments.len;

        ACHIOR_LABS_FPRINTF(handle,"(");

        for(u64 i = 0; i < argumentLength; i++)
        {
            argument = LinkedListAt(&expr->arguments,i);
            ASTToCExpression(self,argument,cFile);

            if(ACHIOR_LABS_LESS(i,argumentLength - 1))
            {
                ACHIOR_LABS_FPRINTF(handle,",");
            }
        }

        ACHIOR_LABS_FPRINTF(handle,")");
    }
}


char *ASTToCGetStructIdent(struct ASTToC *self,struct ASTType *type,bool *isPointer)
{
    if(ACHIOR_LABS_NULL(type))
    {
        puts("NULLL");
    }

    switch (type->dataType)
    {
        case AST_DATA_TYPE_STRUCT:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTStructType,structType);
            structType = type->type;


            return TOKEN_GET_VALUE_DATA(*(structType->ident));
            break;
        }
        case AST_DATA_TYPE_POINTER:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTPointerType,pointerType);
            
            pointerType = type->type;
            *isPointer  = true;

            if(ACHIOR_LABS_EQUAL(pointerType->type->dataType,AST_DATA_TYPE_STRUCT))
            {
                ACHIOR_LABS_PTR_INIT(struct ASTStructType,structType);
                structType = pointerType->type->type;


                return TOKEN_GET_VALUE_DATA(*(structType->ident));
            }

            break;
        }
        default:
        {
            printf("[TYPE ************] : %d\n",type->dataType);
            //exit(8);
            return "shotya";
        }
    }
}





void ASTToCMethodExpr(struct ASTToC *self,struct ASTMethodExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    ACHIOR_LABS_PTR_INIT(char,structIdent);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,argument);
    ACHIOR_LABS_VAR_INIT(u64,argumentLength);
    ACHIOR_LABS_VAR_INIT(bool,isPointer);


    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }


    structIdent = ASTToCGetStructIdent(self,expr->lhs->dataType,&isPointer);
    ACHIOR_LABS_FPRINTF(handle,"%s",structIdent);

    ASTToCIdentifier(self,expr->member,cFile);
    
    if(ACHIOR_LABS_TRUE(isPointer))
    {
        ACHIOR_LABS_FPRINTF(handle,"(");
    }
    else
    {
        ACHIOR_LABS_FPRINTF(handle,"(&");
    }

    

    ASTToCExpression(self,expr->lhs,cFile);
    argumentLength = expr->arguments.len;

    if(ACHIOR_LABS_GREATER(argumentLength,0))
    {
        ACHIOR_LABS_FPRINTF(handle,",");
    }

    for(u64 i = 0; i < argumentLength; i++)
    {
        argument = LinkedListAt(&expr->arguments,i);
        ASTToCExpression(self,argument,cFile);

        if(ACHIOR_LABS_LESS(i,argumentLength - 1))
        {
            ACHIOR_LABS_FPRINTF(handle,",");
        }
    }

    ACHIOR_LABS_FPRINTF(handle,")");
}


void ASTToCStructAccessExpr(struct ASTToC *self,struct ASTStructAccessExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ASTToCExpression(self,expr->lhs,cFile);
    ACHIOR_LABS_FPRINTF(handle,".");
    
    ASTToCIdentifier(self,expr->member,cFile);
}




void ASTToCStructPointerAccessExpr(struct ASTToC *self,struct ASTStructPointerAccessExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    
    ASTToCExpression(self,expr->lhs,cFile);
    ACHIOR_LABS_FPRINTF(handle,"->");
    
    ASTToCIdentifier(self,expr->member,cFile);
}


void ASTToCLenExpr(struct ASTToC *self,struct ASTLenExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);

    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    
    ACHIOR_LABS_FPRINTF(handle,"%lu",expr->dataType->layout.size);
}



void ASTToCAsPtrExpr(struct ASTToC *self,struct ASTAsPtrExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    
    ASTToCExpression(self,expr->lhs,cFile);
}




void ASTToCSubscriptExpr(struct ASTToC *self,struct ASTSubscriptExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    

    ASTToCExpression(self,expr->lhs,cFile);
    ACHIOR_LABS_FPRINTF(handle,"[");

    ASTToCExpression(self,expr->index,cFile);
    ACHIOR_LABS_FPRINTF(handle,"]");
}




void ASTToCPtrDiffExpr(struct ASTToC *self,struct ASTPtrDiffExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    

    ASTToCExpression(self,expr->lhs,cFile);
    ACHIOR_LABS_FPRINTF(handle," - ");

    ASTToCExpression(self,expr->rhs,cFile);
}






void ASTToCPtrAdvanceExpr(struct ASTToC *self,struct ASTPtrAdvanceExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ASTToCExpression(self,expr->lhs,cFile);
    ACHIOR_LABS_FPRINTF(handle," += ");

    ASTToCExpression(self,expr->rhs,cFile);
}






void ASTToCPtrByteOffsetExpr(struct ASTToC *self,struct ASTPtrByteOffsetExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ACHIOR_LABS_FPRINTF(handle,"(((i8 *)");
    ASTToCExpression(self,expr->lhs,cFile);

    ACHIOR_LABS_FPRINTF(handle,")");
    ACHIOR_LABS_FPRINTF(handle," + ");

    ASTToCExpression(self,expr->rhs,cFile);
    ACHIOR_LABS_FPRINTF(handle,")");
}







void ASTToCPtrOffsetExpr(struct ASTToC *self,struct ASTPtrOffsetExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ASTToCExpression(self,expr->lhs,cFile);
    ACHIOR_LABS_FPRINTF(handle," + ");

    ASTToCExpression(self,expr->rhs,cFile);
}





void ASTToCPtrWriteExpr(struct ASTToC *self,struct ASTPtrWriteExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ACHIOR_LABS_FPRINTF(handle,"*");
    ASTToCExpression(self,expr->lhs,cFile);

    ACHIOR_LABS_FPRINTF(handle," = ");
    ASTToCExpression(self,expr->rhs,cFile);
}






void ASTToCPtrReadExpr(struct ASTToC *self,struct ASTPtrReadExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    

    ACHIOR_LABS_FPRINTF(handle,"*");
    ASTToCExpression(self,expr->lhs,cFile);
}



void ASTToCAddressOfExpr(struct ASTToC *self,struct ASTAddressOfExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    

    ACHIOR_LABS_FPRINTF(handle,"&");
    ASTToCExpression(self,expr->rhs,cFile);
}



void ASTToCFunctionCallExpr(struct ASTToC *self,struct ASTFunctionCallExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    ACHIOR_LABS_PTR_INIT(struct ASTExpression,argument);
    ACHIOR_LABS_VAR_INIT(u64,argumentLength);

    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ASTToCExpression(self,expr->base,cFile);
    ACHIOR_LABS_FPRINTF(handle,"(");

    argumentLength = expr->arguments.len;

    for(u64 i = 0; i < argumentLength; i++)
    {
        argument = LinkedListAt(&expr->arguments,i);
        ASTToCExpression(self,argument,cFile);

        if(ACHIOR_LABS_LESS(i,argumentLength - 1))
        {
            ACHIOR_LABS_FPRINTF(handle,",");
        }
    }

    ACHIOR_LABS_FPRINTF(handle,")");

}



void ASTToCCastExpr(struct ASTToC *self,struct ASTCastExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    

    ACHIOR_LABS_FPRINTF(handle,"(");
    ASTToCType(self,expr->dataType,NULL,cFile);

    ACHIOR_LABS_FPRINTF(handle,")");
    ASTToCExpression(self,expr->lhs,cFile);
}



void ASTToCAssignmentExpr(struct ASTToC *self,struct ASTAssignmentExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    

    ASTToCExpression(self,expr->lhs,cFile);
    ASTToCAssignmentOperator(self,expr->op,cFile);
    ASTToCExpression(self,expr->rhs,cFile);
}



void ASTToCAssignmentOperator(struct ASTToC *self,enum ASTAssignmentOperator op,bool cFile)
{
    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    switch(op)
    {
        case AST_ASSIGNMENT_OPERATOR_ADD:
        {
            ACHIOR_LABS_FPRINTF(handle," += ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_SUB:
        {
            ACHIOR_LABS_FPRINTF(handle," -= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_MUL:
        {
            ACHIOR_LABS_FPRINTF(handle," *= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_DIV:
        {
            ACHIOR_LABS_FPRINTF(handle," /= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_MOD:
        {
            ACHIOR_LABS_FPRINTF(handle," %%= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR:
        {
            ACHIOR_LABS_FPRINTF(handle," = ");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(handle," unknown-assignmet-operator ");
            break;
        }
    }
}


void ASTToCBinaryExpr(struct ASTToC *self,struct ASTBinaryExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    
    ASTToCExpression(self,expr->lhs,cFile);
    ASTToCBinaryOperator(self,expr->op,cFile);
    ASTToCExpression(self,expr->rhs,cFile);
}



void ASTToCBinaryOperator(struct ASTToC *self,enum ASTBinaryOperator op,bool cFile)
{
    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    switch(op)
    {
        case AST_BINARY_OPERATOR_ADD:
        {
            ACHIOR_LABS_FPRINTF(handle," + ");
            break;
        }
        case AST_BINARY_OPERATOR_SUB:
        {
            ACHIOR_LABS_FPRINTF(handle," - ");
            break;
        }
        case AST_BINARY_OPERATOR_MUL:
        {
            ACHIOR_LABS_FPRINTF(handle," * ");
            break;
        }
        case AST_BINARY_OPERATOR_DIV:
        {
            ACHIOR_LABS_FPRINTF(handle," / ");
            break;
        }
        case AST_BINARY_OPERATOR_MOD:
        {
            ACHIOR_LABS_FPRINTF(handle," %% ");
            break;
        }
        case AST_BINARY_OPERATOR_LESS:
        {
            ACHIOR_LABS_FPRINTF(handle," < ");
            break;
        }
        case AST_BINARY_OPERATOR_LESS_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(handle," <= ");
            break;
        }
        case AST_BINARY_OPERATOR_GREATER:
        {
            ACHIOR_LABS_FPRINTF(handle," > ");
            break;
        }
        case AST_BINARY_OPERATOR_GREATER_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(handle," >= ");
            break;
        }
        case AST_BINARY_OPERATOR_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(handle," == ");
            break;
        }
        case AST_BINARY_OPERATOR_NOT_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(handle," != ");
            break;
        }
        case AST_BINARY_OPERATOR_AND:
        {
            ACHIOR_LABS_FPRINTF(handle," && ");
            break;
        }
        case AST_BINARY_OPERATOR_OR:
        {
            ACHIOR_LABS_FPRINTF(handle," || ");
            break;
        }
        case AST_BINARY_OPERATOR_BITWISE_AND:
        {
            ACHIOR_LABS_FPRINTF(handle," & ");
            break;
        }
        case AST_BINARY_OPERATOR_BITWISE_OR:
        {
            ACHIOR_LABS_FPRINTF(handle," | ");
            break;
        }
        case AST_BINARY_OPERATOR_BITWISE_LEFT_SHIFT:
        {
            ACHIOR_LABS_FPRINTF(handle," << ");
            break;
        }
        case AST_BINARY_OPERATOR_BITWISE_RIGHT_SHIFT:
        {
            ACHIOR_LABS_FPRINTF(handle," >> ");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(handle,"unknown binary operator");
            break;
        }
    }
}


void ASTToCUnaryExpr(struct ASTToC *self,struct ASTUnaryExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    
    ASTToCUnaryOperator(self,expr->op,cFile);
    ASTToCExpression(self,expr->rhs,cFile);
}


void ASTToCUnaryOperator(struct ASTToC *self,enum ASTUnaryOperator op,bool cFile)
{
    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    switch(op)
    {
        case AST_UNARY_OPERATOR_COMPLEMENT:
        {
            ACHIOR_LABS_FPRINTF(handle,"~");
            break;
        }
        case AST_UNARY_OPERATOR_NEGATE:
        {
            ACHIOR_LABS_FPRINTF(handle,"-");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(handle,"unknown unary operator");
            break;
        }
    }
}



void ASTToCParenExpr(struct ASTToC *self,struct ASTParenExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    
    ACHIOR_LABS_FPRINTF(handle,"( ");
    ASTToCExpression(self,expr->expr,cFile);

    ACHIOR_LABS_FPRINTF(handle,") ");
}



void ASTToCVariableExpr(struct ASTToC *self,struct ASTVariableExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }

    ASTToCIdentifier(self,expr->ident,cFile);
}








void ASTToCLiteralExpr(struct ASTToC *self,struct ASTLiteralExpr *expr,bool cFile)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(FILE,handle);
    handle = self->hFileHandle;

    if(ACHIOR_LABS_TRUE(cFile))
    {
        handle = self->cFileHandle;
    }
    
    
    switch(expr->kind)
    {
        case AST_LITERAL_CHARACTER:
        {
            ACHIOR_LABS_FPRINTF(handle,"'%s'",expr->literal->value.data);
            break;
        }
        case AST_LITERAL_I32:
        {
            ACHIOR_LABS_FPRINTF(handle,"%s",expr->literal->value.data);
            break;
        }
        case AST_LITERAL_STRING:
        {
            ACHIOR_LABS_FPRINTF(handle,"\"%s\"",expr->literal->value.data);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(handle,"unknown literal expression");
        }
    }
}
