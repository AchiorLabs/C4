#ifndef ACHIOR_LABS_AST_H
#define ACHIOR_LABS_AST_H

#include "../../Lexer/Include/Lexer.h"


struct ASTProgram;
enum ASTDeclarationType;
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
};


bool ASTProgramNew(struct ASTProgram *self,struct LinkedList decls);

enum ASTDeclarationType
{
	AST_DECLARATION_NONE,
	AST_DECLARATION_STRUCT,
	AST_DECLARATION_UNION,
	AST_DECLARATION_IMPL,
	AST_DECLARATION_SUM,
	AST_DECLARATION_FUNCTION,
	AST_DECLARATION_FOREIGN,
};




struct ASTDeclaration
{
	enum ASTDeclarationType type;
	void *decl;
};


bool ASTDeclarationNew(struct ASTDeclaration *self,enum ASTDeclarationType type,void *decl);




enum ASTDataType
{
	AST_DATA_TYPE_NONE = 1,
	AST_DATA_TYPE_VOID,
	AST_DATA_TYPE_CHAR,
	AST_DATA_TYPE_I8,
	AST_DATA_TYPE_I16,
	AST_DATA_TYPE_I32,
	AST_DATA_TYPE_I64,
	AST_DATA_TYPE_U8,
	AST_DATA_TYPE_U16,
	AST_DATA_TYPE_U32,
	AST_DATA_TYPE_U64,
	AST_DATA_TYPE_STRING,
	AST_DATA_TYPE_POINTER,
	AST_DATA_TYPE_ARRAY,
	AST_DATA_TYPE_FUNCTION,
	AST_DATA_TYPE_AGGREGATE,
	AST_DATA_TYPE_STRUCT,
	AST_DATA_TYPE_UNION,
};


struct ASTStructType
{
	struct Token ident;
	struct Layout layout;
};

bool ASTStructTypeNew(struct ASTStructType *self,struct Token ident,struct Layout layout);



struct ASTAggregateType
{
	struct Token ident;
	struct Layout layout;
};

bool ASTAggregateTypeNew(struct ASTAggregateType *self,struct Token ident);




struct ASTFunctionType
{
	struct ASTType *returnType;
	struct LinkedList arguments;
};

bool ASTFunctionTypeNew(struct ASTFunctionType *self,struct ASTType *returnType,struct LinkedList arguments);



struct ASTArrayType
{
	struct ASTType *type;
	struct ASTExpression *size;
	struct Layout layout;
};


bool ASTArrayTypeNew(struct ASTArrayType *self,struct ASTType *type,struct ASTExpression *size);


struct ASTPointerType
{
	struct ASTType *type;
	struct Layout layout;
};


bool ASTPointerTypeNew(struct ASTPointerType *self,struct ASTType *type);


struct ASTType
{
	enum ASTDataType dataType;
	struct Layout layout;
	bool is_function;
	void *type;
};


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

struct ASTStructProperty
{
	struct ASTType *type;
	struct Token ident;
};


bool ASTStructPropertyNew(struct ASTStructProperty *self,struct ASTType *type,struct Token ident);


struct ASTStructDecl
{
	struct Token ident;
	struct LinkedList properties;
};


bool ASTStructDeclNew(struct ASTStructDecl *self,struct Token ident,struct LinkedList properties);



struct ASTUnionDecl
{
	struct Token ident;
	struct LinkedList properties;
};


bool ASTUnionDeclNew(struct ASTUnionDecl *self,struct Token ident,struct LinkedList properties);

struct ASTImplDecl
{
	struct Token ident;
	struct LinkedList methods;
};


bool ASTImplDeclNew(struct ASTImplDecl *self,struct Token ident,struct LinkedList methods);


struct ASTSumNamedField
{
    struct Token ident;
    struct ASTType *type;
};


bool ASTSumNamedFieldNew(struct ASTSumNamedField *self,struct Token ident,struct ASTType *type);



enum ASTSumVariantKind
{
    AST_SUM_VARIANT_NONE,
    AST_SUM_VARIANT_UNIT,
    AST_SUM_VARIANT_TUPLE,
    AST_SUM_VARIANT_STRUCT,
};


struct ASTSumVariant
{
    struct Token ident;
    enum ASTSumVariantKind kind;
    struct LinkedList fields;
};


bool ASTSumVariantNew(struct ASTSumVariant *self,struct Token ident,enum ASTSumVariantKind kind,struct LinkedList fields);


struct ASTSumDecl
{
    struct Token ident;
    struct LinkedList variants;
};

bool ASTSumDeclNew(struct ASTSumDecl *self,struct Token ident,struct LinkedList variants);


struct ASTFunctionAttributes
{
    bool is_pub;
    bool is_static;
    bool is_naked;
	bool is_constructor;

    bool is_foreign;
    struct String foreign_abi;   // "C", empty if not foreign

	bool has_link_name;
    struct String link_name;     // optional override
};


bool ASTFunctionAttributesNew(struct ASTFunctionAttributes *self,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name);


struct ASTFunctionArgument
{
	struct ASTType *type;
	struct Token ident;
};


bool ASTFunctionArgumentNew(struct ASTFunctionArgument *self,struct ASTType *type,struct Token ident);


struct ASTFunctionDecl
{
	struct ASTType *returnType;
	struct Token ident;
	struct LinkedList arguments;
	struct ASTBlockStmt *block;
	struct ASTFunctionAttributes *attributes;
};


bool ASTFunctionDeclNew(struct ASTFunctionDecl *self,struct ASTType *returnType,struct Token ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes);

struct ASTForeignDecl
{
	struct LinkedList functions;
};

bool ASTForeignDeclNew(struct ASTForeignDecl *self,struct LinkedList functions);

enum ASTStatementType
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
	enum ASTStatementType type;
	void *stmt;
};


bool ASTStatementNew(struct ASTStatement *self,enum ASTStatementType type,void *stmt);


struct ASTBlockStmt
{
	struct LinkedList stmts;
};


bool ASTBlockStmtNew(struct ASTBlockStmt *self,struct LinkedList stmts);

struct ASTBreakStmt
{
	struct String label;
};

bool ASTBreakStmtNew(struct ASTBreakStmt *self);


struct ASTContinueStmt
{
	struct String label;
};

bool ASTContinueStmtNew(struct ASTContinueStmt *self);


struct ASTLoopStmt
{
	struct ASTBlockStmt *block;
	struct String label;
};


bool ASTLoopStmtNew(struct ASTLoopStmt *self,struct ASTBlockStmt *block);




struct ASTWhileStmt
{
	struct ASTExpression *expr;
	struct ASTBlockStmt *block;
	struct String label;
};


bool ASTWhileStmtNew(struct ASTWhileStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block);



struct ASTIfElse
{
	struct ASTBlockStmt *block;
};


bool ASTIfElseNew(struct ASTIfElse *self,struct ASTBlockStmt *block);


struct ASTIfElif
{
	struct ASTExpression *expr;
	struct ASTBlockStmt *block;
};


bool ASTIfElifNew(struct ASTIfElif *self,struct ASTExpression *expr,struct ASTBlockStmt *block);

struct ASTIfStmt
{
	struct ASTExpression *expr;
	struct ASTBlockStmt *block;
	struct LinkedList  elifs;
	struct ASTIfElse *else_block;
};


bool ASTIfStmtNew(struct ASTIfStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList  elifs,struct ASTIfElse *else_block);

struct ASTVariableDecl
{
	struct ASTType *type;
	struct Token ident;
	struct ASTVariableDeclInit *init;
};

bool ASTVariableDeclNew(struct ASTVariableDecl *self,struct ASTType *type,struct Token ident,struct ASTVariableDeclInit *init);

enum ASTVariableDeclInitType
{
	AST_VAR_DECL_INIT_NONE,
	AST_VAR_DECL_INIT_SINGLE_INIT,
	AST_VAR_DECL_INIT_ARRAY_INIT,
};

struct ASTVariableDeclInit
{
	enum ASTVariableDeclInitType initType;
	void *init;
};

bool ASTVariableDeclInitNew(struct ASTVariableDeclInit *self,enum ASTVariableDeclInitType initType,void *init);


struct ASTVariableDeclSingleInit
{
	struct ASTExpression *expr;
};

bool ASTVariableDeclSingleInitNew(struct ASTVariableDeclSingleInit *self,struct ASTExpression *expr);



struct ASTVariableDeclArrayInit
{
	struct LinkedList elements;
};

bool ASTVariableDeclArrayInitNew(struct ASTVariableDeclArrayInit *self,struct LinkedList elements);


struct ASTReturnStmt
{
	struct ASTExpression *expr;
};





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
    struct Token ident;
    struct LinkedList bindings;
};


bool ASTPatternNew(struct ASTPattern *self,enum ASTPatternKind kind,struct Token ident,struct LinkedList bindings);


struct ASTMatchArm
{
    struct ASTPattern *pattern;
    struct ASTBlockStmt *stmt;
};

bool ASTMatchArmNew(struct ASTMatchArm *self,struct ASTPattern *pattern,struct ASTBlockStmt*stmt);



struct ASTMatchStmt
{
    struct ASTExpression *expr;
    struct LinkedList arms;
};


bool ASTMatchStmtNew(struct ASTMatchStmt *self,struct ASTExpression *expr,struct LinkedList arms);


enum ASTExpressionType
{
	AST_EXPRESSION_NONE,
	AST_EXPRESSION_LITERAL,
	AST_EXPRESSION_VARIABLE,
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
};



struct ASTExpression
{
	enum ASTExpressionType type;
	void *expr;
	struct ASTType *baseType;
	struct ASTType *dataType;
};



bool ASTExpressionNew(struct ASTExpression *self,enum ASTExpressionType type,void *expr);

enum ASTLiteralType
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
	enum ASTLiteralType type;
	struct Token literal;
	struct ASTType *dataType;
};


bool ASTLiteralExprNew(struct ASTLiteralExpr *self,enum ASTLiteralType type,struct Token literal);



struct ASTVariableExpr
{
	struct Token ident;
	struct ASTType *baseType;
	struct ASTType *dataType;
};

bool ASTVariableExprNew(struct ASTVariableExpr *self,struct Token ident);


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
	AST_BINARY_OPERATOR_AND,
	AST_BINARY_OPERATOR_OR,
};


struct ASTBinaryExpr
{
	struct ASTExpression *lhs;
	enum ASTBinaryOperator op;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


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


bool ASTCastExprNew(struct ASTCastExpr *self,struct ASTExpression *lhs,enum ASTCastOperator op,struct ASTType *dataType);

struct ASTFunctionCallExpr
{
	struct ASTExpression *base;
	struct LinkedList arguments;
	struct ASTFunctionAttributes *attributes;
	struct ASTType *dataType;
};


bool ASTFunctionCallExprNew(struct ASTFunctionCallExpr *self,struct ASTExpression *base,struct LinkedList arguments);





struct ASTAddressOfExpr
{
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


bool ASTAddressOfExprNew(struct ASTAddressOfExpr *self,struct ASTExpression *rhs);



struct ASTPtrReadExpr
{
	struct ASTExpression *lhs;
	struct ASTType *dataType;
};


bool ASTPtrReadExprNew(struct ASTPtrReadExpr *self,struct ASTExpression *lhs);




struct ASTPtrWriteExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


bool ASTPtrWriteExprNew(struct ASTPtrWriteExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);




struct ASTPtrOffsetExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


bool ASTPtrOffsetExprNew(struct ASTPtrOffsetExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);





struct ASTPtrByteOffsetExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


bool ASTPtrByteOffsetExprNew(struct ASTPtrByteOffsetExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);







struct ASTPtrAdvanceExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


bool ASTPtrAdvanceExprNew(struct ASTPtrAdvanceExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);





struct ASTPtrDiffExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *rhs;
	struct ASTType *dataType;
};


bool ASTPtrDiffExprNew(struct ASTPtrDiffExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs);




struct ASTSubscriptExpr
{
	struct ASTExpression *lhs;
	struct ASTExpression *index;
	struct LinkedList indices;
	struct ASTType *baseType;
	struct ASTType *dataType;
};


bool ASTSubscriptExprNew(struct ASTSubscriptExpr *self,struct ASTExpression *lhs,struct ASTExpression *index);




struct ASTAsPtrExpr
{
	struct ASTExpression *lhs;
	struct ASTType *dataType;
};


bool ASTAsPtrExprNew(struct ASTAsPtrExpr *self,struct ASTExpression *lhs);




struct ASTLenExpr
{
	struct ASTExpression *lhs;
	struct ASTType *dataType;
};


bool ASTLenExprNew(struct ASTLenExpr *self,struct ASTExpression *lhs);





struct ASTStructAccessExpr
{
	struct ASTExpression *lhs;
	struct Token member;
	u64 offset;
	struct ASTType *dataType;
};


bool ASTStructAccessExprNew(struct ASTStructAccessExpr *self,struct ASTExpression *lhs,struct Token member);




struct ASTStructPointerAccessExpr
{
	struct ASTExpression *lhs;
	struct Token member;
	u64 offset;
	struct ASTType *dataType;
};


bool ASTStructPointerAccessExprNew(struct ASTStructPointerAccessExpr *self,struct ASTExpression *lhs,struct Token member);



#endif
