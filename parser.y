
%code requires {
#include <iostream>
#include <string>
#include "ast.hpp"

void yyerror(ASTNode** root, const char* s);
void baby_parse(ASTNode** root);

extern int yylex();
}

%union {
	int intval;
	char* id;
    ASTNode* node;
}

%token FN;
%token RETURN;
%token START;
%token END;
%token <id> IDENTIFIER;

%token <intval> INT_LITERAL;
%token PLUS;
%token MINUS;
%token COMMA;
%token EQUAL;
%token LPAREN;
%token RPAREN;
%token DOT;

%type <node> program statement expression term unary primary

%parse-param { ASTNode** root }

%%
program: 
    statement { *root = $1; YYACCEPT; }
    ;

statement:
	 expression DOT { $$ = $1; }
	 ;

expression:
	  term { $$ = $1; }
	  ;

term:
    unary PLUS term { $$ = new ASTNodeAdd($1, $3); }
    | unary MINUS term { $$ = new ASTNodeSub($1, $3); }
    | unary { $$ = $1; }
    ;

unary:
     MINUS unary { $$ = new ASTNodeUnaryMinus($2); }
     | primary { $$ = $1; }
     ;

primary:
       INT_LITERAL { $$ = new ASTNodeNumber($1); } 
       ;
%%


void yyerror(ASTNode** root, const char* s) {
    std::cout << "Error: " << s << std::endl;
}



void baby_parse(ASTNode** root) {
    int ret = yyparse(root);
    if (ret == 0) {
        return;
    }
}