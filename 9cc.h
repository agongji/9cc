#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************************
*          tokenizer         *
*****************************/

typedef enum {
	TK_RESERVED,
	TK_NUM,
	TK_EOF,
} TokenKind;

// Token type
typedef struct Token Token;

struct Token {
	TokenKind kind;
	Token * next;
	int val;
	char * str;
	int len;
};

void error(char * fmt, ...);
void error_at(char * loc, char * fmt, ...);

bool consume(char * op);
void expect(char * op);
int expect_number(void);
bool at_eof(void);
Token * new_token(TokenKind kind, Token * cursor, char * str, int len);
bool startswith(char * p, char * q);
Token * tokenize(void);

// input program
char * user_input;

// Current token
Token * token;


/*****************************
*           parser           *
*****************************/

typedef enum {
	ND_ADD,  // +
	ND_SUB,  // -
	ND_MUL,  // *
	ND_DIV,  // /
	ND_EQ,   // ==
	ND_NE,   // !=
	ND_LT,   // <
	ND_LE,   // <=
	ND_NUM,  // integer
} NodeKind;

typedef struct Node Node;

struct Node {
	NodeKind kind;
	Node * lhs;
	Node * rhs;
	int val;
};


Node * expr();
Node * equality();
Node * relational();
Node * add();
Node * mul();
Node * unary();
Node * primary();


/*****************************
*      code generator        *
*****************************/

void gen(Node * node);