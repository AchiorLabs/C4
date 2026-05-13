#include "Include/IdentifierResolution.h"



bool IdentifierEntryNew(struct IdentifierEntry *self,bool hasLinkage,bool isCurrent,enum IdentifierAggregateKind aggregateKind,struct String ident)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->hasLinkage    = hasLinkage;
    self->isCurrent     = isCurrent;
    self->aggregateKind = aggregateKind;
    self->ident         = ident;

    return true;
}

struct String StringReplacePathSeparators(struct String source)
{
    ACHIOR_LABS_VAR_INIT(u64,sourceLength);
    ACHIOR_LABS_STRUCT_INIT(struct String,destination);
    
    sourceLength = source.size;
    
    StringNew(&destination,source.capacity,source.bump);

	for (u64 i = 0; i < sourceLength; i++)
	{
		// Replace "::" with "_" 
		if (i + 1 < sourceLength && source.data[i] == ':' && source.data[i + 1] == ':')
		{
			StringPushBackChar(&destination,'_');

			i++; // Skip second ':' 
			continue;
		}

		StringPushBackChar(&destination,source.data[i]);
	}

	return destination;
}



void IdentifierResolutionFatal(struct IdentifierResolution *self,struct Token *token,char *message,char *label,char *help,char *fix,char *note)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	ACHIOR_LABS_STRUCT_INIT(struct Span,span);
	ACHIOR_LABS_PTR_INIT(struct Diagnostic,diagnostic);

	span             = token->span;
	diagnostic       = DiagnosticEngineReport(self->engine,DIAGNOSTIC_ERROR,message,self->moduleName,self->moduleSource,self->sourceLength,1);
	
	
	if(ACHIOR_LABS_NOT_NULL(label))
	{
		DiagnosticAddLabel(diagnostic,span,label,true,self->bump);
	}
	else
	{
		DiagnosticAddLabel(diagnostic,span,"",true,self->bump);
	}

	if(ACHIOR_LABS_NOT_NULL(help))
	{
		DiagnosticAddHelp(diagnostic,help,self->bump);
	}

	if(ACHIOR_LABS_NOT_NULL(fix))
	{
		DiagnosticAddFix(diagnostic,span,fix,self->bump);
	}
	
	if(ACHIOR_LABS_NOT_NULL(note))
	{
		DiagnosticAddNote(diagnostic,note,self->bump);
	}
}


bool IdentifierResolutionNew(struct IdentifierResolution *self,char *moduleName,char *moduleSource,struct ASTProgram *program,u64 globalCounter,struct DiagnosticEngine *engine,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    ACHIOR_LABS_STRUCT_INIT(struct HashMap,identMap);

    self->program       = program;
    self->globalCounter = globalCounter;
    self->engine        = engine;
    self->bump          = bump;
    self->moduleName    = moduleName;
    self->moduleSource  = moduleSource;
    self->sourceLength  = ACHIOR_LABS_STRLEN(moduleSource);
    

    HashMapNew(&identMap,10,self->bump);
    HashMapNew(&self->program->identMap,10,self->bump);
    HashMapNew(&self->structMap,10,self->bump);
    HashMapNew(&self->functionAttributes,10,self->bump);

    
    IdentifierResolutionProgram(self,program,&identMap);

    //puts("Identifier Resolution done");

    return true;
}




struct HashMap IdentifierResolutionCopyIdentMap(struct IdentifierResolution *self,struct HashMap *identMap)
{
    ACHIOR_LABS_STRUCT_INIT(struct HashMap,newIdentMap);

    if( ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(identMap))
    {
        newIdentMap;
    }

    HashMapNew(&newIdentMap,identMap->capacity,self->bump);

    for(u64 i = 0; i < identMap->capacity; i++)
    {
        ACHIOR_LABS_VAR_INIT(u64,j);

        ACHIOR_LABS_PTR_INIT(struct HashNode,previousNode);
        ACHIOR_LABS_PTR_INIT(struct HashNode,newNode);
        ACHIOR_LABS_PTR_INIT(struct HashNode,node);
        ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
        ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,newEntry);

        ACHIOR_LABS_STRUCT_INIT(struct String,newIdent);

        for (node = identMap->buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            newNode = (struct HashNode *)ACHIOR_LABS_ARENA_ALLOC(self->bump,struct HashNode,1);

            if(ACHIOR_LABS_NULL(newNode))
            {
                continue;
            }

            newNode->hash = node->hash;
            newNode->key  = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,node->keyLength);

            if(ACHIOR_LABS_NULL(newNode->key))
            {
                continue;
            }

            newNode->keyLength = node->keyLength;
            ACHIOR_LABS_MEMCPY(newNode->key,node->key,node->keyLength);

            entry    = (struct IdentifierEntry *)node->value;
            newEntry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
            
            
            StringNew(&newIdent,entry->ident.capacity,self->bump);
            StringPushBack(&newIdent,entry->ident.data);

            IdentifierEntryNew(newEntry,entry->hasLinkage,false,entry->aggregateKind,newIdent);
            

            newNode->value = newEntry;
            newNode->next  = NULL;

            if(ACHIOR_LABS_NOT_NULL(previousNode))
            {
                previousNode->next = newNode;
            }

            previousNode   = newNode; 

            if(ACHIOR_LABS_ZERO(j))
            {
                newIdentMap.buckets[i] = newNode;
            }

            newIdentMap.size++;
            j++;
        }
    }
    
    return newIdentMap;
}




void IdentifierResolutionProgram(struct IdentifierResolution *self,struct ASTProgram *program,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(program))
    {
        return;
    }
 
    
    ACHIOR_LABS_VAR_INIT(u64,declarationLength);

    declarationLength = LinkedListLength(&program->decls);

    for(u64 i = 0; i < declarationLength; i++)
    {
		IdentifierResolutionDeclaration(self,LinkedListAt(&program->decls,i),identMap);
	}
}


void IdentifierResolutionDeclaration(struct IdentifierResolution *self,struct ASTDeclaration *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

	switch(ASTDECLARATION_GET_KIND(*decl))
	{
		case AST_DECLARATION_ENUM:
		{
			IdentifierResolutionEnumDecl(self,ASTDECLARATION_GET_DECL(*decl),identMap);
			break;
		}
		case AST_DECLARATION_STRUCT:
		{
			IdentifierResolutionStructDecl(self,ASTDECLARATION_GET_DECL(*decl),identMap);
			break;
		}
		case AST_DECLARATION_IMPL:
		{
			IdentifierResolutionImplDecl(self,ASTDECLARATION_GET_DECL(*decl),identMap);
			break;
		}
		case AST_DECLARATION_SUM:
		{
            break;
			//IdentifierResolutionSumDecl(self,ASTDECLARATION_GET_DECL(*decl),identMap);
			break;
		}
		case AST_DECLARATION_FUNCTION:
		{
			IdentifierResolutionFunctionDecl(self,ASTDECLARATION_GET_DECL(*decl),(struct String){0},identMap);
			break;
		}
		default:
		{
			break;
		}
	}
}




void IdentifierResolutionEnumDecl(struct IdentifierResolution *self,struct ASTEnumDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
    ACHIOR_LABS_PTR_INIT(char,structIdent);
    ACHIOR_LABS_PTR_INIT(struct ASTEnumConstant,constant);
    ACHIOR_LABS_PTR_INIT(struct Token,token);
    ACHIOR_LABS_PTR_INIT(char,ident);

    ACHIOR_LABS_VAR_INIT(u64,structIdentLength);

    ACHIOR_LABS_STRUCT_INIT(struct String,moduleIdent);

    
    StringNew(&moduleIdent,20,self->bump);

    StringPushBack(&moduleIdent,self->moduleName);
    StringPushBack(&moduleIdent,TOKEN_GET_VALUE_DATA(*(decl->ident)));

    moduleIdent       = StringReplacePathSeparators(moduleIdent);
    structIdent       = TOKEN_GET_VALUE_DATA(*(decl->ident));
    structIdentLength = ACHIOR_LABS_STRLEN(structIdent);
    entry             = HashMapGet(&self->structMap,structIdent,structIdentLength);

    TOKEN_SET_VALUE(*(decl->ident),moduleIdent);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(entry->aggregateKind == IDENTIFIER_AGGREGATE_ENUM)
        {
            IdentifierResolutionFatal(self,decl->ident,"enum redeclared ",NULL,"assign a different name to your enum"," newEnumName",NULL);
        }
        else
        {
            IdentifierResolutionFatal(self,decl->ident,"enum shares same name with another struct ",NULL,"assign a different name to your enum"," newEnumName",NULL);
        }
        
        return;
    }

    entry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_ENUM,TOKEN_GET_VALUE(*(decl->ident)));
    
    HashMapAdd(&self->structMap,structIdent,structIdentLength,entry);
    HashMapAdd(&self->program->identMap,structIdent,structIdentLength,entry);

    structIdent = TOKEN_GET_VALUE_DATA(*(decl->ident));

    for(u64 i = 0; i <decl->constants.len; i++)
    {
        constant = LinkedListAt(&decl->constants,i);
        token    = constant->constant;
        ident    = token->value.data;


        StringNew(&token->value,token->value.capacity,self->bump);
        StringPushBack(&token->value,structIdent);
        StringPushBack(&token->value,ident);
    }

}



void IdentifierResolutionStructDecl(struct IdentifierResolution *self,struct ASTStructDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
    ACHIOR_LABS_PTR_INIT(char,structIdent);
    ACHIOR_LABS_PTR_INIT(struct ASTStructProperty,property);

    ACHIOR_LABS_VAR_INIT(u64,structIdentLength);

    ACHIOR_LABS_STRUCT_INIT(struct String,moduleIdent);

    
    StringNew(&moduleIdent,20,self->bump);

    StringPushBack(&moduleIdent,self->moduleName);
    StringPushBack(&moduleIdent,TOKEN_GET_VALUE_DATA(*(decl->ident)));

    moduleIdent       = StringReplacePathSeparators(moduleIdent);
    structIdent       = TOKEN_GET_VALUE_DATA(*(decl->ident));
    structIdentLength = ACHIOR_LABS_STRLEN(structIdent);
    entry             = HashMapGet(&self->structMap,structIdent,structIdentLength);

    TOKEN_SET_VALUE(*(decl->ident),moduleIdent);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(entry->aggregateKind == IDENTIFIER_AGGREGATE_STRUCT)
        {
            IdentifierResolutionFatal(self,decl->ident,"struct redeclared ",NULL,"assign a different name to your struct"," newStructName",NULL);
        }
        else
        {
            IdentifierResolutionFatal(self,decl->ident,"struct shares same name with another enum ",NULL,"assign a different name to your struct"," newStructName",NULL);
        }
        
        return;
    }

    entry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_STRUCT,TOKEN_GET_VALUE(*(decl->ident)));
    
    HashMapAdd(&self->structMap,structIdent,structIdentLength,entry);
    HashMapAdd(&self->program->identMap,structIdent,structIdentLength,entry);


    for(u64 i = 0; i < decl->properties.len; i++)
    {
        property = LinkedListAt(&decl->properties,i);

        IdentifierResolutionType(self,property->type);
    }
}




/*


void IdentifierResolutionSumDecl(struct IdentifierResolution *self,struct ASTSumDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    IdentifierResolutionSumEnum(self,TOKEN_GET_VALUE_DATA(*(decl->ident)),decl->variants);
    

    
    IdentifierResolutionIdentifier(self,decl->ident);

    

    IdentifierResolutionSumVariants(self,decl->variants);

    

}


char *IdentifierResolutionCapitalizeString(struct IdentifierResolution *self,char *source)
{
    u64 length        = ACHIOR_LABS_STRLEN(source);
    char *destination = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,length + 1); 

    for(u64 i = 0; i < length; i++)
    {
        destination[i] = ACHIOR_LABS_TOUPPER(source[i]);
    }

    destination[length] = '\0';
    return destination;
}


void IdentifierResolutionSumEnum(struct IdentifierResolution *self,char *ident,struct LinkedList variants)
{
    
    for(u64 i = 0; i < variants.len; i++)
    {
        struct ASTSumVariant *variant = LinkedListAt(&variants,i);

        
        break;
    }

    
}




void IdentifierResolutionSumVariants(struct IdentifierResolution *self,struct LinkedList va8/riants)
{
    
    for(u64 i = 0; i < variants.len; i++)
    {
        struct ASTSumVariant *variant = LinkedListAt(&variants,i);

        switch(variant->kind)
        {
            case AST_SUM_VARIANT_UNIT:
            {
                struct ASTType *type = LinkedListAt(&variant->fields,0);
                
                struct LinkedList arrayBuffer;
                
                
                //IdentifierResolutionType(self,type,&arrayBuffer,identMap);
                
                IdentifierResolutionIdentifier(self,variant->ident);
                
                
                break;
            }
            case AST_SUM_VARIANT_TUPLE:
            {
                for(u64 i = 0; i < variant->fields.len; i++)
                {
                    struct ASTType *type = LinkedListAt(&variant->fields,i);
                    struct LinkedList arrayBuffer;
                    //IdentifierResolutionType(self,type,&arrayBuffer,identMap);
                }

                
                break;
            }
            case AST_SUM_VARIANT_STRUCT:
            {
                break;
            }
        }
    }
    
}


*/



void IdentifierResolutionImplDecl(struct IdentifierResolution *self,struct ASTImplDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct ASTFunctionDecl,method);

    ACHIOR_LABS_VAR_INIT(u64,methodLength);

    ACHIOR_LABS_STRUCT_INIT(struct String,moduleIdent);
    ACHIOR_LABS_STRUCT_INIT(struct HashMap,newIdentMap);


    StringNew(&moduleIdent,20,self->bump);

    StringPushBack(&moduleIdent,self->moduleName);
    StringPushBack(&moduleIdent,TOKEN_GET_VALUE_DATA(*(decl->ident)));

    moduleIdent = StringReplacePathSeparators(moduleIdent);



    TOKEN_GET_VALUE(*(decl->ident)) = moduleIdent;

    
    newIdentMap  = IdentifierResolutionCopyIdentMap(self,identMap);
    methodLength = LinkedListLength(&decl->methods);

    for(u64 i = 0; i < methodLength; i++)
    {
        method = LinkedListAt(&decl->methods,i);
        
        IdentifierResolutionFunctionDecl(self,method,TOKEN_GET_VALUE(*(decl->ident)),&newIdentMap);
    }
}



void IdentifierResolutionType(struct IdentifierResolution *self,struct ASTType *type)
{
    if( ACHIOR_LABS_NULL(type))
    {
        return;
    }

    

    switch(type->dataType)
    {
        case AST_DATA_TYPE_AGGREGATE:
        {
            struct ASTAggregateType *aggregateType = (struct ASTAggregateType *)type->type;
            struct Token *token                    = LinkedListAt(&aggregateType->path,0);
            char *ident                            = token->value.data;
            u64 identLength                        = ACHIOR_LABS_STRLEN(ident);
            struct IdentifierEntry *entry          = HashMapGet(&self->structMap,ident,identLength);

            if(ACHIOR_LABS_NULL(entry))
            {
                return;
            }

            token->value = entry->ident;

            struct ASTStructType *structType = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructType,1);
            ASTStructTypeNew(structType,token,(struct Layout){0});
            type->type = structType;


            if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
            {
                type->dataType = AST_DATA_TYPE_STRUCT;
            }
            else if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_ENUM))
            {
                type->dataType = AST_DATA_TYPE_ENUM;
            }
            else if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_UNION))
            {
                type->dataType = AST_DATA_TYPE_UNION;
            }
            break;
        }
        case AST_DATA_TYPE_STRUCT:
        {
            struct ASTStructType *structType = (struct ASTStructType *)type->type;
            char *ident                      = TOKEN_GET_VALUE_DATA(*(structType->ident));
            u64 identLength                  = ACHIOR_LABS_STRLEN(ident);
            struct IdentifierEntry *entry    = HashMapGet(&self->structMap,ident,identLength);


            if(ACHIOR_LABS_NULL(entry))
            {
                return;
            }


            TOKEN_SET_VALUE(*(structType->ident),entry->ident);
            
            break;
        }
        case AST_DATA_TYPE_POINTER:
        {
            struct ASTPointerType *pointerType = (struct ASTPointerType *)type->type;
            IdentifierResolutionType(self,pointerType->type);
            break;
        }
    }
}


void IdentifierResolutionFunctionDecl(struct IdentifierResolution *self,struct ASTFunctionDecl *decl,struct String structIdent,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    if(ACHIOR_LABS_NOT_NULL(decl->attributes) && ACHIOR_LABS_TRUE(decl->attributes->isForeign))
    {
        //return;
    }


    ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
    ACHIOR_LABS_PTR_INIT(char,ident);
    ACHIOR_LABS_PTR_INIT(struct ASTStructProperty,property);

    ACHIOR_LABS_VAR_INIT(u64,identLength);
    ACHIOR_LABS_VAR_INIT(u64,argumentLength);

    ACHIOR_LABS_STRUCT_INIT(struct String,moduleIdent);
    ACHIOR_LABS_STRUCT_INIT(struct String,newIdent);
    ACHIOR_LABS_STRUCT_INIT(struct HashMap,newIdentMap);


    IdentifierResolutionType(self,decl->returnType);


    StringNew(&moduleIdent,20,self->bump);

    StringPushBack(&moduleIdent,self->moduleName);

    if(ACHIOR_LABS_NOT_ZERO(structIdent.size))
    {
        moduleIdent.size = 0;
        StringPushBack(&moduleIdent,structIdent.data);
    }

    StringPushBack(&moduleIdent,TOKEN_GET_VALUE_DATA(*(decl->ident)));
    

    moduleIdent = StringReplacePathSeparators(moduleIdent);



    ident       = TOKEN_GET_VALUE_DATA(*(decl->ident));
    identLength = ACHIOR_LABS_STRLEN(ident);
    entry       = HashMapGet(identMap,ident,identLength);
    newIdent    = TOKEN_GET_VALUE(*(decl->ident));

    if(ACHIOR_LABS_STRNCMP(TOKEN_GET_VALUE_DATA(*(decl->ident)),"main",4) && ACHIOR_LABS_FALSE(decl->attributes->isForeign))
    {
        TOKEN_SET_VALUE(*(decl->ident),moduleIdent);

        newIdent = moduleIdent;
    }


    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(ACHIOR_LABS_TRUE(entry->isCurrent))
        {
            IdentifierResolutionFatal(self,decl->ident,"function redeclared ",NULL,"assign a different name to your function"," newFunctionName",NULL);
            return;
        }
        
    }

    HashMapAdd(&self->functionAttributes,newIdent.data,newIdent.size,decl->attributes);

    entry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);

    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_NONE,TOKEN_GET_VALUE(*(decl->ident)));
    
    HashMapAdd(identMap,ident,identLength,entry);
    HashMapAdd(&self->program->identMap,ident,identLength,entry);

    newIdentMap    = IdentifierResolutionCopyIdentMap(self,identMap);
    argumentLength = LinkedListLength(&decl->arguments);

    for(u64 i = 0; i < argumentLength; i++)
    {
        IdentifierResolutionFunctionArgument(self,LinkedListAt(&decl->arguments,i),&newIdentMap);
    }

    
    if(ACHIOR_LABS_NOT_NULL(decl->block))
    {
        IdentifierResolutionBlockStmt(self,decl->block,&newIdentMap);
    }
}





void IdentifierResolutionFunctionArgument(struct IdentifierResolution *self,struct ASTFunctionArgument *argument,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
    ACHIOR_LABS_PTR_INIT(char,ident);

    ACHIOR_LABS_VAR_INIT(u64,identLength);

    ACHIOR_LABS_STRUCT_INIT(struct String,newIdent);


    IdentifierResolutionType(self,argument->type);

    ident       = TOKEN_GET_VALUE_DATA(*(argument->ident));
    identLength = ACHIOR_LABS_STRLEN(ident);
    entry       = HashMapGet(identMap,ident,identLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(ACHIOR_LABS_TRUE(entry->isCurrent))
        {
            IdentifierResolutionFatal(self,argument->ident,"function argument redeclared ",NULL,"assign a different name to your function argument"," newFunctionArgumentName",NULL);
            return;
        }
        
    }

    newIdent = IdentifierResolutionMakeTmp(self);
    entry   = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);

    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_NONE,newIdent);
    
    HashMapAdd(identMap,ident,identLength,entry);
    HashMapAdd(&self->program->identMap,ident,identLength,entry);

    TOKEN_SET_VALUE(*(argument->ident),newIdent);
}



void IdentifierResolutionBlockStmt(struct IdentifierResolution *self,struct ASTBlockStmt *block,struct HashMap *identMap)
{
    ACHIOR_LABS_VAR_INIT(u64,stmtLength);

    ACHIOR_LABS_STRUCT_INIT(struct HashMap,newIdentMap);

    newIdentMap = IdentifierResolutionCopyIdentMap(self,identMap);
    stmtLength  = LinkedListLength(&block->stmts);

    for(u64 i = 0; i < stmtLength; i++)
    {
        IdentifierResolutionStmt(self,LinkedListAt(&block->stmts,i),&newIdentMap);
    }   
}


void IdentifierResolutionStmt(struct IdentifierResolution *self,struct ASTStatement *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

	switch(ASTSTATEMENT_GET_KIND(*stmt))
	{
		case AST_STATEMENT_RETURN:
		{
            IdentifierResolutionReturnStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_LOOP:
		{
            IdentifierResolutionLoopStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_WHILE:
		{
            IdentifierResolutionWhileStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_BREAK:
		{
            IdentifierResolutionBreakStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_CONTINUE:
		{
            IdentifierResolutionContinueStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_IF:
		{
            IdentifierResolutionIfStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_VAR_DECL:
		{
            IdentifierResolutionVariableDeclStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
        case AST_STATEMENT_EXPRESSION:
		{
            IdentifierResolutionExpressionStmt(self,ASTSTATEMENT_GET_STMT(*stmt),identMap);
			break;
		}
		default:
		{
			break;
		}
	}

}





void IdentifierResolutionExpressionStmt(struct IdentifierResolution *self,struct ASTExpression *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionExpression(self,stmt,identMap);
}



void IdentifierResolutionVariableDeclStmt(struct IdentifierResolution *self,struct ASTVariableDecl *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
    ACHIOR_LABS_PTR_INIT(char,ident);
    
    ACHIOR_LABS_VAR_INIT(u64,identLength);

    ACHIOR_LABS_STRUCT_INIT(struct String,newIdent);

    IdentifierResolutionType(self,stmt->type);

    ident       = TOKEN_GET_VALUE_DATA(*(stmt->ident));
    identLength = ACHIOR_LABS_STRLEN(ident);
    entry       = HashMapGet(identMap,ident,identLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(ACHIOR_LABS_TRUE(entry->isCurrent))
        {
            IdentifierResolutionFatal(self,stmt->ident,"variable identifier redeclared ",NULL,"assign a different name to your variable declaration"," newVariableName",NULL);
            return;
        }
        
    }

    newIdent = IdentifierResolutionMakeTmp(self);
    entry    = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);

    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_NONE,newIdent);
    
    HashMapAdd(identMap,ident,identLength,entry);
    HashMapAdd(&self->program->identMap,ident,identLength,entry);

    TOKEN_SET_VALUE(*(stmt->ident),newIdent);

    if(ACHIOR_LABS_NOT_NULL(stmt->init))
    {
        IdentifierResolutionVariableDeclInit(self,stmt->init,identMap);
    }
}



void IdentifierResolutionVariableDeclInit(struct IdentifierResolution *self,struct ASTVariableDeclInit *init,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(init))
    {
        return;
    }

    switch(ASTVARIABLEDECLINIT_GET_INITKIND(*init))
    {
        case AST_VAR_DECL_INIT_SINGLE_INIT:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclSingleInit,singleInit);

            singleInit = init->init;

            IdentifierResolutionExpression(self,singleInit->expr,identMap);
            break;
        }
        case AST_VAR_DECL_INIT_ARRAY_INIT:
        {
            ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclInit,tmpInit);
            ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclArrayInit,arrayInit);

            ACHIOR_LABS_VAR_INIT(u64,elementLength);

            arrayInit     = init->init;
            elementLength = LinkedListLength(&arrayInit->elements);

            for(u64 i = 0; i < elementLength; i++)
            {
                tmpInit = LinkedListAt(&arrayInit->elements,i);

                IdentifierResolutionVariableDeclInit(self,tmpInit,identMap);
            }
            break;
        }
    }

}



void IdentifierResolutionIfStmt(struct IdentifierResolution *self,struct ASTIfStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
    
    ACHIOR_LABS_PTR_INIT(struct ASTIfElif,elifBlock);

    ACHIOR_LABS_VAR_INIT(u64,elifLength);

    IdentifierResolutionExpression(self,stmt->expr,identMap);
    IdentifierResolutionBlockStmt(self,stmt->block,identMap);


    elifLength = LinkedListLength(&stmt->elifs);

    for(u64 i = 0; i < elifLength; i++)
    {
        elifBlock = LinkedListAt(&stmt->elifs,i);

        IdentifierResolutionExpression(self,elifBlock->expr,identMap);   
        IdentifierResolutionBlockStmt(self,elifBlock->block,identMap);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->elseBlock))
    {
        IdentifierResolutionBlockStmt(self,stmt->elseBlock->block,identMap);
    }
}


void IdentifierResolutionContinueStmt(struct IdentifierResolution *self,struct ASTContinueStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}



void IdentifierResolutionBreakStmt(struct IdentifierResolution *self,struct ASTBreakStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}


void IdentifierResolutionWhileStmt(struct IdentifierResolution *self,struct ASTWhileStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionExpression(self,stmt->expr,identMap);
    IdentifierResolutionBlockStmt(self,stmt->block,identMap);
}



void IdentifierResolutionLoopStmt(struct IdentifierResolution *self,struct ASTLoopStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionBlockStmt(self,stmt->block,identMap);
}



void IdentifierResolutionReturnStmt(struct IdentifierResolution *self,struct ASTReturnStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionExpression(self,stmt->expr,identMap);    
}



void IdentifierResolutionExpression(struct IdentifierResolution *self,struct ASTExpression *expr,struct HashMap *identMap)
{    
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    

	switch(ASTEXPRESSION_GET_KIND(*expr))
    {
        case AST_EXPRESSION_LITERAL:
        {
            break;
        }
        case AST_EXPRESSION_VARIABLE:
        {
            IdentifierResolutionVariableExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PAREN:
        {
            IdentifierResolutionParenExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            IdentifierResolutionUnaryExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_BINARY:
        {
            IdentifierResolutionBinaryExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_ASSIGNMENT:
        {
            IdentifierResolutionAssignmentExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_CAST:
        {
            IdentifierResolutionCastExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_FUNCTION_CALL:
        {
            IdentifierResolutionFunctionCallExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_ADDRESS_OF:
        {
            IdentifierResolutionAddressOfExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PTR_READ:
        {
            IdentifierResolutionPtrReadExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PTR_WRITE:
        {
            IdentifierResolutionPtrWriteExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PTR_OFFSET:
        {
            IdentifierResolutionPtrOffsetExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PTR_BYTE_OFFSET:
        {
            IdentifierResolutionPtrByteOffsetExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PTR_ADVANCE:
        {
            IdentifierResolutionPtrAdvanceExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PTR_DIFF:
        {
            IdentifierResolutionPtrDiffExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_SUBSCRIPT:
        {
            IdentifierResolutionSubscriptExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_AS_PTR:
        {
            IdentifierResolutionAsPtrExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_LEN:
        {
            IdentifierResolutionLenExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_STRUCT_ACCESS:
        {
            IdentifierResolutionStructAccessExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_STRUCT_POINTER_ACCESS:
        {
            IdentifierResolutionStructPointerAccessExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_METHOD:
        {
            IdentifierResolutionMethodExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        case AST_EXPRESSION_PATH:
        {
            IdentifierResolutionPathExpr(self,ASTEXPRESSION_GET_EXPR(*expr),identMap);
            break;
        }
        default:
        {
            
            break;
        }
    }
}



void IdentifierResolutionPathExpr(struct IdentifierResolution *self,struct ASTPathExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    if(ACHIOR_LABS_TRUE(expr->isFunction))
    {
        ACHIOR_LABS_PTR_INIT(struct ASTExpression,tmpExpr);

        ACHIOR_LABS_VAR_INIT(u64,argumentLength);

        argumentLength = expr->arguments.len;

        for(u64 i = 0; i < argumentLength; i++)
        {
            tmpExpr = LinkedListAt(&expr->arguments,i);

            IdentifierResolutionExpression(self,tmpExpr,identMap);
        }
    }
}

void IdentifierResolutionMethodExpr(struct IdentifierResolution *self,struct ASTMethodExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    ACHIOR_LABS_PTR_INIT(struct ASTExpression,argument);

    ACHIOR_LABS_VAR_INIT(u64,argumentLength);

    IdentifierResolutionExpression(self,expr->lhs,identMap);

    argumentLength = expr->arguments.len;

    for(u64 i = 0; i < argumentLength; i++)
    {
        argument = LinkedListAt(&expr->arguments,i);

        IdentifierResolutionExpression(self,argument,identMap);
    }

}



void IdentifierResolutionStructPointerAccessExpr(struct IdentifierResolution *self,struct ASTStructPointerAccessExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    IdentifierResolutionExpression(self,expr->lhs,identMap);
}


void IdentifierResolutionStructAccessExpr(struct IdentifierResolution *self,struct ASTStructAccessExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    IdentifierResolutionExpression(self,expr->lhs,identMap);
}


void IdentifierResolutionLenExpr(struct IdentifierResolution *self,struct ASTLenExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
}



void IdentifierResolutionAsPtrExpr(struct IdentifierResolution *self,struct ASTAsPtrExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    
    IdentifierResolutionExpression(self,expr->lhs,identMap);
}




void IdentifierResolutionSubscriptExpr(struct IdentifierResolution *self,struct ASTSubscriptExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    IdentifierResolutionExpression(self,expr->lhs,identMap);    
    IdentifierResolutionExpression(self,expr->index,identMap);
}




void IdentifierResolutionPtrDiffExpr(struct IdentifierResolution *self,struct ASTPtrDiffExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}






void IdentifierResolutionPtrAdvanceExpr(struct IdentifierResolution *self,struct ASTPtrAdvanceExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}






void IdentifierResolutionPtrByteOffsetExpr(struct IdentifierResolution *self,struct ASTPtrByteOffsetExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    
    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}







void IdentifierResolutionPtrOffsetExpr(struct IdentifierResolution *self,struct ASTPtrOffsetExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}





void IdentifierResolutionPtrWriteExpr(struct IdentifierResolution *self,struct ASTPtrWriteExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}






void IdentifierResolutionPtrReadExpr(struct IdentifierResolution *self,struct ASTPtrReadExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    IdentifierResolutionExpression(self,expr->lhs,identMap);
}



void IdentifierResolutionAddressOfExpr(struct IdentifierResolution *self,struct ASTAddressOfExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}



void IdentifierResolutionFunctionCallExpr(struct IdentifierResolution *self,struct ASTFunctionCallExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct ASTExpression,argument);

    ACHIOR_LABS_VAR_INIT(u64,argumentLength);


    IdentifierResolutionExpression(self,expr->base,identMap);

    argumentLength = expr->arguments.len;

    for(u64 i = 0; i < argumentLength; i++)
    {
        argument = LinkedListAt(&expr->arguments,i);
        
        IdentifierResolutionExpression(self,argument,identMap);
    }
   

    if(ACHIOR_LABS_EQUAL(ASTEXPRESSION_GET_KIND(*(expr->base)),AST_EXPRESSION_VARIABLE))
    {
        ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
        ACHIOR_LABS_PTR_INIT(struct ASTVariableExpr,variableExpr);
        ACHIOR_LABS_PTR_INIT(struct ASTFunctionAttributes,attributes);
        ACHIOR_LABS_PTR_INIT(char,ident);
        
        ACHIOR_LABS_VAR_INIT(u64,identLength);


        variableExpr = expr->base->expr;
        ident        = TOKEN_GET_VALUE_DATA(*(variableExpr->ident));
        identLength  = ACHIOR_LABS_STRLEN(ident);
        entry        = HashMapGet(identMap,ident,identLength);
        attributes   = HashMapGet(&self->functionAttributes,ident,identLength);

        if(ACHIOR_LABS_NOT_NULL(attributes))
        {
            expr->attributes = attributes;
        }
        else
        {
            //exit(11);
        }
    }
    
    
}



void IdentifierResolutionCastExpr(struct IdentifierResolution *self,struct ASTCastExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    IdentifierResolutionExpression(self,expr->lhs,identMap);
}



void IdentifierResolutionAssignmentExpr(struct IdentifierResolution *self,struct ASTAssignmentExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}


void IdentifierResolutionBinaryExpr(struct IdentifierResolution *self,struct ASTBinaryExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    IdentifierResolutionExpression(self,expr->lhs,identMap);
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}



void IdentifierResolutionUnaryExpr(struct IdentifierResolution *self,struct ASTUnaryExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    
    IdentifierResolutionExpression(self,expr->rhs,identMap);
}


void IdentifierResolutionParenExpr(struct IdentifierResolution *self,struct ASTParenExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    IdentifierResolutionExpression(self,expr->expr,identMap);
}


void IdentifierResolutionVariableExpr(struct IdentifierResolution *self,struct ASTVariableExpr *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    ACHIOR_LABS_PTR_INIT(struct IdentifierEntry,entry);
    ACHIOR_LABS_PTR_INIT(struct ASTFunctionAttributes,attributes);
    ACHIOR_LABS_PTR_INIT(char,ident);
    
    ACHIOR_LABS_VAR_INIT(u64,identLength);


    ident       = TOKEN_GET_VALUE_DATA(*(expr->ident));
    identLength = ACHIOR_LABS_STRLEN(ident);
    entry       = HashMapGet(identMap,ident,identLength);

    if(ACHIOR_LABS_NULL(entry))
    {
        puts("illegal use of an undeclared variable identifier : [error] => IR");
        puts(ident);
        IdentifierResolutionFatal(self,expr->ident,"illegal use of an undeclared variable identifier  ",NULL,"variable must be declared before use",NULL,NULL);
        return;
    }

    TOKEN_SET_VALUE(*(expr->ident),entry->ident);
}



struct String IdentifierResolutionMakeTmp(struct IdentifierResolution *self)
{
    ACHIOR_LABS_STRUCT_INIT(struct String,tmp);
    ACHIOR_LABS_ARRAY_INIT(char,buf,10);
    ACHIOR_LABS_VAR_INIT(char,counter);

    StringNew(&tmp,50,self->bump);

    counter = self->globalCounter++;

    ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%lu",self->globalCounter);
    
    StringPushBack(&tmp,self->moduleName);
    StringPushBack(&tmp,"__C4C");
    StringPushBack(&tmp,buf);


    return StringReplacePathSeparators(tmp);
}
