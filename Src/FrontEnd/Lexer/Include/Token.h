#ifndef ACHIOR_LABS_TOKEN_H
#define ACHIOR_LABS_TOKEN_H

#include "../../Include/Include.h"



// Defines all token categories produced by the lexer.
// Covers operators, literals, keywords, punctuation, and error tokens.

enum TokenKind
{
    // Arithmetic operators used in expressions (+, -, *, /, %, exponentiation)

    TOKEN_EXP = 0,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_ADD,
    TOKEN_SUB,

    // Relational comparison operators used in conditions and branching

    TOKEN_GREATER,
    TOKEN_LESS,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS_EQUAL,


    // Equality and inequality checks used in boolean expressions

    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,


    // Bitwise operations on integer values (AND, OR, XOR, shifts, NOT)

    TOKEN_BITWISE_AND,
    TOKEN_BITWISE_OR,
    TOKEN_BITWISE_XOR,
    TOKEN_BITWISE_NOT,
    TOKEN_LEFT_SHIFT,
    TOKEN_RIGHT_SHIFT,


    // Logical boolean operators used in control flow conditions

    TOKEN_AND,
    TOKEN_OR ,
    TOKEN_NOT,


    // Conditional ternary operator used for inline branching

    TOKEN_TERNARY,


    // Unary increment and decrement operators

    TOKEN_PLUS_PLUS,
    TOKEN_SUB_SUB,


    // Assignment and compound assignment operators
    // Used to modify existing variables with operations

    TOKEN_ASSIGN,
    TOKEN_ASSIGN_ADD,
    TOKEN_ASSIGN_SUB,
    TOKEN_ASSIGN_MUL,
    TOKEN_ASSIGN_DIV,
    TOKEN_ASSIGN_MOD,
    TOKEN_ASSIGN_EXP,
    TOKEN_ASSIGN_BITWISE_AND,
    TOKEN_ASSIGN_BITWISE_OR,
    TOKEN_ASSIGN_BITWISE_XOR,
    TOKEN_ASSIGN_LEFT_SHIFT,
    TOKEN_ASSIGN_RIGHT_SHIFT,



    // Punctuation and syntax symbols used by parser and grammar rules

    TOKEN_COLON,
    TOKEN_TILDE,
    TOKEN_RESOLUTION,
    TOKEN_SEMI_COLON,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_UNDERSCORE,
    TOKEN_RETPARAM,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_AT,
    TOKEN_MULTI_COMMENT,
    TOKEN_SINGLE_COMMENT,


    // Identifiers(variable names,function names,struct names, etcetera etcetera)

    TOKEN_IDENT,


    // Constant literal values parsed directly from source code

    TOKEN_LITERAL_INT,
    TOKEN_LITERAL_FLOAT,
    TOKEN_LITERAL_STRING,
    TOKEN_LITERAL_CHARACTER,


    // Reserved language keywords with special parsing meaning

    TOKEN_KEYWORD_AND,
    TOKEN_KEYWORD_AS,
    TOKEN_KEYWORD_BREAK,
    TOKEN_KEYWORD_BOOL,
    TOKEN_KEYWORD_CASE,
    TOKEN_KEYWORD_CAST,
    TOKEN_KEYWORD_CHAR,
    TOKEN_KEYWORD_CONST,
    TOKEN_KEYWORD_CONTINUE,
    TOKEN_KEYWORD_DEFAULT,
    TOKEN_KEYWORD_DO,
    TOKEN_KEYWORD_DEFER,
    TOKEN_KEYWORD_ELIF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_ENUM,
    TOKEN_KEYWORD_EXTERN,
    TOKEN_KEYWORD_F32,
    TOKEN_KEYWORD_F64,
    TOKEN_KEYWORD_FALSE,
    TOKEN_KEYWORD_FN,
    TOKEN_KEYWORD_FOR,
    TOKEN_KEYWORD_FOREIGN,
    TOKEN_KEYWORD_I8,
    TOKEN_KEYWORD_I16,
    TOKEN_KEYWORD_I32,
    TOKEN_KEYWORD_I64,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_IMPL,
    TOKEN_KEYWORD_LOOP,
    TOKEN_KEYWORD_MACRO,
    TOKEN_KEYWORD_MATCH,
    TOKEN_KEYWORD_MODULE,
    TOKEN_KEYWORD_NEW,
    TOKEN_KEYWORD_NOT_NEW,
    TOKEN_KEYWORD_NOT,
    TOKEN_KEYWORD_NULL,
    TOKEN_KEYWORD_OR,
    TOKEN_KEYWORD_PUB,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_SELF,
    TOKEN_KEYWORD_STATIC,
    TOKEN_KEYWORD_STR,
    TOKEN_KEYWORD_STRUCT,
    TOKEN_KEYWORD_SUM,
    TOKEN_KEYWORD_SWITCH,
    TOKEN_KEYWORD_TRUE,
    TOKEN_KEYWORD_U8,
    TOKEN_KEYWORD_U16,
    TOKEN_KEYWORD_U32,
    TOKEN_KEYWORD_U64,
    TOKEN_KEYWORD_USE,
    TOKEN_KEYWORD_UNION,
    TOKEN_KEYWORD_VOID,
    TOKEN_KEYWORD_WHILE,
    TOKEN_KEYWORD_WITH,


    // Special tokens representing lexer errors and end-of-file state
    // Used for diagnostics and stream termination

    TOKEN_ERROR_INVALID_CHARACTER,                 //done
    TOKEN_ERROR_MALFORMED_NUMBER,
    TOKEN_ERROR_UNTERMINATED_STRING,               //done
    TOKEN_ERROR_UNTERMINATED_CHARACTER,
    TOKEN_ERROR_INVALID_ESCAPE_CHARACTER,
    TOKEN_ERROR_UNTERMINATED_COMMENT,
    TOKEN_EOF,
};






// Represents a source code range (start/end positions + line/column info)
// Used for error reporting, diagnostics, and AST node tracking

struct Span
{
    // Byte offsets in the source buffer marking span boundaries
    u64 start;
    u64 end;

    // Source location where the span begins (line and column)
    u64 startLine;
    u64 startColumn;

    // Source location where the span ends (line and column)
    u64 endLine;
    u64 endColumn;
};



// Accessor macros for reading span fields without direct struct access

#ifndef SPAN_GET_START
#define SPAN_GET_START(span) (span).start 
#endif


#ifndef SPAN_GET_END
#define SPAN_GET_END(span) (span).end 
#endif


#ifndef SPAN_GET_STARTLINE
#define SPAN_GET_STARTLINE(span) (span).startLine
#endif


#ifndef SPAN_GET_STARTCOLUMN
#define SPAN_GET_STARTCOLUMN(span) (span).startColumn
#endif


#ifndef SPAN_GET_ENDLINE
#define SPAN_GET_ENDLINE(span) (span).endLine
#endif


#ifndef SPAN_GET_ENDCOLUMN
#define SPAN_GET_ENDCOLUMN(span) (span).endColumn
#endif


// Mutator macros for assigning span fields consistently

#ifndef SPAN_SET_START
#define SPAN_SET_START(span,c4value) (span).start = (c4value)
#endif


#ifndef SPAN_SET_END
#define SPAN_SET_END(span,c4value) (span).end = (c4value)
#endif


#ifndef SPAN_SET_STARTLINE
#define SPAN_SET_STARTLINE(span,c4value) (span).startLine = (c4value)
#endif


#ifndef SPAN_SET_STARTCOLUMN
#define SPAN_SET_STARTCOLUMN(span,c4value) (span).startColumn = (c4value)
#endif


#ifndef SPAN_SET_ENDLINE
#define SPAN_SET_ENDLINE(span,c4value) (span).endLine = (c4value)
#endif


#ifndef SPAN_SET_ENDCOLUMN
#define SPAN_SET_ENDCOLUMN(span,c4value) (span).endColumn = (c4value)
#endif


// Initializes a Span with full source position information
// Used when creating token or AST node location metadata

void SpanNew(struct Span *self,u64 start,u64 end,u64 startLine,u64 startColumn,u64 endLine,u64 endColumn);




// Represents a single lexed token from the source code
// Contains token type, raw value, and source location span

struct Token
{
	enum TokenKind kind;
	struct String value;
	struct Span span;
};


// Accessor macros for reading token fields without direct struct access

#ifndef TOKEN_GET_KIND
#define TOKEN_GET_KIND(token) (token).kind
#endif

#ifndef TOKEN_GET_VALUE
#define TOKEN_GET_VALUE(token) (token).value
#endif


#ifndef TOKEN_GET_VALUE_DATA
#define TOKEN_GET_VALUE_DATA(token) (token).value.data
#endif

#ifndef TOKEN_GET_VALUE_SIZE
#define TOKEN_GET_VALUE_SIZE(token) (token).value.size
#endif

#ifndef TOKEN_GET_SPAN
#define TOKEN_GET_SPAN(token) (token).span
#endif



// Mutator macros for assigning token fields consistently

#ifndef TOKEN_SET_TYPE
#define TOKEN_SET_TYPE(token,c4value) (token).type = (c4value)
#endif

#ifndef TOKEN_SET_VALUE
#define TOKEN_SET_VALUE(token,c4value) (token).value = (c4value)
#endif

#ifndef TOKEN_SET_SPAN
#define TOKEN_SET_SPAN(token,c4value) (token).span = (c4value)
#endif


// Constructs and initializes a Token instance
// Assigns type, value, and source span information

void TokenNew(struct Token *self,enum TokenKind kind,struct String value,struct Span span);

struct Token *C4MakeToken(struct BumpAllocator *bump,enum TokenKind kind,struct String value,struct Span span);



#endif
