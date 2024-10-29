
%code requires {
#include <iostream>
#include <string>
#include "ast.hpp"

void yyerror(ASTNode** root, const char* code, const char* s);
void baby_parse(ASTNode** root, const char* code);

extern int yylex();
extern void scanner_destroy();
extern void scanner_init(const char* code);
}

%union {
	int intval;
	char* id;
    ASTNode* node;
    ASTNodeBlock* block;
    ASTNodeParameters* param_list;
    ASTNodeArguments* arg_list;
}

%token FN;
%token RETURN;
%token LBRACE;
%token RBRACE;
%token END;
%token <id> IDENTIFIER;

%token <intval> INT_LITERAL;
%token PLUS;
%token MINUS;
%token STAR;
%token SLASH;

%token LESS;
%token GREATER;
%token LESS_EQUAL;
%token GREATER_EQUAL;
%token EQUAL_EQUAL;
%token NOT_EQUAL;
%token AND;
%token OR;

%token IF;
%token ELSE;
%token COMMA;
%token EQUAL;
%token LPAREN;
%token RPAREN;
%token SEMICOLON;

%token BB_EOF;

%type <node> program statement expression term unary primary assignment factor equality comparison if_stmt return_stmt fn_decl call 
%type <block> statement_list block
%type <param_list> param_list
%type <arg_list> arg_list


%parse-param { ASTNode** root} { const char* code }

%%
program: 
    statement_list { *root = $1; YYACCEPT; }
    ;

statement_list:
    statement { $$ = new ASTNodeBlock({$1}); }
    | statement_list statement BB_EOF { $1->statements.push_back($2); $$ = $1; }
    ;

statement:
	 expression SEMICOLON { $$ = $1; }
     | assignment SEMICOLON { $$ = $1;}
     | block { $$ = $1; } 
     | if_stmt { $$ = $1; }
     | fn_decl { $$ = $1; }
     | return_stmt SEMICOLON { $$ = $1; }
	 ;

fn_decl:
    FN IDENTIFIER LPAREN param_list RPAREN block { $$ = new ASTNodeFunctionDeclaration($2, $4, $6); }
    ;

param_list:
    IDENTIFIER { $$ = new ASTNodeParameters({$1}); }
    | param_list COMMA IDENTIFIER { $1->params.push_back($3); $$ = $1; }
    ;

return_stmt:
    RETURN expression { $$ = new ASTNodeReturn($2); }
    ;

if_stmt:
    IF expression block ELSE block { $$ = new ASTNodeIf($2, $3, $5); }
    ;

block: 
    LBRACE statement_list RBRACE { $$ = $2; }
    ;

statement_list:
    statement { $$ = new ASTNodeBlock({$1}); }
    | statement_list statement { $1->statements.push_back($2); $$ = $1; }

assignment:
    IDENTIFIER EQUAL expression { $$ = new ASTNodeVariableDeclaration($1, $3); }
    ;

expression:
	  equality { $$ = $1; }
	  ;

equality:
    | comparison EQUAL_EQUAL equality { $$ = new ASTNodeBinary($1, "==", $3); }
    | comparison NOT_EQUAL equality { $$ = new ASTNodeBinary($1, "!=", $3); }
    | comparison { $$ = $1; }
    ;

comparison:
    term LESS comparison { $$ = new ASTNodeBinary($1, "<", $3); }
    | term LESS_EQUAL comparison { $$ = new ASTNodeBinary($1, "<=", $3); } 
    | term GREATER comparison { $$ = new ASTNodeBinary($1, ">", $3); }
    | term GREATER_EQUAL comparison { $$ = new ASTNodeBinary($1, ">=", $3); }
    | term { $$ = $1; }
    ;


term:
    factor PLUS term { $$ = new ASTNodeBinary($1, "+", $3); }
    | factor MINUS term { $$ = new ASTNodeBinary($1, "-", $3); }
    | factor { $$ = $1; }
    ;

factor:
    unary SLASH factor { $$ = new ASTNodeBinary($1, "/", $3); }
    | unary STAR factor { $$ = new ASTNodeBinary($1, "*", $3); }
    | unary { $$ = $1; }

unary:
     MINUS unary { $$ = new ASTNodeUnary("-", $2); }
     | call { $$ = $1; }
     ;

call:
    IDENTIFIER LPAREN arg_list RPAREN { $$ = new ASTNodeFunctionCall($1, $3); }
    | primary { $$ = $1; }
    ;

arg_list:
    expression { $$ = new ASTNodeArguments({$1}); }
    | arg_list COMMA expression { $1->arguments.push_back($3); $$ = $1; }
    ;

primary:
       INT_LITERAL { $$ = new ASTNodeNumber($1); } 
       | IDENTIFIER { $$ = new ASTNodeIdentifier($1); }
       ;
%%

void yyerror(ASTNode** root, const char* code, const char* s) {
    std::cout << "Error: " << s << std::endl;
}

void baby_parse(ASTNode** root, const char* code) {
    scanner_init(code);

    int ret = yyparse(root, code);

    scanner_destroy();

    if (ret == 0) {
        return;
    }
}