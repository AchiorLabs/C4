#ifndef ACHIOR_LABS_AST_H
#define ACHIOR_LABS_AST_H

#include "../../Lexer/Include/Lexer.h"


struct ASTProgram;
enum ASTDeclarationKind;
struct ASTDeclaration;
enum ASTDataType;
struct ASTType;
struct ASTFunctionArgument;
struct ASTFunctionDecl;
struct ASTForeignDecl;
enum ASTStatementType;
struct ASTStatement;
struct ASTBlockStmt;
struct ASTVariableDecl;
enum ASTVariableDeclInitType;
struct ASTVariableDeclInit;
struct ASTVariableDeclSingleInit;
struct ASTReturnStmt;



enum ASTExpressionType;
struct ASTExpression;
struct ASTUnaryExpr;
enum ASTLiteralType;
struct ASTLiteralExpr;



struct ASTProgram
{
	struct LinkedList decls;
	struct HashMap identMap;
};


bool ASTProgramNew(struct ASTProgram *self,struct LinkedList decls);

enum ASTDeclarationKind
{
	AST_DECLARATION_NONE,
	AST_DECLARATION_USE,
	AST_DECLARATION_ENUM,
	AST_DECLARATION_STRUCT,
	AST_DECLARATION_UNION,
	AST_DECLARATION_IMPL,
	AST_DECLARATION_SUM,
	AST_DECLARATION_TYPE,
	AST_DECLARATION_FUNCTION,
	AST_DECLARATION_FOREIGN,
	AST_DECLARATION_VARIABLE,
};




struct ASTDeclaration
{
	enum ASTDeclarationKind kind;
	void *decl;
	bool isPublic;
};


// Accessor macros for reading ASTDeclaration fields without direct struct access

#ifndef ASTDECLARATION_GET_KIND
#define ASTDECLARATION_GET_KIND(astDeclaration) (astDeclaration).kind
#endif


#ifndef ASTDECLARATION_GET_DECL
#define ASTDECLARATION_GET_DECL(astDeclaration) (astDeclaration).decl
#endif


#ifndef ASTDECLARATION_GET_ISPUBLIC
#define ASTDECLARATION_GET_ISPUBLIC(astDeclaration) (astDeclaration).isPublic
#endif



// Mutator macros for assigning ASTDeclaration fields consistently

#ifndef ASTDECLARATION_SET_KIND
#define ASTDECLARATION_SET_KIND(astDeclaration,c4value) (astDeclaration).kind = (c4value)
#endif


#ifndef ASTDECLARATION_SET_DECL
#define ASTDECLARATION_SET_DECL(astDeclaration,c4value) (astDeclaration).decl = (c4value)
#endif


#ifndef ASTDECLARATION_SET_ISPUBLIC
#define ASTDECLARATION_SET_ISPUBLIC(astDeclaration,c4value) (astDeclaration).isPublic = (c4value)
#endif

bool ASTDeclarationNew(struct ASTDeclaration *self,enum ASTDeclarationKind kind,void *decl,bool isPublic);




enum ASTDataType
{
	AST_DATA_TYPE_NONE = 1,
	AST_DATA_TYPE_VOID,
	AST_DATA_TYPE_CHAR,
	AST_DATA_TYPE_I8,
	AST_DATA_TYPE_I16,
	AST_DATA_TYPE_I32,
	AST_DATA_TYPE_I64,
	AST_DATA_TYPE_ISIZE,
	AST_DATA_TYPE_U8,
	AST_DATA_TYPE_U16,
	AST_DATA_TYPE_U32,
	AST_DATA_TYPE_U64,
	AST_DATA_TYPE_USIZE,
	AST_DATA_TYPE_STRING,
	AST_DATA_TYPE_POINTER,
	AST_DATA_TYPE_ARRAY,
	AST_DATA_TYPE_FUNCTION,
	AST_DATA_TYPE_AGGREGATE,
	AST_DATA_TYPE_ENUM,
	AST_DATA_TYPE_STRUCT,
	AST_DATA_TYPE_UNION,
	AST_DATA_TYPE_GENERIC,
};


struct ASTStructType
{
	struct Token *ident;
	struct Layout layout;
	struct ModuleSymbol *symbol;
	struct Module *module;
};


// Accessor macros for reading ASTStructType fields without direct struct access

#ifndef ASTSTRUCTTYPE_GET_IDENT
#define ASTSTRUCTTYPE_GET_IDENT(astStructType) (astStructType).ident
#endif


#ifndef ASTSTRUCTTYPE_GET_LAYOUT
#define ASTSTRUCTTYPE_GET_LAYOUT(astStructType) (astStructType).layout
#endif


#ifndef ASTSTRUCTTYPE_GET_SYMBOL
#define ASTSTRUCTTYPE_GET_SYMBOL(astStructType) (astStructType).symbol
#endif


#ifndef ASTSTRUCTTYPE_GET_MODULE
#define ASTSTRUCTTYPE_GET_MODULE(astStructType) (astStructType).module
#endif



// Mutator macros for assigning ASTStructType fields consistently

#ifndef ASTSTRUCTTYPE_SET_IDENT
#define ASTSTRUCTTYPE_SET_IDENT(astStructType,c4value) (astStructType).ident = (c4value)
#endif


#ifndef ASTSTRUCTTYPE_SET_LAYOUT
#define ASTSTRUCTTYPE_SET_LAYOUT(astStructType,c4value) (astStructType).layout = (c4value)
#endif


#ifndef ASTSTRUCTTYPE_SET_SYMBOL
#define ASTSTRUCTTYPE_SET_SYMBOL(astStructType,c4value) (astStructType).symbol = (c4value)
#endif


#ifndef ASTSTRUCTTYPE_SET_MODULE
#define ASTSTRUCTTYPE_SET_MODULE(astStructType,c4value) (astStructType).module = (c4value)
#endif


bool ASTStructTypeNew(struct ASTStructType *self,struct Token *ident,struct Layout layout);



struct ASTAggregateType
{
	struct LinkedList path;
	struct Layout layout;
	struct ModuleSymbol *symbol;
};

// Accessor macros for reading ASTAggregateType fields without direct struct access

#ifndef ASTAGGREGATETYPE_GET_PATH
#define ASTAGGREGATETYPE_GET_PATH(astAggregateType) (astAggregateType).path
#endif


#ifndef ASTAGGREGATETYPE_GET_LAYOUT
#define ASTAGGREGATETYPE_GET_LAYOUT(astAggregateType) (astAggregateType).layout
#endif


#ifndef ASTAGGREGATETYPE_GET_SYMBOL
#define ASTAGGREGATETYPE_GET_SYMBOL(astAggregateType) (astAggregateType).symbol
#endif



// Mutator macros for assigning ASTAggregateType fields consistently

#ifndef ASTAGGREGATETYPE_SET_PATH
#define ASTAGGREGATETYPE_SET_PATH(astAggregateType,c4value) (astAggregateType).path = (c4value)
#endif


#ifndef ASTAGGREGATETYPE_SET_LAYOUT
#define ASTAGGREGATETYPE_SET_LAYOUT(astAggregateType,c4value) (astAggregateType).layout = (c4value)
#endif


#ifndef ASTAGGREGATETYPE_SET_SYMBOL
#define ASTAGGREGATETYPE_SET_SYMBOL(astAggregateType,c4value) (astAggregateType).symbol = (c4value)
#endif



bool ASTAggregateTypeNew(struct ASTAggregateType *self,struct LinkedList path);




struct ASTFunctionType
{
	struct ASTType *returnType;
	struct LinkedList arguments;
	bool hasVariableArguments;
};

// Accessor macros for reading ASTFunctionType fields without direct struct access

#ifndef ASTFUNCTIONTYPE_GET_RETURNTYPE
#define ASTFUNCTIONTYPE_GET_RETURNTYPE(astFunctionType) (astFunctionType).returnType
#endif


#ifndef ASTFUNCTIONTYPE_GET_ARGUMENTS
#define ASTFUNCTIONTYPE_GET_ARGUMENTS(astFunctionType) (astFunctionType).arguments
#endif



// Mutator macros for assigning ASTFunctionType fields consistently

#ifndef ASTFUNCTIONTYPE_SET_RETURNTYPE
#define ASTFUNCTIONTYPE_SET_RETURNTYPE(astFunctionType,c4value) (astFunctionType).returnType = (c4value)
#endif


#ifndef ASTFUNCTIONTYPE_SET_ARGUMENTS
#define ASTFUNCTIONTYPE_SET_ARGUMENTS(astFunctionType,c4value) (astFunctionType).arguments = (c4value)
#endif

bool ASTFunctionTypeNew(struct ASTFunctionType *self,struct ASTType *returnType,struct LinkedList arguments,bool hasVariableArguments);



struct ASTArrayType
{
	struct ASTType *type;
	struct ASTExpression *size;
	struct Layout layout;
};


// Accessor macros for reading ASTArrayType fields without direct struct access

#ifndef ASTARRAYTYPE_GET_TYPE
#define ASTARRAYTYPE_GET_TYPE(astArrayType) (astArrayType).type
#endif


#ifndef ASTARRAYTYPE_GET_SIZE
#define ASTARRAYTYPE_GET_SIZE(astArrayType) (astArrayType).size
#endif


#ifndef ASTARRAYTYPE_GET_LAYOUT
#define ASTARRAYTYPE_GET_LAYOUT(astArrayType) (astArrayType).layout
#endif



// Mutator macros for assigning ASTArrayType fields consistently

#ifndef ASTARRAYTYPE_SET_TYPE
#define ASTARRAYTYPE_SET_TYPE(astArrayType,c4value) (astArrayType).type = (c4value)
#endif


#ifndef ASTARRAYTYPE_SET_SIZE
#define ASTARRAYTYPE_SET_SIZE(astArrayType,c4value) (astArrayType).size = (c4value)
#endif


#ifndef ASTARRAYTYPE_SET_LAYOUT
#define ASTARRAYTYPE_SET_LAYOUT(astArrayType,c4value) (astArrayType).layout = (c4value)
#endif


bool ASTArrayTypeNew(struct ASTArrayType *self,struct ASTType *type,struct ASTExpression *size);


struct ASTPointerType
{
	struct ASTType *type;
	struct Layout layout;
};


// Accessor macros for reading ASTPointerType fields without direct struct access

#ifndef ASTPOINTERTYPE_GET_TYPE
#define ASTPOINTERTYPE_GET_TYPE(astPointerType) (astPointerType).type
#endif


#ifndef ASTPOINTERTYPE_GET_LAYOUT
#define ASTPOINTERTYPE_GET_LAYOUT(astPointerType) (astPointerType).layout
#endif



// Mutator macros for assigning ASTPointerType fields consistently

#ifndef ASTPOINTERTYPE_SET_TYPE
#define ASTPOINTERTYPE_SET_TYPE(astPointerType,c4value) (astPointerType).type = (c4value)
#endif


#ifndef ASTPOINTERTYPE_SET_LAYOUT
#define ASTPOINTERTYPE_SET_LAYOUT(astPointerType,c4value) (astPointerType).layout = (c4value)
#endif


bool ASTPointerTypeNew(struct ASTPointerType *self,struct ASTType *type);


struct ASTGenericType
{
    struct ASTType *base;        // Box, Vec, etc
    struct LinkedList args;      // ASTType*
};


bool ASTGenericTypeNew(struct ASTGenericType *self,struct ASTType *base,struct LinkedList args);



struct ASTType
{
	enum ASTDataType dataType;
	struct Layout layout;
	bool isFunction;
	void *type;
};



// Accessor macros for reading ASTType fields without direct struct access

#ifndef ASTTYPE_GET_DATATYPE
#define ASTTYPE_GET_DATATYPE(astType) (astType).dataType
#endif


#ifndef ASTTYPE_GET_LAYOUT
#define ASTTYPE_GET_LAYOUT(astType) (astType).layout
#endif


#ifndef ASTTYPE_GET_ISFUNCTION
#define ASTTYPE_GET_ISFUNCTION(astType) (astType).isFunction
#endif


#ifndef ASTTYPE_GET_TYPE
#define ASTTYPE_GET_TYPE(astType) (astType).type
#endif



// Mutator macros for assigning ASTType fields consistently

#ifndef ASTTYPE_SET_DATATYPE
#define ASTTYPE_SET_DATATYPE(astType,c4value) (astType).dataType = (c4value)
#endif


#ifndef ASTTYPE_SET_LAYOUT
#define ASTTYPE_SET_LAYOUT(astType,c4value) (astType).layout = (c4value)
#endif


#ifndef ASTTYPE_SET_ISFUNCTION
#define ASTTYPE_SET_ISFUNCTION(astType,c4value) (astType).isFunction = (c4value)
#endif


#ifndef ASTTYPE_SET_TYPE
#define ASTTYPE_SET_TYPE(astType,c4value) (astType).type = (c4value)
#endif



bool ASTTypeNew(struct ASTType *self,enum ASTDataType dataType,void *type);

/*

struct ASTFunctionAttributes
{
    struct ASTVisibility visibility;   // private/pub
    struct ASTLinkage linkage;         // normal/static/foreign
    struct ASTCodegenOptions codegen; // naked, inline, etc.
    struct ASTSymbolOptions symbol;   // link_name, no_mangle
};


future ****

*/

struct ModuleImport;

struct ASTUseDecl
{
    struct LinkedList path;
    struct Token *alias;
	struct ModuleImport *import;
};


// Accessor macros for reading ASTUseDecl fields without direct struct access

#ifndef ASTUSEDECL_GET_PATH
#define ASTUSEDECL_GET_PATH(astUseDecl) (astUseDecl).path
#endif


#ifndef ASTUSEDECL_GET_ALIAS
#define ASTUSEDECL_GET_ALIAS(astUseDecl) (astUseDecl).alias
#endif


#ifndef ASTUSEDECL_GET_IMPORT
#define ASTUSEDECL_GET_IMPORT(astUseDecl) (astUseDecl).import
#endif



// Mutator macros for assigning ASTUseDecl fields consistently

#ifndef ASTUSEDECL_SET_PATH
#define ASTUSEDECL_SET_PATH(astUseDecl,c4value) (astUseDecl).path = (c4value)
#endif


#ifndef ASTUSEDECL_SET_ALIAS
#define ASTUSEDECL_SET_ALIAS(astUseDecl,c4value) (astUseDecl).alias = (c4value)
#endif


#ifndef ASTUSEDECL_SET_IMPORT
#define ASTUSEDECL_SET_IMPORT(astUseDecl,c4value) (astUseDecl).import = (c4value)
#endif


bool ASTUseDeclNew(struct ASTUseDecl *self,struct LinkedList path,struct Token *alias);


struct ASTEnumConstant
{
	struct Token *constant;
	struct ASTExpression *expr;
};

// Accessor macros for reading ASTEnumConstant fields without direct struct access

#ifndef ASTENUMCONSTANT_GET_CONSTANT
#define ASTENUMCONSTANT_GET_CONSTANT(astEnumConstant) (astEnumConstant).constant
#endif


#ifndef ASTENUMCONSTANT_GET_EXPR
#define ASTENUMCONSTANT_GET_EXPR(astEnumConstant) (astEnumConstant).expr
#endif



// Mutator macros for assigning ASTEnumConstant fields consistently

#ifndef ASTENUMCONSTANT_SET_CONSTANT
#define ASTENUMCONSTANT_SET_CONSTANT(astEnumConstant,c4value) (astEnumConstant).constant = (c4value)
#endif


#ifndef ASTENUMCONSTANT_SET_EXPR
#define ASTENUMCONSTANT_SET_EXPR(astEnumConstant,c4value) (astEnumConstant).expr = (c4value)
#endif

bool ASTEnumConstantNew(struct ASTEnumConstant *self,struct Token *constant,struct ASTExpression *expr);


struct ASTEnumDecl
{
	struct Token *ident;
	struct LinkedList constants;
};


// Accessor macros for reading ASTEnumDecl fields without direct struct access

#ifndef ASTENUMDECL_GET_IDENT
#define ASTENUMDECL_GET_IDENT(astEnumDecl) (astEnumDecl).ident
#endif


#ifndef ASTENUMDECL_GET_CONSTANTS
#define ASTENUMDECL_GET_CONSTANTS(astEnumDecl) (astEnumDecl).constants
#endif



// Mutator macros for assigning ASTEnumDecl fields consistently

#ifndef ASTENUMDECL_SET_IDENT
#define ASTENUMDECL_SET_IDENT(astEnumDecl,c4value) (astEnumDecl).ident = (c4value)
#endif


#ifndef ASTENUMDECL_SET_CONSTANTS
#define ASTENUMDECL_SET_CONSTANTS(astEnumDecl,c4value) (astEnumDecl).constants = (c4value)
#endif

bool ASTEnumDeclNew(struct ASTEnumDecl *self,struct Token *ident,struct LinkedList constants);




struct ASTStructProperty
{
	struct ASTType *type;
	struct Token *ident;
};

// Accessor macros for reading ASTStructProperty fields without direct struct access

#ifndef ASTSTRUCTPROPERTY_GET_TYPE
#define ASTSTRUCTPROPERTY_GET_TYPE(astStructProperty) (astStructProperty).type
#endif


#ifndef ASTSTRUCTPROPERTY_GET_IDENT
#define ASTSTRUCTPROPERTY_GET_IDENT(astStructProperty) (astStructProperty).ident
#endif



// Mutator macros for assigning ASTStructProperty fields consistently

#ifndef ASTSTRUCTPROPERTY_SET_TYPE
#define ASTSTRUCTPROPERTY_SET_TYPE(astStructProperty,c4value) (astStructProperty).type = (c4value)
#endif


#ifndef ASTSTRUCTPROPERTY_SET_IDENT
#define ASTSTRUCTPROPERTY_SET_IDENT(astStructProperty,c4value) (astStructProperty).ident = (c4value)
#endif


bool ASTStructPropertyNew(struct ASTStructProperty *self,struct ASTType *type,struct Token *ident);


struct ASTStructDecl
{
	struct Token *ident;
	struct LinkedList properties;
};

// Accessor macros for reading ASTStructDecl fields without direct struct access

#ifndef ASTSTRUCTDECL_GET_IDENT
#define ASTSTRUCTDECL_GET_IDENT(astStructDecl) (astStructDecl).ident
#endif


#ifndef ASTSTRUCTDECL_GET_PROPERTIES
#define ASTSTRUCTDECL_GET_PROPERTIES(astStructDecl) (astStructDecl).properties
#endif



// Mutator macros for assigning ASTStructDecl fields consistently

#ifndef ASTSTRUCTDECL_SET_IDENT
#define ASTSTRUCTDECL_SET_IDENT(astStructDecl,c4value) (astStructDecl).ident = (c4value)
#endif


#ifndef ASTSTRUCTDECL_SET_PROPERTIES
#define ASTSTRUCTDECL_SET_PROPERTIES(astStructDecl,c4value) (astStructDecl).properties = (c4value)
#endif



bool ASTStructDeclNew(struct ASTStructDecl *self,struct Token *ident,struct LinkedList properties);



struct ASTUnionDecl
{
	struct Token *ident;
	struct LinkedList properties;
};

// Accessor macros for reading ASTUnionDecl fields without direct struct access

#ifndef ASTUNIONDECL_GET_IDENT
#define ASTUNIONDECL_GET_IDENT(astUnionDecl) (astUnionDecl).ident
#endif


#ifndef ASTUNIONDECL_GET_PROPERTIES
#define ASTUNIONDECL_GET_PROPERTIES(astUnionDecl) (astUnionDecl).properties
#endif



// Mutator macros for assigning ASTUnionDecl fields consistently

#ifndef ASTUNIONDECL_SET_IDENT
#define ASTUNIONDECL_SET_IDENT(astUnionDecl,c4value) (astUnionDecl).ident = (c4value)
#endif


#ifndef ASTUNIONDECL_SET_PROPERTIES
#define ASTUNIONDECL_SET_PROPERTIES(astUnionDecl,c4value) (astUnionDecl).properties = (c4value)
#endif

bool ASTUnionDeclNew(struct ASTUnionDecl *self,struct Token *ident,struct LinkedList properties);



struct ASTImplDecl
{
	struct Token *ident;
	struct LinkedList methods;
};

// Accessor macros for reading ASTImplDecl fields without direct struct access

#ifndef ASTIMPLDECL_GET_IDENT
#define ASTIMPLDECL_GET_IDENT(astImplDecl) (astImplDecl).ident
#endif


#ifndef ASTIMPLDECL_GET_METHODS
#define ASTIMPLDECL_GET_METHODS(astImplDecl) (astImplDecl).methods
#endif



// Mutator macros for assigning ASTImplDecl fields consistently

#ifndef ASTIMPLDECL_SET_IDENT
#define ASTIMPLDECL_SET_IDENT(astImplDecl,c4value) (astImplDecl).ident = (c4value)
#endif


#ifndef ASTIMPLDECL_SET_METHODS
#define ASTIMPLDECL_SET_METHODS(astImplDecl,c4value) (astImplDecl).methods = (c4value)
#endif


bool ASTImplDeclNew(struct ASTImplDecl *self,struct Token *ident,struct LinkedList methods);


struct ASTSumNamedField
{
    struct Token *ident;
    struct ASTType *type;
};

// Accessor macros for reading ASTSumNamedField fields without direct struct access

#ifndef ASTSUMNAMEDFIELD_GET_IDENT
#define ASTSUMNAMEDFIELD_GET_IDENT(astSumNamedField) (astSumNamedField).ident
#endif


#ifndef ASTSUMNAMEDFIELD_GET_TYPE
#define ASTSUMNAMEDFIELD_GET_TYPE(astSumNamedField) (astSumNamedField).type
#endif



// Mutator macros for assigning ASTSumNamedField fields consistently

#ifndef ASTSUMNAMEDFIELD_SET_IDENT
#define ASTSUMNAMEDFIELD_SET_IDENT(astSumNamedField,c4value) (astSumNamedField).ident = (c4value)
#endif


#ifndef ASTSUMNAMEDFIELD_SET_TYPE
#define ASTSUMNAMEDFIELD_SET_TYPE(astSumNamedField,c4value) (astSumNamedField).type = (c4value)
#endif


bool ASTSumNamedFieldNew(struct ASTSumNamedField *self,struct Token *ident,struct ASTType *type);



enum ASTSumVariantKind
{
    AST_SUM_VARIANT_NONE,
    AST_SUM_VARIANT_UNIT,
    AST_SUM_VARIANT_TUPLE,
    AST_SUM_VARIANT_STRUCT,
};


struct ASTSumVariant
{
    struct Token *ident;
    enum ASTSumVariantKind kind;
    struct LinkedList fields;
};

// Accessor macros for reading ASTSumVariant fields without direct struct access

#ifndef ASTSUMVARIANT_GET_IDENT
#define ASTSUMVARIANT_GET_IDENT(astSumVariant) (astSumVariant).ident
#endif


#ifndef ASTSUMVARIANT_GET_KIND
#define ASTSUMVARIANT_GET_KIND(astSumVariant) (astSumVariant).kind
#endif


#ifndef ASTSUMVARIANT_GET_FIELDS
#define ASTSUMVARIANT_GET_FIELDS(astSumVariant) (astSumVariant).fields
#endif



// Mutator macros for assigning ASTSumVariant fields consistently

#ifndef ASTSUMVARIANT_SET_IDENT
#define ASTSUMVARIANT_SET_IDENT(astSumVariant,c4value) (astSumVariant).ident = (c4value)
#endif


#ifndef ASTSUMVARIANT_SET_KIND
#define ASTSUMVARIANT_SET_KIND(astSumVariant,c4value) (astSumVariant).kind = (c4value)
#endif


#ifndef ASTSUMVARIANT_SET_FIELDS
#define ASTSUMVARIANT_SET_FIELDS(astSumVariant,c4value) (astSumVariant).fields = (c4value)
#endif

bool ASTSumVariantNew(struct ASTSumVariant *self,struct Token *ident,enum ASTSumVariantKind kind,struct LinkedList fields);


struct ASTSumDecl
{
    struct Token *ident;
    struct LinkedList variants;
};

// Accessor macros for reading ASTSumDecl fields without direct struct access

#ifndef ASTSUMDECL_GET_IDENT
#define ASTSUMDECL_GET_IDENT(astSumDecl) (astSumDecl).ident
#endif


#ifndef ASTSUMDECL_GET_VARIANTS
#define ASTSUMDECL_GET_VARIANTS(astSumDecl) (astSumDecl).variants
#endif



// Mutator macros for assigning ASTSumDecl fields consistently

#ifndef ASTSUMDECL_SET_IDENT
#define ASTSUMDECL_SET_IDENT(astSumDecl,c4value) (astSumDecl).ident = (c4value)
#endif


#ifndef ASTSUMDECL_SET_VARIANTS
#define ASTSUMDECL_SET_VARIANTS(astSumDecl,c4value) (astSumDecl).variants = (c4value)
#endif

bool ASTSumDeclNew(struct ASTSumDecl *self,struct Token *ident,struct LinkedList variants);


struct ASTTypeDecl
{
	struct Token *ident;
	struct ASTType *type;
};


bool ASTTypeDeclNew(struct ASTTypeDecl *self,struct Token *ident,struct ASTType *type);



struct ASTFunctionAttributes
{
    bool isPublic;
    bool isStatic;
    bool isNaked;
	bool isConstructor;

    bool isForeign;
    struct String foreignAbi;   // "C", empty if not foreign

	bool hasLinkName;
    struct String linkName;     // optional override
};


// Accessor macros for reading ASTFunctionAttributes fields without direct struct access

#ifndef ASTFUNCTIONATTRIBUTES_GET_ISPUBLIC
#define ASTFUNCTIONATTRIBUTES_GET_ISPUBLIC(astFunctionAttributes) (astFunctionAttributes).isPublic
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_ISSTATIC
#define ASTFUNCTIONATTRIBUTES_GET_ISSTATIC(astFunctionAttributes) (astFunctionAttributes).isStatic
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_ISNAKED
#define ASTFUNCTIONATTRIBUTES_GET_ISNAKED(astFunctionAttributes) (astFunctionAttributes).isNaked
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_ISCONSTRUCTOR
#define ASTFUNCTIONATTRIBUTES_GET_ISCONSTRUCTOR(astFunctionAttributes) (astFunctionAttributes).isConstructor
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_ISFOREIGN
#define ASTFUNCTIONATTRIBUTES_GET_ISFOREIGN(astFunctionAttributes) (astFunctionAttributes).isForeign
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_FOREIGNABI
#define ASTFUNCTIONATTRIBUTES_GET_FOREIGNABI(astFunctionAttributes) (astFunctionAttributes).foreignAbi
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_HASLINKNAME
#define ASTFUNCTIONATTRIBUTES_GET_HASLINKNAME(astFunctionAttributes) (astFunctionAttributes).hasLinkName
#endif


#ifndef ASTFUNCTIONATTRIBUTES_GET_LINKNAME
#define ASTFUNCTIONATTRIBUTES_GET_LINKNAME(astFunctionAttributes) (astFunctionAttributes).linkName
#endif



// Mutator macros for assigning ASTFunctionAttributes fields consistently

#ifndef ASTFUNCTIONATTRIBUTES_SET_ISPUBLIC
#define ASTFUNCTIONATTRIBUTES_SET_ISPUBLIC(astFunctionAttributes,c4value) (astFunctionAttributes).isPublic = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_ISSTATIC
#define ASTFUNCTIONATTRIBUTES_SET_ISSTATIC(astFunctionAttributes,c4value) (astFunctionAttributes).isStatic = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_ISNAKED
#define ASTFUNCTIONATTRIBUTES_SET_ISNAKED(astFunctionAttributes,c4value) (astFunctionAttributes).isNaked = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_ISCONSTRUCTOR
#define ASTFUNCTIONATTRIBUTES_SET_ISCONSTRUCTOR(astFunctionAttributes,c4value) (astFunctionAttributes).isConstructor = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_ISFOREIGN
#define ASTFUNCTIONATTRIBUTES_SET_ISFOREIGN(astFunctionAttributes,c4value) (astFunctionAttributes).isForeign = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_FOREIGNABI
#define ASTFUNCTIONATTRIBUTES_SET_FOREIGNABI(astFunctionAttributes,c4value) (astFunctionAttributes).foreignAbi = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_HASLINKNAME
#define ASTFUNCTIONATTRIBUTES_SET_HASLINKNAME(astFunctionAttributes,c4value) (astFunctionAttributes).hasLinkName = (c4value)
#endif


#ifndef ASTFUNCTIONATTRIBUTES_SET_LINKNAME
#define ASTFUNCTIONATTRIBUTES_SET_LINKNAME(astFunctionAttributes,c4value) (astFunctionAttributes).linkName = (c4value)
#endif





bool ASTFunctionAttributesNew(struct ASTFunctionAttributes *self,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name);


struct ASTFunctionArgument
{
	struct ASTType *type;
	struct Token *ident;
};


// Accessor macros for reading ASTFunctionArgument fields without direct struct access

#ifndef ASTFUNCTIONARGUMENT_GET_TYPE
#define ASTFUNCTIONARGUMENT_GET_TYPE(astFunctionArgument) (astFunctionArgument).type
#endif


#ifndef ASTFUNCTIONARGUMENT_GET_IDENT
#define ASTFUNCTIONARGUMENT_GET_IDENT(astFunctionArgument) (astFunctionArgument).ident
#endif



// Mutator macros for assigning ASTFunctionArgument fields consistently

#ifndef ASTFUNCTIONARGUMENT_SET_TYPE
#define ASTFUNCTIONARGUMENT_SET_TYPE(astFunctionArgument,c4value) (astFunctionArgument).type = (c4value)
#endif


#ifndef ASTFUNCTIONARGUMENT_SET_IDENT
#define ASTFUNCTIONARGUMENT_SET_IDENT(astFunctionArgument,c4value) (astFunctionArgument).ident = (c4value)
#endif



bool ASTFunctionArgumentNew(struct ASTFunctionArgument *self,struct ASTType *type,struct Token *ident);


struct ASTFunctionDecl
{
	struct ASTType *returnType;
	struct Token *ident;
	struct LinkedList arguments;
	struct ASTBlockStmt *block;
	struct ASTFunctionAttributes *attributes;
	bool hasVariableArguments;
	struct ModuleSymbol *symbol;
};


// Accessor macros for reading ASTFunctionDecl fields without direct struct access

#ifndef ASTFUNCTIONDECL_GET_RETURNTYPE
#define ASTFUNCTIONDECL_GET_RETURNTYPE(astFunctionDecl) (astFunctionDecl).returnType
#endif


#ifndef ASTFUNCTIONDECL_GET_IDENT
#define ASTFUNCTIONDECL_GET_IDENT(astFunctionDecl) (astFunctionDecl).ident
#endif


#ifndef ASTFUNCTIONDECL_GET_ARGUMENTS
#define ASTFUNCTIONDECL_GET_ARGUMENTS(astFunctionDecl) (astFunctionDecl).arguments
#endif


#ifndef ASTFUNCTIONDECL_GET_BLOCK
#define ASTFUNCTIONDECL_GET_BLOCK(astFunctionDecl) (astFunctionDecl).block
#endif


#ifndef ASTFUNCTIONDECL_GET_ATTRIBUTES
#define ASTFUNCTIONDECL_GET_ATTRIBUTES(astFunctionDecl) (astFunctionDecl).attributes
#endif


#ifndef ASTFUNCTIONDECL_GET_SYMBOL
#define ASTFUNCTIONDECL_GET_SYMBOL(astFunctionDecl) (astFunctionDecl).symbol
#endif



// Mutator macros for assigning ASTFunctionDecl fields consistently

#ifndef ASTFUNCTIONDECL_SET_RETURNTYPE
#define ASTFUNCTIONDECL_SET_RETURNTYPE(astFunctionDecl,c4value) (astFunctionDecl).returnType = (c4value)
#endif


#ifndef ASTFUNCTIONDECL_SET_IDENT
#define ASTFUNCTIONDECL_SET_IDENT(astFunctionDecl,c4value) (astFunctionDecl).ident = (c4value)
#endif


#ifndef ASTFUNCTIONDECL_SET_ARGUMENTS
#define ASTFUNCTIONDECL_SET_ARGUMENTS(astFunctionDecl,c4value) (astFunctionDecl).arguments = (c4value)
#endif


#ifndef ASTFUNCTIONDECL_SET_BLOCK
#define ASTFUNCTIONDECL_SET_BLOCK(astFunctionDecl,c4value) (astFunctionDecl).block = (c4value)
#endif


#ifndef ASTFUNCTIONDECL_SET_ATTRIBUTES
#define ASTFUNCTIONDECL_SET_ATTRIBUTES(astFunctionDecl,c4value) (astFunctionDecl).attributes = (c4value)
#endif


#ifndef ASTFUNCTIONDECL_SET_SYMBOL
#define ASTFUNCTIONDECL_SET_SYMBOL(astFunctionDecl,c4value) (astFunctionDecl).symbol = (c4value)
#endif



bool ASTFunctionDeclNew(struct ASTFunctionDecl *self,struct ASTType *returnType,struct Token *ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes,bool hasVariableArguments);

struct ASTForeignDecl
{
	struct LinkedList functions;
};

// Accessor macros for reading ASTForeignDecl fields without direct struct access

#ifndef ASTFOREIGNDECL_GET_FUNCTIONS
#define ASTFOREIGNDECL_GET_FUNCTIONS(astForeignDecl) (astForeignDecl).functions
#endif



// Mutator macros for assigning ASTForeignDecl fields consistently

#ifndef ASTFOREIGNDECL_SET_FUNCTIONS
#define ASTFOREIGNDECL_SET_FUNCTIONS(astForeignDecl,c4value) (astForeignDecl).functions = (c4value)
#endif

bool ASTForeignDeclNew(struct ASTForeignDecl *self,struct LinkedList functions);

enum ASTStatementKind
{
	AST_STATEMENT_NONE,
	AST_STATEMENT_RETURN,
	AST_STATEMENT_VAR_DECL,
	AST_STATEMENT_IF,
	AST_STATEMENT_WHILE,
	AST_STATEMENT_LOOP,
	AST_STATEMENT_CONTINUE,
	AST_STATEMENT_BREAK,
	AST_STATEMENT_MATCH,
	AST_STATEMENT_EXPRESSION,
};


struct ASTStatement
{
	enum ASTStatementKind kind;
	void *stmt;
};

// Accessor macros for reading ASTStatement fields without direct struct access

#ifndef ASTSTATEMENT_GET_KIND
#define ASTSTATEMENT_GET_KIND(astStatement) (astStatement).kind
#endif


#ifndef ASTSTATEMENT_GET_STMT
#define ASTSTATEMENT_GET_STMT(astStatement) (astStatement).stmt
#endif



// Mutator macros for assigning ASTStatement fields consistently

#ifndef ASTSTATEMENT_SET_KIND
#define ASTSTATEMENT_SET_KIND(astStatement,c4value) (astStatement).kind = (c4value)
#endif


#ifndef ASTSTATEMENT_SET_STMT
#define ASTSTATEMENT_SET_STMT(astStatement,c4value) (astStatement).stmt = (c4value)
#endif


bool ASTStatementNew(struct ASTStatement *self,enum ASTStatementKind type,void *stmt);


struct ASTBlockStmt
{
	struct LinkedList stmts;
};

// Accessor macros for reading ASTBlockStmt fields without direct struct access

#ifndef ASTBLOCKSTMT_GET_STMTS
#define ASTBLOCKSTMT_GET_STMTS(astBlockStmt) (astBlockStmt).stmts
#endif



// Mutator macros for assigning ASTBlockStmt fields consistently

#ifndef ASTBLOCKSTMT_SET_STMTS
#define ASTBLOCKSTMT_SET_STMTS(astBlockStmt,c4value) (astBlockStmt).stmts = (c4value)
#endif



bool ASTBlockStmtNew(struct ASTBlockStmt *self,struct LinkedList stmts);



struct ASTBreakStmt
{
	struct String label;
};


// Accessor macros for reading ASTBreakStmt fields without direct struct access

#ifndef ASTBREAKSTMT_GET_LABEL
#define ASTBREAKSTMT_GET_LABEL(astBreakStmt) (astBreakStmt).label
#endif



// Mutator macros for assigning ASTBreakStmt fields consistently

#ifndef ASTBREAKSTMT_SET_LABEL
#define ASTBREAKSTMT_SET_LABEL(astBreakStmt,c4value) (astBreakStmt).label = (c4value)
#endif


bool ASTBreakStmtNew(struct ASTBreakStmt *self);


struct ASTContinueStmt
{
	struct String label;
};

// Accessor macros for reading ASTContinueStmt fields without direct struct access

#ifndef ASTCONTINUESTMT_GET_LABEL
#define ASTCONTINUESTMT_GET_LABEL(astContinueStmt) (astContinueStmt).label
#endif



// Mutator macros for assigning ASTContinueStmt fields consistently

#ifndef ASTCONTINUESTMT_SET_LABEL
#define ASTCONTINUESTMT_SET_LABEL(astContinueStmt,c4value) (astContinueStmt).label = (c4value)
#endif

bool ASTContinueStmtNew(struct ASTContinueStmt *self);


struct ASTLoopStmt
{
	struct ASTBlockStmt *block;
	struct String label;
};

// Accessor macros for reading ASTLoopStmt fields without direct struct access

#ifndef ASTLOOPSTMT_GET_BLOCK
#define ASTLOOPSTMT_GET_BLOCK(astLoopStmt) (astLoopStmt).block
#endif


#ifndef ASTLOOPSTMT_GET_LABEL
#define ASTLOOPSTMT_GET_LABEL(astLoopStmt) (astLoopStmt).label
#endif



// Mutator macros for assigning ASTLoopStmt fields consistently

#ifndef ASTLOOPSTMT_SET_BLOCK
#define ASTLOOPSTMT_SET_BLOCK(astLoopStmt,c4value) (astLoopStmt).block = (c4value)
#endif


#ifndef ASTLOOPSTMT_SET_LABEL
#define ASTLOOPSTMT_SET_LABEL(astLoopStmt,c4value) (astLoopStmt).label = (c4value)
#endif


bool ASTLoopStmtNew(struct ASTLoopStmt *self,struct ASTBlockStmt *block);




struct ASTWhileStmt
{
	struct ASTExpression *expr;
	struct ASTBlockStmt *block;
	struct String label;
};

// Accessor macros for reading ASTWhileStmt fields without direct struct access

#ifndef ASTWHILESTMT_GET_EXPR
#define ASTWHILESTMT_GET_EXPR(astWhileStmt) (astWhileStmt).expr
#endif


#ifndef ASTWHILESTMT_GET_BLOCK
#define ASTWHILESTMT_GET_BLOCK(astWhileStmt) (astWhileStmt).block
#endif


#ifndef ASTWHILESTMT_GET_LABEL
#define ASTWHILESTMT_GET_LABEL(astWhileStmt) (astWhileStmt).label
#endif



// Mutator macros for assigning ASTWhileStmt fields consistently

#ifndef ASTWHILESTMT_SET_EXPR
#define ASTWHILESTMT_SET_EXPR(astWhileStmt,c4value) (astWhileStmt).expr = (c4value)
#endif


#ifndef ASTWHILESTMT_SET_BLOCK
#define ASTWHILESTMT_SET_BLOCK(astWhileStmt,c4value) (astWhileStmt).block = (c4value)
#endif


#ifndef ASTWHILESTMT_SET_LABEL
#define ASTWHILESTMT_SET_LABEL(astWhileStmt,c4value) (astWhileStmt).label = (c4value)
#endif


bool ASTWhileStmtNew(struct ASTWhileStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block);



struct ASTIfElse
{
	struct ASTBlockStmt *block;
};


// Accessor macros for reading ASTIfElse fields without direct struct access

#ifndef ASTIFELSE_GET_BLOCK
#define ASTIFELSE_GET_BLOCK(astIfElse) (astIfElse).block
#endif



// Mutator macros for assigning ASTIfElse fields consistently

#ifndef ASTIFELSE_SET_BLOCK
#define ASTIFELSE_SET_BLOCK(astIfElse,c4value) (astIfElse).block = (c4value)
#endif


bool ASTIfElseNew(struct ASTIfElse *self,struct ASTBlockStmt *block);


struct ASTIfElif
{
	struct ASTExpression *expr;
	struct ASTBlockStmt *block;
};

// Accessor macros for reading ASTIfElif fields without direct struct access

#ifndef ASTIFELIF_GET_EXPR
#define ASTIFELIF_GET_EXPR(astIfElif) (astIfElif).expr
#endif


#ifndef ASTIFELIF_GET_BLOCK
#define ASTIFELIF_GET_BLOCK(astIfElif) (astIfElif).block
#endif



// Mutator macros for assigning ASTIfElif fields consistently

#ifndef ASTIFELIF_SET_EXPR
#define ASTIFELIF_SET_EXPR(astIfElif,c4value) (astIfElif).expr = (c4value)
#endif


#ifndef ASTIFELIF_SET_BLOCK
#define ASTIFELIF_SET_BLOCK(astIfElif,c4value) (astIfElif).block = (c4value)
#endif


bool ASTIfElifNew(struct ASTIfElif *self,struct ASTExpression *expr,struct ASTBlockStmt *block);

struct ASTIfStmt
{
	struct ASTExpression *expr;
	struct ASTBlockStmt *block;
	struct LinkedList  elifs;
	struct ASTIfElse *elseBlock;
};


// Accessor macros for reading ASTIfStmt fields without direct struct access

#ifndef ASTIFSTMT_GET_EXPR
#define ASTIFSTMT_GET_EXPR(astIfStmt) (astIfStmt).expr
#endif


#ifndef ASTIFSTMT_GET_BLOCK
#define ASTIFSTMT_GET_BLOCK(astIfStmt) (astIfStmt).block
#endif


#ifndef ASTIFSTMT_GET_ELIFS
#define ASTIFSTMT_GET_ELIFS(astIfStmt) (astIfStmt).elifs
#endif


#ifndef ASTIFSTMT_GET_ELSEBLOCK
#define ASTIFSTMT_GET_ELSEBLOCK(astIfStmt) (astIfStmt).elseBlock
#endif



// Mutator macros for assigning ASTIfStmt fields consistently

#ifndef ASTIFSTMT_SET_EXPR
#define ASTIFSTMT_SET_EXPR(astIfStmt,c4value) (astIfStmt).expr = (c4value)
#endif


#ifndef ASTIFSTMT_SET_BLOCK
#define ASTIFSTMT_SET_BLOCK(astIfStmt,c4value) (astIfStmt).block = (c4value)
#endif


#ifndef ASTIFSTMT_SET_ELIFS
#define ASTIFSTMT_SET_ELIFS(astIfStmt,c4value) (astIfStmt).elifs = (c4value)
#endif


#ifndef ASTIFSTMT_SET_ELSEBLOCK
#define ASTIFSTMT_SET_ELSEBLOCK(astIfStmt,c4value) (astIfStmt).elseBlock = (c4value)
#endif



bool ASTIfStmtNew(struct ASTIfStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList  elifs,struct ASTIfElse *elseBlock);


struct ASTVariableDecl
{
	bool isConstant;
	struct ASTType *type;
	struct Token *ident;
	struct ASTVariableDeclInit *init;
};


// Accessor macros for reading ASTVariableDecl fields without direct struct access

#ifndef ASTVARIABLEDECL_GET_TYPE
#define ASTVARIABLEDECL_GET_TYPE(astVariableDecl) (astVariableDecl).type
#endif


#ifndef ASTVARIABLEDECL_GET_IDENT
#define ASTVARIABLEDECL_GET_IDENT(astVariableDecl) (astVariableDecl).ident
#endif


#ifndef ASTVARIABLEDECL_GET_INIT
#define ASTVARIABLEDECL_GET_INIT(astVariableDecl) (astVariableDecl).init
#endif



// Mutator macros for assigning ASTVariableDecl fields consistently

#ifndef ASTVARIABLEDECL_SET_TYPE
#define ASTVARIABLEDECL_SET_TYPE(astVariableDecl,c4value) (astVariableDecl).type = (c4value)
#endif


#ifndef ASTVARIABLEDECL_SET_IDENT
#define ASTVARIABLEDECL_SET_IDENT(astVariableDecl,c4value) (astVariableDecl).ident = (c4value)
#endif


#ifndef ASTVARIABLEDECL_SET_INIT
#define ASTVARIABLEDECL_SET_INIT(astVariableDecl,c4value) (astVariableDecl).init = (c4value)
#endif


bool ASTVariableDeclNew(struct ASTVariableDecl *self,bool isConstant,struct ASTType *type,struct Token *ident,struct ASTVariableDeclInit *init);

enum ASTVariableDeclInitKind
{
	AST_VAR_DECL_INIT_NONE,
	AST_VAR_DECL_INIT_SINGLE_INIT,
	AST_VAR_DECL_INIT_ARRAY_INIT,
};

struct ASTVariableDeclInit
{
	enum ASTVariableDeclInitKind kind;
	void *init;
};

// Accessor macros for reading ASTVariableDeclInit fields without direct struct access

#ifndef ASTVARIABLEDECLINIT_GET_INITKIND
#define ASTVARIABLEDECLINIT_GET_INITKIND(astVariableDeclInit) (astVariableDeclInit).kind
#endif


#ifndef ASTVARIABLEDECLINIT_GET_INIT
#define ASTVARIABLEDECLINIT_GET_INIT(astVariableDeclInit) (astVariableDeclInit).init
#endif



// Mutator macros for assigning ASTVariableDeclInit fields consistently

#ifndef ASTVARIABLEDECLINIT_SET_INITKIND
#define ASTVARIABLEDECLINIT_SET_INITKIND(astVariableDeclInit,c4value) (astVariableDeclInit).kind = (c4value)
#endif


#ifndef ASTVARIABLEDECLINIT_SET_INIT
#define ASTVARIABLEDECLINIT_SET_INIT(astVariableDeclInit,c4value) (astVariableDeclInit).init = (c4value)
#endif


bool ASTVariableDeclInitNew(struct ASTVariableDeclInit *self,enum ASTVariableDeclInitKind kind,void *init);


struct ASTVariableDeclSingleInit
{
	struct ASTExpression *expr;
};

// Accessor macros for reading ASTVariableDeclSingleInit fields without direct struct access

#ifndef ASTVARIABLEDECLSINGLEINIT_GET_EXPR
#define ASTVARIABLEDECLSINGLEINIT_GET_EXPR(astVariableDeclSingleInit) (astVariableDeclSingleInit).expr
#endif



// Mutator macros for assigning ASTVariableDeclSingleInit fields consistently

#ifndef ASTVARIABLEDECLSINGLEINIT_SET_EXPR
#define ASTVARIABLEDECLSINGLEINIT_SET_EXPR(astVariableDeclSingleInit,c4value) (astVariableDeclSingleInit).expr = (c4value)
#endif


bool ASTVariableDeclSingleInitNew(struct ASTVariableDeclSingleInit *self,struct ASTExpression *expr);



struct ASTVariableDeclArrayInit
{
	struct LinkedList elements;
};

// Accessor macros for reading ASTVariableDeclArrayInit fields without direct struct access

#ifndef ASTVARIABLEDECLARRAYINIT_GET_ELEMENTS
#define ASTVARIABLEDECLARRAYINIT_GET_ELEMENTS(astVariableDeclArrayInit) (astVariableDeclArrayInit).elements
#endif



// Mutator macros for assigning ASTVariableDeclArrayInit fields consistently

#ifndef ASTVARIABLEDECLARRAYINIT_SET_ELEMENTS
#define ASTVARIABLEDECLARRAYINIT_SET_ELEMENTS(astVariableDeclArrayInit,c4value) (astVariableDeclArrayInit).elements = (c4value)
#endif

bool ASTVariableDeclArrayInitNew(struct ASTVariableDeclArrayInit *self,struct LinkedList elements);


struct ASTReturnStmt
{
	struct ASTExpression *expr;
};


// Accessor macros for reading ASTReturnStmt fields without direct struct access

#ifndef ASTRETURNSTMT_GET_EXPR
#define ASTRETURNSTMT_GET_EXPR(astReturnStmt) (astReturnStmt).expr
#endif



// Mutator macros for assigning ASTReturnStmt fields consistently

#ifndef ASTRETURNSTMT_SET_EXPR
#define ASTRETURNSTMT_SET_EXPR(astReturnStmt,c4value) (astReturnStmt).expr = (c4value)
#endif


bool ASTReturnStmtNew(struct ASTReturnStmt *self,struct ASTExpression *expr);



enum ASTPatternKind
{
    AST_PATTERN_LITERAL,
    AST_PATTERN_IDENTIFIER,
    AST_PATTERN_ENUM,
    AST_PATTERN_SUM_SINGLE,
    AST_PATTERN_SUM_TUPLE,
    AST_PATTERN_SUM_STRUCT,
    AST_PATTERN_STRUCT,
    AST_PATTERN_TUPLE,
    AST_PATTERN_WILDCARD
};


struct ASTPattern
{
    enum ASTPatternKind kind;
    struct Token *ident;
    struct LinkedList bindings;
};


// Accessor macros for reading ASTPattern fields without direct struct access

#ifndef ASTPATTERN_GET_KIND
#define ASTPATTERN_GET_KIND(astPattern) (astPattern).kind
#endif


#ifndef ASTPATTERN_GET_IDENT
#define ASTPATTERN_GET_IDENT(astPattern) (astPattern).ident
#endif


#ifndef ASTPATTERN_GET_BINDINGS
#define ASTPATTERN_GET_BINDINGS(astPattern) (astPattern).bindings
#endif



// Mutator macros for assigning ASTPattern fields consistently

#ifndef ASTPATTERN_SET_KIND
#define ASTPATTERN_SET_KIND(astPattern,c4value) (astPattern).kind = (c4value)
#endif


#ifndef ASTPATTERN_SET_IDENT
#define ASTPATTERN_SET_IDENT(astPattern,c4value) (astPattern).ident = (c4value)
#endif


#ifndef ASTPATTERN_SET_BINDINGS
#define ASTPATTERN_SET_BINDINGS(astPattern,c4value) (astPattern).bindings = (c4value)
#endif

bool ASTPatternNew(struct ASTPattern *self,enum ASTPatternKind kind,struct Token *ident,struct LinkedList bindings);


struct ASTMatchArm
{
    struct ASTPattern *pattern;
    struct ASTBlockStmt *stmt;
};

// Accessor macros for reading ASTMatchArm fields without direct struct access

#ifndef ASTMATCHARM_GET_PATTERN
#define ASTMATCHARM_GET_PATTERN(astMatchArm) (astMatchArm).pattern
#endif


#ifndef ASTMATCHARM_GET_STMT
#define ASTMATCHARM_GET_STMT(astMatchArm) (astMatchArm).stmt
#endif



// Mutator macros for assigning ASTMatchArm fields consistently

#ifndef ASTMATCHARM_SET_PATTERN
#define ASTMATCHARM_SET_PATTERN(astMatchArm,c4value) (astMatchArm).pattern = (c4value)
#endif


#ifndef ASTMATCHARM_SET_STMT
#define ASTMATCHARM_SET_STMT(astMatchArm,c4value) (astMatchArm).stmt = (c4value)
#endif


bool ASTMatchArmNew(struct ASTMatchArm *self,struct ASTPattern *pattern,struct ASTBlockStmt*stmt);



struct ASTMatchStmt
{
    struct ASTExpression *expr;
    struct LinkedList arms;
};


// Accessor macros for reading ASTMatchStmt fields without direct struct access

#ifndef ASTMATCHSTMT_GET_EXPR
#define ASTMATCHSTMT_GET_EXPR(astMatchStmt) (astMatchStmt).expr
#endif


#ifndef ASTMATCHSTMT_GET_ARMS
#define ASTMATCHSTMT_GET_ARMS(astMatchStmt) (astMatchStmt).arms
#endif



// Mutator macros for assigning ASTMatchStmt fields consistently

#ifndef ASTMATCHSTMT_SET_EXPR
#define ASTMATCHSTMT_SET_EXPR(astMatchStmt,c4value) (astMatchStmt).expr = (c4value)
#endif


#ifndef ASTMATCHSTMT_SET_ARMS
#define ASTMATCHSTMT_SET_ARMS(astMatchStmt,c4value) (astMatchStmt).arms = (c4value)
#endif


bool ASTMatchStmtNew(struct ASTMatchStmt *self,struct ASTExpression *expr,struct LinkedList arms);


enum ASTExpressionKind
{
	AST_EXPRESSION_NONE,
	AST_EXPRESSION_LITERAL,
	AST_EXPRESSION_VARIABLE,
	AST_EXPRESSION_PAREN,
	AST_EXPRESSION_UNARY,
	AST_EXPRESSION_BINARY,
	AST_EXPRESSION_ASSIGNMENT,
	AST_EXPRESSION_CAST,
	AST_EXPRESSION_FUNCTION_CALL,
	AST_EXPRESSION_ADDRESS_OF,
	AST_EXPRESSION_PTR_READ,
	AST_EXPRESSION_PTR_WRITE,
	AST_EXPRESSION_PTR_OFFSET,
	AST_EXPRESSION_PTR_BYTE_OFFSET,
	AST_EXPRESSION_PTR_ADVANCE,
	AST_EXPRESSION_PTR_DIFF,
	AST_EXPRESSION_SUBSCRIPT,
	AST_EXPRESSION_AS_PTR,
	AST_EXPRESSION_LEN,
	AST_EXPRESSION_STRUCT_ACCESS,
	AST_EXPRESSION_STRUCT_POINTER_ACCESS,
	AST_EXPRESSION_METHOD,
	AST_EXPRESSION_PATH,
};



struct ASTExpression
{
	enum ASTExpressionKind kind;
	void *expr;
	struct ASTType *baseType;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTExpression fields without direct struct access

#ifndef ASTEXPRESSION_GET_KIND
#define ASTEXPRESSION_GET_KIND(astExpression) (astExpression).kind
#endif


#ifndef ASTEXPRESSION_GET_EXPR
#define ASTEXPRESSION_GET_EXPR(astExpression) (astExpression).expr
#endif


#ifndef ASTEXPRESSION_GET_BASETYPE
#define ASTEXPRESSION_GET_BASETYPE(astExpression) (astExpression).baseType
#endif


#ifndef ASTEXPRESSION_GET_DATATYPE
#define ASTEXPRESSION_GET_DATATYPE(astExpression) (astExpression).dataType
#endif



// Mutator macros for assigning ASTExpression fields consistently

#ifndef ASTEXPRESSION_SET_KIND
#define ASTEXPRESSION_SET_KIND(astExpression,c4value) (astExpression).kind = (c4value)
#endif


#ifndef ASTEXPRESSION_SET_EXPR
#define ASTEXPRESSION_SET_EXPR(astExpression,c4value) (astExpression).expr = (c4value)
#endif


#ifndef ASTEXPRESSION_SET_BASETYPE
#define ASTEXPRESSION_SET_BASETYPE(astExpression,c4value) (astExpression).baseType = (c4value)
#endif


#ifndef ASTEXPRESSION_SET_DATATYPE
#define ASTEXPRESSION_SET_DATATYPE(astExpression,c4value) (astExpression).dataType = (c4value)
#endif


bool ASTExpressionNew(struct ASTExpression *self,enum ASTExpressionKind kind,void *expr);

enum ASTLiteralKind
{
	AST_LITERAL_NONE,
	AST_LITERAL_I32,
	AST_LITERAL_I64,
	AST_LITERAL_U32,
	AST_LITERAL_U64,
	AST_LITERAL_CHARACTER,
	AST_LITERAL_STRING,
};


struct ASTLiteralExpr
{
	enum ASTLiteralKind kind;
	struct Token *literal;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTLiteralExpr fields without direct struct access

#ifndef ASTLITERALEXPR_GET_KIND
#define ASTLITERALEXPR_GET_KIND(astLiteralExpr) (astLiteralExpr).kind
#endif


#ifndef ASTLITERALEXPR_GET_LITERAL
#define ASTLITERALEXPR_GET_LITERAL(astLiteralExpr) (astLiteralExpr).literal
#endif


#ifndef ASTLITERALEXPR_GET_DATATYPE
#define ASTLITERALEXPR_GET_DATATYPE(astLiteralExpr) (astLiteralExpr).dataType
#endif



// Mutator macros for assigning ASTLiteralExpr fields consistently

#ifndef ASTLITERALEXPR_SET_KIND
#define ASTLITERALEXPR_SET_KIND(astLiteralExpr,c4value) (astLiteralExpr).kind = (c4value)
#endif


#ifndef ASTLITERALEXPR_SET_LITERAL
#define ASTLITERALEXPR_SET_LITERAL(astLiteralExpr,c4value) (astLiteralExpr).literal = (c4value)
#endif


#ifndef ASTLITERALEXPR_SET_DATATYPE
#define ASTLITERALEXPR_SET_DATATYPE(astLiteralExpr,c4value) (astLiteralExpr).dataType = (c4value)
#endif


bool ASTLiteralExprNew(struct ASTLiteralExpr *self,enum ASTLiteralKind kind,struct Token *literal);



struct ASTVariableExpr
{
	struct Token *ident;
	struct ASTType *baseType;
	struct ASTType *dataType;
	struct ModuleSymbol *symbol;
};

// Accessor macros for reading ASTVariableExpr fields without direct struct access

#ifndef ASTVARIABLEEXPR_GET_IDENT
#define ASTVARIABLEEXPR_GET_IDENT(astVariableExpr) (astVariableExpr).ident
#endif


#ifndef ASTVARIABLEEXPR_GET_BASETYPE
#define ASTVARIABLEEXPR_GET_BASETYPE(astVariableExpr) (astVariableExpr).baseType
#endif


#ifndef ASTVARIABLEEXPR_GET_DATATYPE
#define ASTVARIABLEEXPR_GET_DATATYPE(astVariableExpr) (astVariableExpr).dataType
#endif


#ifndef ASTVARIABLEEXPR_GET_SYMBOL
#define ASTVARIABLEEXPR_GET_SYMBOL(astVariableExpr) (astVariableExpr).symbol
#endif



// Mutator macros for assigning ASTVariableExpr fields consistently

#ifndef ASTVARIABLEEXPR_SET_IDENT
#define ASTVARIABLEEXPR_SET_IDENT(astVariableExpr,c4value) (astVariableExpr).ident = (c4value)
#endif


#ifndef ASTVARIABLEEXPR_SET_BASETYPE
#define ASTVARIABLEEXPR_SET_BASETYPE(astVariableExpr,c4value) (astVariableExpr).baseType = (c4value)
#endif


#ifndef ASTVARIABLEEXPR_SET_DATATYPE
#define ASTVARIABLEEXPR_SET_DATATYPE(astVariableExpr,c4value) (astVariableExpr).dataType = (c4value)
#endif


#ifndef ASTVARIABLEEXPR_SET_SYMBOL
#define ASTVARIABLEEXPR_SET_SYMBOL(astVariableExpr,c4value) (astVariableExpr).symbol = (c4value)
#endif


bool ASTVariableExprNew(struct ASTVariableExpr *self,struct Token *ident);


struct ASTParenExpr
{
	struct ASTExpression *expr;
	struct ASTType *dataType;
};


bool ASTParenExprNew(struct ASTParenExpr *self,struct ASTExpression *expr);



enum ASTUnaryOperator
{
	AST_UNARY_OPERATOR_NONE,
	AST_UNARY_OPERATOR_COMPLEMENT,
	AST_UNARY_OPERATOR_NEGATE,
};


struct ASTUnaryExpr
{
	enum ASTUnaryOperator op;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTUnaryExpr fields without direct struct access

#ifndef ASTUNARYEXPR_GET_OP
#define ASTUNARYEXPR_GET_OP(astUnaryExpr) (astUnaryExpr).op
#endif


#ifndef ASTUNARYEXPR_GET_RHS
#define ASTUNARYEXPR_GET_RHS(astUnaryExpr) (astUnaryExpr).rhs
#endif


#ifndef ASTUNARYEXPR_GET_DATATYPE
#define ASTUNARYEXPR_GET_DATATYPE(astUnaryExpr) (astUnaryExpr).dataType
#endif



// Mutator macros for assigning ASTUnaryExpr fields consistently

#ifndef ASTUNARYEXPR_SET_OP
#define ASTUNARYEXPR_SET_OP(astUnaryExpr,c4value) (astUnaryExpr).op = (c4value)
#endif


#ifndef ASTUNARYEXPR_SET_RHS
#define ASTUNARYEXPR_SET_RHS(astUnaryExpr,c4value) (astUnaryExpr).rhs = (c4value)
#endif


#ifndef ASTUNARYEXPR_SET_DATATYPE
#define ASTUNARYEXPR_SET_DATATYPE(astUnaryExpr,c4value) (astUnaryExpr).dataType = (c4value)
#endif

bool ASTUnaryExprNew(struct ASTUnaryExpr *self,enum ASTUnaryOperator op,struct ASTExpression *rhs);




enum ASTPrecedence
{
    AST_PRECEDENCE_NONE         = 0, 
    AST_PRECEDENCE_COMMA        = 1,  
    AST_PRECEDENCE_ASSIGN       = 2,   
    AST_PRECEDENCE_OR_LOGICAL   = 3,  
    AST_PRECEDENCE_AND_LOGICAL  = 4,  
    AST_PRECEDENCE_OR_BITWISE   = 5,   
    AST_PRECEDENCE_XOR_BITWISE  = 6,  
    AST_PRECEDENCE_AND_BITWISE  = 7, 
    AST_PRECEDENCE_EQUALITY     = 8, 
    AST_PRECEDENCE_RELATIONAL   = 9,  
    AST_PRECEDENCE_SHIFT        = 10,  
    AST_PRECEDENCE_ADD          = 11, 
    AST_PRECEDENCE_MUL          = 12, 
	AST_PRECEDENCE_AS           = 13,
};


enum ASTBinaryOperator
{
	AST_BINARY_OPERATOR_NONE,
	AST_BINARY_OPERATOR_ADD,
	AST_BINARY_OPERATOR_SUB,
	AST_BINARY_OPERATOR_MUL,
	AST_BINARY_OPERATOR_DIV,
	AST_BINARY_OPERATOR_MOD,
	AST_BINARY_OPERATOR_LESS,
	AST_BINARY_OPERATOR_LESS_EQUAL,
	AST_BINARY_OPERATOR_GREATER,
	AST_BINARY_OPERATOR_GREATER_EQUAL,
	AST_BINARY_OPERATOR_EQUAL,
	AST_BINARY_OPERATOR_NOT_EQUAL,
	AST_BINARY_OPERATOR_AND,
	AST_BINARY_OPERATOR_OR,
	AST_BINARY_OPERATOR_BITWISE_AND,
	AST_BINARY_OPERATOR_BITWISE_OR,
	AST_BINARY_OPERATOR_BITWISE_LEFT_SHIFT,
	AST_BINARY_OPERATOR_BITWISE_RIGHT_SHIFT,
};


struct ASTBinaryExpr
{
	struct ASTExpression *lhs;
	enum ASTBinaryOperator op;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTBinaryExpr fields without direct struct access

#ifndef ASTBINARYEXPR_GET_LHS
#define ASTBINARYEXPR_GET_LHS(astBinaryExpr) (astBinaryExpr).lhs
#endif


#ifndef ASTBINARYEXPR_GET_OP
#define ASTBINARYEXPR_GET_OP(astBinaryExpr) (astBinaryExpr).op
#endif


#ifndef ASTBINARYEXPR_GET_RHS
#define ASTBINARYEXPR_GET_RHS(astBinaryExpr) (astBinaryExpr).rhs
#endif


#ifndef ASTBINARYEXPR_GET_DATATYPE
#define ASTBINARYEXPR_GET_DATATYPE(astBinaryExpr) (astBinaryExpr).dataType
#endif



// Mutator macros for assigning ASTBinaryExpr fields consistently

#ifndef ASTBINARYEXPR_SET_LHS
#define ASTBINARYEXPR_SET_LHS(astBinaryExpr,c4value) (astBinaryExpr).lhs = (c4value)
#endif


#ifndef ASTBINARYEXPR_SET_OP
#define ASTBINARYEXPR_SET_OP(astBinaryExpr,c4value) (astBinaryExpr).op = (c4value)
#endif


#ifndef ASTBINARYEXPR_SET_RHS
#define ASTBINARYEXPR_SET_RHS(astBinaryExpr,c4value) (astBinaryExpr).rhs = (c4value)
#endif


#ifndef ASTBINARYEXPR_SET_DATATYPE
#define ASTBINARYEXPR_SET_DATATYPE(astBinaryExpr,c4value) (astBinaryExpr).dataType = (c4value)
#endif

bool ASTBinaryExprNew(struct ASTBinaryExpr *self,struct ASTExpression *lhs,enum ASTBinaryOperator op,struct ASTExpression *rhs);

enum ASTAssignmentOperator
{
	AST_ASSIGNMENT_OPERATOR_NONE,
	AST_ASSIGNMENT_OPERATOR,
	AST_ASSIGNMENT_OPERATOR_ADD,
	AST_ASSIGNMENT_OPERATOR_SUB,
	AST_ASSIGNMENT_OPERATOR_MUL,
	AST_ASSIGNMENT_OPERATOR_DIV,
	AST_ASSIGNMENT_OPERATOR_MOD,
};

struct ASTAssignmentExpr
{
	struct ASTExpression *lhs;
	enum ASTAssignmentOperator op;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTAssignmentExpr fields without direct struct access

#ifndef ASTASSIGNMENTEXPR_GET_LHS
#define ASTASSIGNMENTEXPR_GET_LHS(astAssignmentExpr) (astAssignmentExpr).lhs
#endif


#ifndef ASTASSIGNMENTEXPR_GET_OP
#define ASTASSIGNMENTEXPR_GET_OP(astAssignmentExpr) (astAssignmentExpr).op
#endif


#ifndef ASTASSIGNMENTEXPR_GET_RHS
#define ASTASSIGNMENTEXPR_GET_RHS(astAssignmentExpr) (astAssignmentExpr).rhs
#endif


#ifndef ASTASSIGNMENTEXPR_GET_DATATYPE
#define ASTASSIGNMENTEXPR_GET_DATATYPE(astAssignmentExpr) (astAssignmentExpr).dataType
#endif



// Mutator macros for assigning ASTAssignmentExpr fields consistently

#ifndef ASTASSIGNMENTEXPR_SET_LHS
#define ASTASSIGNMENTEXPR_SET_LHS(astAssignmentExpr,c4value) (astAssignmentExpr).lhs = (c4value)
#endif


#ifndef ASTASSIGNMENTEXPR_SET_OP
#define ASTASSIGNMENTEXPR_SET_OP(astAssignmentExpr,c4value) (astAssignmentExpr).op = (c4value)
#endif


#ifndef ASTASSIGNMENTEXPR_SET_RHS
#define ASTASSIGNMENTEXPR_SET_RHS(astAssignmentExpr,c4value) (astAssignmentExpr).rhs = (c4value)
#endif


#ifndef ASTASSIGNMENTEXPR_SET_DATATYPE
#define ASTASSIGNMENTEXPR_SET_DATATYPE(astAssignmentExpr,c4value) (astAssignmentExpr).dataType = (c4value)
#endif

bool ASTAssignmentExprNew(struct ASTAssignmentExpr *self,struct ASTExpression *lhs,enum ASTAssignmentOperator op,struct ASTExpression *rhs);


enum ASTCastOperator
{
	AST_CAST_OPERATOR_NONE,
	AST_CAST_OPERATOR_WIDEN,
	AST_CAST_OPERATOR_NARROW,
};

struct ASTCastExpr
{
	struct ASTExpression *lhs;
	enum ASTCastOperator op;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTCastExpr fields without direct struct access

#ifndef ASTCASTEXPR_GET_LHS
#define ASTCASTEXPR_GET_LHS(astCastExpr) (astCastExpr).lhs
#endif


#ifndef ASTCASTEXPR_GET_OP
#define ASTCASTEXPR_GET_OP(astCastExpr) (astCastExpr).op
#endif


#ifndef ASTCASTEXPR_GET_DATATYPE
#define ASTCASTEXPR_GET_DATATYPE(astCastExpr) (astCastExpr).dataType
#endif



// Mutator macros for assigning ASTCastExpr fields consistently

#ifndef ASTCASTEXPR_SET_LHS
#define ASTCASTEXPR_SET_LHS(astCastExpr,c4value) (astCastExpr).lhs = (c4value)
#endif


#ifndef ASTCASTEXPR_SET_OP
#define ASTCASTEXPR_SET_OP(astCastExpr,c4value) (astCastExpr).op = (c4value)
#endif


#ifndef ASTCASTEXPR_SET_DATATYPE
#define ASTCASTEXPR_SET_DATATYPE(astCastExpr,c4value) (astCastExpr).dataType = (c4value)
#endif

bool ASTCastExprNew(struct ASTCastExpr *self,struct ASTExpression *lhs,enum ASTCastOperator op,struct ASTType *dataType);

struct ASTFunctionCallExpr
{
	struct ASTExpression *base;
	struct LinkedList arguments;
	struct ASTFunctionAttributes *attributes;
	struct ModuleSymbol *symbol;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTFunctionCallExpr fields without direct struct access

#ifndef ASTFUNCTIONCALLEXPR_GET_BASE
#define ASTFUNCTIONCALLEXPR_GET_BASE(astFunctionCallExpr) (astFunctionCallExpr).base
#endif


#ifndef ASTFUNCTIONCALLEXPR_GET_ARGUMENTS
#define ASTFUNCTIONCALLEXPR_GET_ARGUMENTS(astFunctionCallExpr) (astFunctionCallExpr).arguments
#endif


#ifndef ASTFUNCTIONCALLEXPR_GET_ATTRIBUTES
#define ASTFUNCTIONCALLEXPR_GET_ATTRIBUTES(astFunctionCallExpr) (astFunctionCallExpr).attributes
#endif


#ifndef ASTFUNCTIONCALLEXPR_GET_SYMBOL
#define ASTFUNCTIONCALLEXPR_GET_SYMBOL(astFunctionCallExpr) (astFunctionCallExpr).symbol
#endif


#ifndef ASTFUNCTIONCALLEXPR_GET_DATATYPE
#define ASTFUNCTIONCALLEXPR_GET_DATATYPE(astFunctionCallExpr) (astFunctionCallExpr).dataType
#endif



// Mutator macros for assigning ASTFunctionCallExpr fields consistently

#ifndef ASTFUNCTIONCALLEXPR_SET_BASE
#define ASTFUNCTIONCALLEXPR_SET_BASE(astFunctionCallExpr,c4value) (astFunctionCallExpr).base = (c4value)
#endif


#ifndef ASTFUNCTIONCALLEXPR_SET_ARGUMENTS
#define ASTFUNCTIONCALLEXPR_SET_ARGUMENTS(astFunctionCallExpr,c4value) (astFunctionCallExpr).arguments = (c4value)
#endif


#ifndef ASTFUNCTIONCALLEXPR_SET_ATTRIBUTES
#define ASTFUNCTIONCALLEXPR_SET_ATTRIBUTES(astFunctionCallExpr,c4value) (astFunctionCallExpr).attributes = (c4value)
#endif


#ifndef ASTFUNCTIONCALLEXPR_SET_SYMBOL
#define ASTFUNCTIONCALLEXPR_SET_SYMBOL(astFunctionCallExpr,c4value) (astFunctionCallExpr).symbol = (c4value)
#endif


#ifndef ASTFUNCTIONCALLEXPR_SET_DATATYPE
#define ASTFUNCTIONCALLEXPR_SET_DATATYPE(astFunctionCallExpr,c4value) (astFunctionCallExpr).dataType = (c4value)
#endif


bool ASTFunctionCallExprNew(struct ASTFunctionCallExpr *self,struct ASTExpression *base,struct LinkedList arguments);





struct ASTAddressOfExpr
{
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTAddressOfExpr fields without direct struct access

#ifndef ASTADDRESSEDEXPR_GET_RHS
#define ASTADDRESSEDEXPR_GET_RHS(astAddressOfExpr) (astAddressOfExpr).rhs
#endif


#ifndef ASTADDRESSEDEXPR_GET_DATATYPE
#define ASTADDRESSEDEXPR_GET_DATATYPE(astAddressOfExpr) (astAddressOfExpr).dataType
#endif



// Mutator macros for assigning ASTAddressOfExpr fields consistently

#ifndef ASTADDRESSEDEXPR_SET_RHS
#define ASTADDRESSEDEXPR_SET_RHS(astAddressOfExpr,c4value) (astAddressOfExpr).rhs = (c4value)
#endif


#ifndef ASTADDRESSEDEXPR_SET_DATATYPE
#define ASTADDRESSEDEXPR_SET_DATATYPE(astAddressOfExpr,c4value) (astAddressOfExpr).dataType = (c4value)
#endif

bool ASTAddressOfExprNew(struct ASTAddressOfExpr *self,struct ASTExpression *rhs);



struct ASTPtrReadExpr
{
	struct ASTExpression *lhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTPtrReadExpr fields without direct struct access

#ifndef ASTPTRREADEXPR_GET_LHS
#define ASTPTRREADEXPR_GET_LHS(astPtrReadExpr) (astPtrReadExpr).lhs
#endif


#ifndef ASTPTRREADEXPR_GET_DATATYPE
#define ASTPTRREADEXPR_GET_DATATYPE(astPtrReadExpr) (astPtrReadExpr).dataType
#endif



// Mutator macros for assigning ASTPtrReadExpr fields consistently

#ifndef ASTPTRREADEXPR_SET_LHS
#define ASTPTRREADEXPR_SET_LHS(astPtrReadExpr,c4value) (astPtrReadExpr).lhs = (c4value)
#endif


#ifndef ASTPTRREADEXPR_SET_DATATYPE
#define ASTPTRREADEXPR_SET_DATATYPE(astPtrReadExpr,c4value) (astPtrReadExpr).dataType = (c4value)
#endif

bool ASTPtrReadExprNew(struct ASTPtrReadExpr *self,struct ASTExpression *lhs);




struct ASTPtrWriteExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTPtrWriteExpr fields without direct struct access

#ifndef ASTPTRWRITEEXPR_GET_LHS
#define ASTPTRWRITEEXPR_GET_LHS(astPtrWriteExpr) (astPtrWriteExpr).lhs
#endif


#ifndef ASTPTRWRITEEXPR_GET_RHS
#define ASTPTRWRITEEXPR_GET_RHS(astPtrWriteExpr) (astPtrWriteExpr).rhs
#endif


#ifndef ASTPTRWRITEEXPR_GET_DATATYPE
#define ASTPTRWRITEEXPR_GET_DATATYPE(astPtrWriteExpr) (astPtrWriteExpr).dataType
#endif



// Mutator macros for assigning ASTPtrWriteExpr fields consistently

#ifndef ASTPTRWRITEEXPR_SET_LHS
#define ASTPTRWRITEEXPR_SET_LHS(astPtrWriteExpr,c4value) (astPtrWriteExpr).lhs = (c4value)
#endif


#ifndef ASTPTRWRITEEXPR_SET_RHS
#define ASTPTRWRITEEXPR_SET_RHS(astPtrWriteExpr,c4value) (astPtrWriteExpr).rhs = (c4value)
#endif


#ifndef ASTPTRWRITEEXPR_SET_DATATYPE
#define ASTPTRWRITEEXPR_SET_DATATYPE(astPtrWriteExpr,c4value) (astPtrWriteExpr).dataType = (c4value)
#endif

bool ASTPtrWriteExprNew(struct ASTPtrWriteExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);




struct ASTPtrOffsetExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTPtrOffsetExpr fields without direct struct access

#ifndef ASTPTROFFSETEXPR_GET_LHS
#define ASTPTROFFSETEXPR_GET_LHS(astPtrOffsetExpr) (astPtrOffsetExpr).lhs
#endif


#ifndef ASTPTROFFSETEXPR_GET_RHS
#define ASTPTROFFSETEXPR_GET_RHS(astPtrOffsetExpr) (astPtrOffsetExpr).rhs
#endif


#ifndef ASTPTROFFSETEXPR_GET_DATATYPE
#define ASTPTROFFSETEXPR_GET_DATATYPE(astPtrOffsetExpr) (astPtrOffsetExpr).dataType
#endif



// Mutator macros for assigning ASTPtrOffsetExpr fields consistently

#ifndef ASTPTROFFSETEXPR_SET_LHS
#define ASTPTROFFSETEXPR_SET_LHS(astPtrOffsetExpr,c4value) (astPtrOffsetExpr).lhs = (c4value)
#endif


#ifndef ASTPTROFFSETEXPR_SET_RHS
#define ASTPTROFFSETEXPR_SET_RHS(astPtrOffsetExpr,c4value) (astPtrOffsetExpr).rhs = (c4value)
#endif


#ifndef ASTPTROFFSETEXPR_SET_DATATYPE
#define ASTPTROFFSETEXPR_SET_DATATYPE(astPtrOffsetExpr,c4value) (astPtrOffsetExpr).dataType = (c4value)
#endif

bool ASTPtrOffsetExprNew(struct ASTPtrOffsetExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);





struct ASTPtrByteOffsetExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTPtrByteOffsetExpr fields without direct struct access

#ifndef ASTPTRBYTEOFFSETEXPR_GET_LHS
#define ASTPTRBYTEOFFSETEXPR_GET_LHS(astPtrByteOffsetExpr) (astPtrByteOffsetExpr).lhs
#endif


#ifndef ASTPTRBYTEOFFSETEXPR_GET_RHS
#define ASTPTRBYTEOFFSETEXPR_GET_RHS(astPtrByteOffsetExpr) (astPtrByteOffsetExpr).rhs
#endif


#ifndef ASTPTRBYTEOFFSETEXPR_GET_DATATYPE
#define ASTPTRBYTEOFFSETEXPR_GET_DATATYPE(astPtrByteOffsetExpr) (astPtrByteOffsetExpr).dataType
#endif



// Mutator macros for assigning ASTPtrByteOffsetExpr fields consistently

#ifndef ASTPTRBYTEOFFSETEXPR_SET_LHS
#define ASTPTRBYTEOFFSETEXPR_SET_LHS(astPtrByteOffsetExpr,c4value) (astPtrByteOffsetExpr).lhs = (c4value)
#endif


#ifndef ASTPTRBYTEOFFSETEXPR_SET_RHS
#define ASTPTRBYTEOFFSETEXPR_SET_RHS(astPtrByteOffsetExpr,c4value) (astPtrByteOffsetExpr).rhs = (c4value)
#endif


#ifndef ASTPTRBYTEOFFSETEXPR_SET_DATATYPE
#define ASTPTRBYTEOFFSETEXPR_SET_DATATYPE(astPtrByteOffsetExpr,c4value) (astPtrByteOffsetExpr).dataType = (c4value)
#endif



bool ASTPtrByteOffsetExprNew(struct ASTPtrByteOffsetExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);







struct ASTPtrAdvanceExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTPtrAdvanceExpr fields without direct struct access

#ifndef ASTPTRADVANCEEXPR_GET_LHS
#define ASTPTRADVANCEEXPR_GET_LHS(astPtrAdvanceExpr) (astPtrAdvanceExpr).lhs
#endif


#ifndef ASTPTRADVANCEEXPR_GET_RHS
#define ASTPTRADVANCEEXPR_GET_RHS(astPtrAdvanceExpr) (astPtrAdvanceExpr).rhs
#endif


#ifndef ASTPTRADVANCEEXPR_GET_DATATYPE
#define ASTPTRADVANCEEXPR_GET_DATATYPE(astPtrAdvanceExpr) (astPtrAdvanceExpr).dataType
#endif



// Mutator macros for assigning ASTPtrAdvanceExpr fields consistently

#ifndef ASTPTRADVANCEEXPR_SET_LHS
#define ASTPTRADVANCEEXPR_SET_LHS(astPtrAdvanceExpr,c4value) (astPtrAdvanceExpr).lhs = (c4value)
#endif


#ifndef ASTPTRADVANCEEXPR_SET_RHS
#define ASTPTRADVANCEEXPR_SET_RHS(astPtrAdvanceExpr,c4value) (astPtrAdvanceExpr).rhs = (c4value)
#endif


#ifndef ASTPTRADVANCEEXPR_SET_DATATYPE
#define ASTPTRADVANCEEXPR_SET_DATATYPE(astPtrAdvanceExpr,c4value) (astPtrAdvanceExpr).dataType = (c4value)
#endif



bool ASTPtrAdvanceExprNew(struct ASTPtrAdvanceExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);





struct ASTPtrDiffExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTPtrDiffExpr fields without direct struct access

#ifndef ASTPTRDIFFEXPR_GET_LHS
#define ASTPTRDIFFEXPR_GET_LHS(astPtrDiffExpr) (astPtrDiffExpr).lhs
#endif


#ifndef ASTPTRDIFFEXPR_GET_RHS
#define ASTPTRDIFFEXPR_GET_RHS(astPtrDiffExpr) (astPtrDiffExpr).rhs
#endif


#ifndef ASTPTRDIFFEXPR_GET_DATATYPE
#define ASTPTRDIFFEXPR_GET_DATATYPE(astPtrDiffExpr) (astPtrDiffExpr).dataType
#endif



// Mutator macros for assigning ASTPtrDiffExpr fields consistently

#ifndef ASTPTRDIFFEXPR_SET_LHS
#define ASTPTRDIFFEXPR_SET_LHS(astPtrDiffExpr,c4value) (astPtrDiffExpr).lhs = (c4value)
#endif


#ifndef ASTPTRDIFFEXPR_SET_RHS
#define ASTPTRDIFFEXPR_SET_RHS(astPtrDiffExpr,c4value) (astPtrDiffExpr).rhs = (c4value)
#endif


#ifndef ASTPTRDIFFEXPR_SET_DATATYPE
#define ASTPTRDIFFEXPR_SET_DATATYPE(astPtrDiffExpr,c4value) (astPtrDiffExpr).dataType = (c4value)
#endif

bool ASTPtrDiffExprNew(struct ASTPtrDiffExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);




struct ASTSubscriptExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *index;
	struct LinkedList indices;
	struct ASTType *baseType;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTSubscriptExpr fields without direct struct access

#ifndef ASTSUBSCRIPTEXPR_GET_LHS
#define ASTSUBSCRIPTEXPR_GET_LHS(astSubscriptExpr) (astSubscriptExpr).lhs
#endif


#ifndef ASTSUBSCRIPTEXPR_GET_INDEX
#define ASTSUBSCRIPTEXPR_GET_INDEX(astSubscriptExpr) (astSubscriptExpr).index
#endif


#ifndef ASTSUBSCRIPTEXPR_GET_INDICES
#define ASTSUBSCRIPTEXPR_GET_INDICES(astSubscriptExpr) (astSubscriptExpr).indices
#endif


#ifndef ASTSUBSCRIPTEXPR_GET_BASETYPE
#define ASTSUBSCRIPTEXPR_GET_BASETYPE(astSubscriptExpr) (astSubscriptExpr).baseType
#endif


#ifndef ASTSUBSCRIPTEXPR_GET_DATATYPE
#define ASTSUBSCRIPTEXPR_GET_DATATYPE(astSubscriptExpr) (astSubscriptExpr).dataType
#endif



// Mutator macros for assigning ASTSubscriptExpr fields consistently

#ifndef ASTSUBSCRIPTEXPR_SET_LHS
#define ASTSUBSCRIPTEXPR_SET_LHS(astSubscriptExpr,c4value) (astSubscriptExpr).lhs = (c4value)
#endif


#ifndef ASTSUBSCRIPTEXPR_SET_INDEX
#define ASTSUBSCRIPTEXPR_SET_INDEX(astSubscriptExpr,c4value) (astSubscriptExpr).index = (c4value)
#endif


#ifndef ASTSUBSCRIPTEXPR_SET_INDICES
#define ASTSUBSCRIPTEXPR_SET_INDICES(astSubscriptExpr,c4value) (astSubscriptExpr).indices = (c4value)
#endif


#ifndef ASTSUBSCRIPTEXPR_SET_BASETYPE
#define ASTSUBSCRIPTEXPR_SET_BASETYPE(astSubscriptExpr,c4value) (astSubscriptExpr).baseType = (c4value)
#endif


#ifndef ASTSUBSCRIPTEXPR_SET_DATATYPE
#define ASTSUBSCRIPTEXPR_SET_DATATYPE(astSubscriptExpr,c4value) (astSubscriptExpr).dataType = (c4value)
#endif

bool ASTSubscriptExprNew(struct ASTSubscriptExpr *self,struct ASTExpression *lhs,struct ASTExpression *index);




struct ASTAsPtrExpr
{
	struct ASTExpression *lhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTAsPtrExpr fields without direct struct access

#ifndef ASTASPTR_GET_LHS
#define ASTASPTR_GET_LHS(astAsPtrExpr) (astAsPtrExpr).lhs
#endif


#ifndef ASTASPTR_GET_DATATYPE
#define ASTASPTR_GET_DATATYPE(astAsPtrExpr) (astAsPtrExpr).dataType
#endif



// Mutator macros for assigning ASTAsPtrExpr fields consistently

#ifndef ASTASPTR_SET_LHS
#define ASTASPTR_SET_LHS(astAsPtrExpr,c4value) (astAsPtrExpr).lhs = (c4value)
#endif


#ifndef ASTASPTR_SET_DATATYPE
#define ASTASPTR_SET_DATATYPE(astAsPtrExpr,c4value) (astAsPtrExpr).dataType = (c4value)
#endif

bool ASTAsPtrExprNew(struct ASTAsPtrExpr *self,struct ASTExpression *lhs);




struct ASTLenExpr
{
	struct ASTExpression *lhs;
	struct ASTType *dataType;
};

// Accessor macros for reading ASTLenExpr fields without direct struct access

#ifndef ASTLENEXPR_GET_LHS
#define ASTLENEXPR_GET_LHS(astLenExpr) (astLenExpr).lhs
#endif


#ifndef ASTLENEXPR_GET_DATATYPE
#define ASTLENEXPR_GET_DATATYPE(astLenExpr) (astLenExpr).dataType
#endif



// Mutator macros for assigning ASTLenExpr fields consistently

#ifndef ASTLENEXPR_SET_LHS
#define ASTLENEXPR_SET_LHS(astLenExpr,c4value) (astLenExpr).lhs = (c4value)
#endif


#ifndef ASTLENEXPR_SET_DATATYPE
#define ASTLENEXPR_SET_DATATYPE(astLenExpr,c4value) (astLenExpr).dataType = (c4value)
#endif


bool ASTLenExprNew(struct ASTLenExpr *self,struct ASTExpression *lhs);





struct ASTStructAccessExpr
{
	struct ASTExpression *lhs;
	struct Token *member;
	u64 offset;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTStructAccessExpr fields without direct struct access

#ifndef ASTSTRUCTACCESSEXPR_GET_LHS
#define ASTSTRUCTACCESSEXPR_GET_LHS(astStructAccessExpr) (astStructAccessExpr).lhs
#endif


#ifndef ASTSTRUCTACCESSEXPR_GET_MEMBER
#define ASTSTRUCTACCESSEXPR_GET_MEMBER(astStructAccessExpr) (astStructAccessExpr).member
#endif


#ifndef ASTSTRUCTACCESSEXPR_GET_OFFSET
#define ASTSTRUCTACCESSEXPR_GET_OFFSET(astStructAccessExpr) (astStructAccessExpr).offset
#endif


#ifndef ASTSTRUCTACCESSEXPR_GET_DATATYPE
#define ASTSTRUCTACCESSEXPR_GET_DATATYPE(astStructAccessExpr) (astStructAccessExpr).dataType
#endif



// Mutator macros for assigning ASTStructAccessExpr fields consistently

#ifndef ASTSTRUCTACCESSEXPR_SET_LHS
#define ASTSTRUCTACCESSEXPR_SET_LHS(astStructAccessExpr,c4value) (astStructAccessExpr).lhs = (c4value)
#endif


#ifndef ASTSTRUCTACCESSEXPR_SET_MEMBER
#define ASTSTRUCTACCESSEXPR_SET_MEMBER(astStructAccessExpr,c4value) (astStructAccessExpr).member = (c4value)
#endif


#ifndef ASTSTRUCTACCESSEXPR_SET_OFFSET
#define ASTSTRUCTACCESSEXPR_SET_OFFSET(astStructAccessExpr,c4value) (astStructAccessExpr).offset = (c4value)
#endif


#ifndef ASTSTRUCTACCESSEXPR_SET_DATATYPE
#define ASTSTRUCTACCESSEXPR_SET_DATATYPE(astStructAccessExpr,c4value) (astStructAccessExpr).dataType = (c4value)
#endif

bool ASTStructAccessExprNew(struct ASTStructAccessExpr *self,struct ASTExpression *lhs,struct Token *member);




struct ASTStructPointerAccessExpr
{
	struct ASTExpression *lhs;
	struct Token *member;
	u64 offset;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTStructPointerAccessExpr fields without direct struct access

#ifndef ASTSTRUCTPOINTERACCESSEXPR_GET_LHS
#define ASTSTRUCTPOINTERACCESSEXPR_GET_LHS(astStructPointerAccessExpr) (astStructPointerAccessExpr).lhs
#endif


#ifndef ASTSTRUCTPOINTERACCESSEXPR_GET_MEMBER
#define ASTSTRUCTPOINTERACCESSEXPR_GET_MEMBER(astStructPointerAccessExpr) (astStructPointerAccessExpr).member
#endif


#ifndef ASTSTRUCTPOINTERACCESSEXPR_GET_OFFSET
#define ASTSTRUCTPOINTERACCESSEXPR_GET_OFFSET(astStructPointerAccessExpr) (astStructPointerAccessExpr).offset
#endif


#ifndef ASTSTRUCTPOINTERACCESSEXPR_GET_DATATYPE
#define ASTSTRUCTPOINTERACCESSEXPR_GET_DATATYPE(astStructPointerAccessExpr) (astStructPointerAccessExpr).dataType
#endif



// Mutator macros for assigning ASTStructPointerAccessExpr fields consistently

#ifndef ASTSTRUCTPOINTERACCESSEXPR_SET_LHS
#define ASTSTRUCTPOINTERACCESSEXPR_SET_LHS(astStructPointerAccessExpr,c4value) (astStructPointerAccessExpr).lhs = (c4value)
#endif


#ifndef ASTSTRUCTPOINTERACCESSEXPR_SET_MEMBER
#define ASTSTRUCTPOINTERACCESSEXPR_SET_MEMBER(astStructPointerAccessExpr,c4value) (astStructPointerAccessExpr).member = (c4value)
#endif


#ifndef ASTSTRUCTPOINTERACCESSEXPR_SET_OFFSET
#define ASTSTRUCTPOINTERACCESSEXPR_SET_OFFSET(astStructPointerAccessExpr,c4value) (astStructPointerAccessExpr).offset = (c4value)
#endif


#ifndef ASTSTRUCTPOINTERACCESSEXPR_SET_DATATYPE
#define ASTSTRUCTPOINTERACCESSEXPR_SET_DATATYPE(astStructPointerAccessExpr,c4value) (astStructPointerAccessExpr).dataType = (c4value)
#endif

bool ASTStructPointerAccessExprNew(struct ASTStructPointerAccessExpr *self,struct ASTExpression *lhs,struct Token *member);




struct ASTMethodExpr
{
	struct ASTExpression *lhs;
	struct Token *member;
	struct LinkedList arguments;
	struct ASTFunctionAttributes *attributes;
	struct ModuleSymbol *symbol;
	struct ASTType *dataType;
};


// Accessor macros for reading ASTMethodExpr fields without direct struct access

#ifndef ASTMETHODEXPR_GET_LHS
#define ASTMETHODEXPR_GET_LHS(astMethodExpr) (astMethodExpr).lhs
#endif


#ifndef ASTMETHODEXPR_GET_MEMBER
#define ASTMETHODEXPR_GET_MEMBER(astMethodExpr) (astMethodExpr).member
#endif


#ifndef ASTMETHODEXPR_GET_ARGUMENTS
#define ASTMETHODEXPR_GET_ARGUMENTS(astMethodExpr) (astMethodExpr).arguments
#endif


#ifndef ASTMETHODEXPR_GET_ATTRIBUTES
#define ASTMETHODEXPR_GET_ATTRIBUTES(astMethodExpr) (astMethodExpr).attributes
#endif


#ifndef ASTMETHODEXPR_GET_SYMBOL
#define ASTMETHODEXPR_GET_SYMBOL(astMethodExpr) (astMethodExpr).symbol
#endif


#ifndef ASTMETHODEXPR_GET_DATATYPE
#define ASTMETHODEXPR_GET_DATATYPE(astMethodExpr) (astMethodExpr).dataType
#endif



// Mutator macros for assigning ASTMethodExpr fields consistently

#ifndef ASTMETHODEXPR_SET_LHS
#define ASTMETHODEXPR_SET_LHS(astMethodExpr,c4value) (astMethodExpr).lhs = (c4value)
#endif


#ifndef ASTMETHODEXPR_SET_MEMBER
#define ASTMETHODEXPR_SET_MEMBER(astMethodExpr,c4value) (astMethodExpr).member = (c4value)
#endif


#ifndef ASTMETHODEXPR_SET_ARGUMENTS
#define ASTMETHODEXPR_SET_ARGUMENTS(astMethodExpr,c4value) (astMethodExpr).arguments = (c4value)
#endif


#ifndef ASTMETHODEXPR_SET_ATTRIBUTES
#define ASTMETHODEXPR_SET_ATTRIBUTES(astMethodExpr,c4value) (astMethodExpr).attributes = (c4value)
#endif


#ifndef ASTMETHODEXPR_SET_SYMBOL
#define ASTMETHODEXPR_SET_SYMBOL(astMethodExpr,c4value) (astMethodExpr).symbol = (c4value)
#endif


#ifndef ASTMETHODEXPR_SET_DATATYPE
#define ASTMETHODEXPR_SET_DATATYPE(astMethodExpr,c4value) (astMethodExpr).dataType = (c4value)
#endif


bool ASTMethodExprNew(struct ASTMethodExpr *self,struct ASTExpression *lhs,struct Token *member,struct LinkedList arguments);


struct ASTPathExpr
{
    struct LinkedList path;      // ["tcp", "Socket"]
	bool isFunction;
	struct LinkedList arguments;
    struct ModuleSymbol *symbol; // resolved result
    struct ASTType *dataType;
};


// Accessor macros for reading ASTPathExpr fields without direct struct access

#ifndef ASTPATHEXPR_GET_PATH
#define ASTPATHEXPR_GET_PATH(astPathExpr) (astPathExpr).path
#endif


#ifndef ASTPATHEXPR_GET_SYMBOL
#define ASTPATHEXPR_GET_SYMBOL(astPathExpr) (astPathExpr).symbol
#endif


#ifndef ASTPATHEXPR_GET_DATATYPE
#define ASTPATHEXPR_GET_DATATYPE(astPathExpr) (astPathExpr).dataType
#endif



// Mutator macros for assigning ASTPathExpr fields consistently

#ifndef ASTPATHEXPR_SET_PATH
#define ASTPATHEXPR_SET_PATH(astPathExpr,c4value) (astPathExpr).path = (c4value)
#endif


#ifndef ASTPATHEXPR_SET_SYMBOL
#define ASTPATHEXPR_SET_SYMBOL(astPathExpr,c4value) (astPathExpr).symbol = (c4value)
#endif


#ifndef ASTPATHEXPR_SET_DATATYPE
#define ASTPATHEXPR_SET_DATATYPE(astPathExpr,c4value) (astPathExpr).dataType = (c4value)
#endif

bool ASTPathExprNew(struct ASTPathExpr *self,struct LinkedList path,bool isFunction,struct LinkedList arguments);

























struct ASTProgram *C4MakeASTProgram(struct BumpAllocator *bump,struct LinkedList decls);


struct ASTDeclaration *C4MakeASTDeclaration(struct BumpAllocator *bump,enum ASTDeclarationKind kind,void *decl,bool isPublic);


struct ASTUseDecl *C4MakeASTUseDecl(struct BumpAllocator *bump,struct LinkedList path,struct Token *alias);


struct ASTEnumDecl *C4MakeASTEnumDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList constants);

struct ASTEnumConstant *C4MakeASTEnumConstant(struct BumpAllocator *bump,struct Token *constant,struct ASTExpression *expr);

struct ASTStructDecl *C4MakeASTStructDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList properties);



struct ASTStructProperty *C4MakeASTStructProperty(struct BumpAllocator *bump,struct ASTType *type,struct Token *ident);




struct ASTStructProperty *C4MakeASTStructProperty(struct BumpAllocator *bump,struct ASTType *type,struct Token *ident);



struct ASTImplDecl *C4MakeASTImplDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList methods); 

struct ASTSumDecl *C4MakeASTSumDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList variants);


struct ASTSumVariant *C4MakeASTSumVariant(struct BumpAllocator *bump,struct Token *ident,enum ASTSumVariantKind kind,struct LinkedList fields);

struct ASTForeignDecl *C4MakeASTForeignDecl(struct BumpAllocator *bump,struct LinkedList functions);




struct ASTFunctionDecl *C4MakeASTFunctionDecl(struct BumpAllocator *bump,struct ASTType *returnType,struct Token *ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes,bool hasVariableArguments);



struct ASTTypeDecl *C4MakeASTTypeDecl(struct BumpAllocator *bump,struct Token *ident,struct ASTType *type);


struct ASTFunctionArgument *C4MakeASTFunctionArgument(struct BumpAllocator *bump,struct ASTType *type,struct Token *ident);



struct ASTFunctionAttributes *C4MakeASTFunctionAttributes(struct BumpAllocator *bump,bool isPublic,bool isStatic,bool isNaked,bool isForeign,struct String foreignAbi,bool hasLinkName,struct String linkName);




struct ASTType *C4MakeASTType(struct BumpAllocator *bump,enum ASTDataType dataType,void *type);



struct ASTPointerType *C4MakeASTPointerType(struct BumpAllocator *bump,struct ASTType *type);



struct ASTArrayType *C4MakeASTArrayType(struct BumpAllocator *bump,struct ASTType *type,struct ASTExpression *size);



struct ASTFunctionType *C4MakeASTFunctionType(struct BumpAllocator *bump,struct ASTType *returnType,struct LinkedList arguments,bool hasVariableArguments);



struct ASTStructType *C4MakeASTStructType(struct BumpAllocator *bump,struct Token *ident,struct Layout layout);



struct ASTAggregateType *C4MakeASTAggregateType(struct BumpAllocator *bump,struct LinkedList path);


struct ASTGenericType *C4MakeASTGenericType(struct BumpAllocator *bump,struct ASTType *base,struct LinkedList args);


struct ASTStatement *C4MakeASTStatement(struct BumpAllocator *bump,enum ASTStatementKind kind,void *stmt);



struct ASTBlockStmt *C4MakeASTBlockStmt(struct BumpAllocator *bump,struct LinkedList stmts);



struct ASTReturnStmt *C4MakeASTReturnStmt(struct BumpAllocator *bump,struct ASTExpression *expr);



struct ASTVariableDecl *C4MakeASTVariableDecl(struct BumpAllocator *bump,bool isConstant,struct ASTType *type,struct Token *ident,struct ASTVariableDeclInit *init);



struct ASTVariableDeclInit *C4MakeASTVariableDeclInit(struct BumpAllocator *bump,enum ASTVariableDeclInitKind kind,void *init);



struct ASTVariableDeclSingleInit *C4MakeASTVariableDeclSingleInit(struct BumpAllocator *bump,struct ASTExpression *expr);



struct ASTVariableDeclArrayInit *C4MakeASTVariableDeclArrayInit(struct BumpAllocator *bump,struct LinkedList elements);



struct ASTBreakStmt *C4MakeASTBreakStmt(struct BumpAllocator *bump);




struct ASTContinueStmt *C4MakeASTContinueStmt(struct BumpAllocator *bump);



struct ASTLoopStmt *C4MakeASTLoopStmt(struct BumpAllocator *bump,struct ASTBlockStmt *block);



struct ASTWhileStmt *C4MakeASTWhileStmt(struct BumpAllocator *bump,struct ASTExpression *expr,struct ASTBlockStmt *block);



struct ASTIfStmt *C4MakeASTIfStmt(struct BumpAllocator *bump,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList elifs,struct ASTIfElse *elseBlock);




struct ASTIfElif *C4MakeASTIfElif(struct BumpAllocator *bump,struct ASTExpression *expr,struct ASTBlockStmt *block);



struct ASTIfElse *C4MakeASTIfElse(struct BumpAllocator *bump,struct ASTBlockStmt *block);




struct ASTExpression *C4MakeASTExpression(struct BumpAllocator *bump,enum ASTExpressionKind kind,void *expr);



struct ASTLiteralExpr *C4MakeASTLiteralExpr(struct BumpAllocator *bump,enum ASTLiteralKind kind,struct Token *literal);



struct ASTVariableExpr *C4MakeASTVariableExpr(struct BumpAllocator *bump,struct Token *ident);

struct ASTParenExpr *C4MakeASTParenExpr(struct BumpAllocator *bump,struct ASTExpression *expr);

struct ASTUnaryExpr *C4MakeASTUnaryExpr(struct BumpAllocator *bump,enum ASTUnaryOperator op,struct ASTExpression *rhs);



struct ASTBinaryExpr *C4MakeASTBinaryExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,enum ASTBinaryOperator op,struct ASTExpression *rhs);



struct ASTAssignmentExpr *C4MakeASTAssignmentExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,enum ASTAssignmentOperator op,struct ASTExpression *rhs);



struct ASTCastExpr *C4MakeASTCastExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,enum ASTCastOperator op,struct ASTType *dataType);



struct ASTFunctionCallExpr *C4MakeASTFunctionCallExpr(struct BumpAllocator *bump,struct ASTExpression *base,struct LinkedList arguments);



struct ASTAddressOfExpr *C4MakeASTAddressOfExpr(struct BumpAllocator *bump,struct ASTExpression *rhs);



struct ASTPtrReadExpr *C4MakeASTPtrReadExpr(struct BumpAllocator *bump,struct ASTExpression *lhs);



struct ASTPtrWriteExpr *C4MakeASTPtrWriteExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs);



struct ASTPtrOffsetExpr *C4MakeASTPtrOffsetExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs);



struct ASTPtrByteOffsetExpr *C4MakeASTPtrByteOffsetExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs);

struct ASTPtrAdvanceExpr *C4MakeASTPtrAdvanceExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs);

struct ASTPtrDiffExpr *C4MakeASTPtrDiffExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs);



struct ASTSubscriptExpr *C4MakeASTSubscriptExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *index);



struct ASTAsPtrExpr *C4MakeASTAsPtrExpr(struct BumpAllocator *bump,struct ASTExpression *lhs);



struct ASTLenExpr *C4MakeASTLenExpr(struct BumpAllocator *bump,struct ASTExpression *lhs);



struct ASTStructAccessExpr *C4MakeASTStructAccessExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct Token *member);



struct ASTStructPointerAccessExpr *C4MakeASTStructPointerAccessExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct Token *member);





struct ASTMethodExpr *C4MakeASTMethodExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct Token *member,struct LinkedList arguments);


struct ASTPathExpr *C4MakeASTPathExpr(struct BumpAllocator *bump,struct LinkedList path,bool isFunction,struct LinkedList arguments);








#endif
