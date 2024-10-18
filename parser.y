
%{
#include <iostream>
#include <string>

void yyerror(const char* s);
extern int yylex();
%}

%union {
	int intval;
	char* id;
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

%%
program: 
       declaration
       ;

declaration:
	   statement declaration
	   |
	   ;

statement:
	 expression DOT
	 | block
	 | assignment
	 | fn_decl
	 ;

assignment:
	  IDENTIFIER EQUAL expression DOT
	  ;

fn_decl:
       FN IDENTIFIER LPAREN params RPAREN block
       ;

params:
      | IDENTIFIER COMMA params
      | IDENTIFIER
      | 
      ;

block:
     START declaration END
     ;

expression:
	  term
	  ;

term:
    unary PLUS term
    | unary MINUS term
    | unary
    ;

unary:
     MINUS unary
     | call
     ;

call:
    call LPAREN args RPAREN
    | primary
    ;

args:
    expression COMMA args
    | expression
    | 
    ;

primary:
       INT_LITERAL { std::cout << "found int" << std::endl; } 
       | IDENTIFIER { std::cout << "found identifier" << std::endl; }
       ;
%%

void yyerror(const char* s) {
	std::cerr << "Error: " << s << std::endl;
}
