%{
#include "parser.hpp"
#include <iostream>

extern YYSTYPE yylval;
%}

%%

\t|\n|" " {/* skip whitespace */ } 

fn 	{ return FN; }
return 	{ return RETURN; }
if 		{ return IF; }
else 	{ return ELSE; }


[0-9]+  { yylval.intval = atoi(yytext); return INT_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return IDENTIFIER; }

"+"	{ return PLUS; }
"-"	{ return MINUS; }
"*" { return STAR; }
"/" { return SLASH; }
"="	{ return EQUAL; }
"<" { return LESS; }
"<=" { return LESS_EQUAL; }
">" { return GREATER; }
">=" { return GREATER_EQUAL; }
"==" { return EQUAL_EQUAL; }
"!=" { return NOT_EQUAL; }
"("	{ return LPAREN; }
")"	{ return RPAREN; }
"{"  	{ return LBRACE; }
"}" 	{ return RBRACE; }
"("		{ return LPAREN; }
")" 	{ return RPAREN; }
";"	{ return SEMICOLON; }
","	{ return COMMA; }

%%

int yywrap() {
	return 1;
}

void scanner_destroy() {
	yylex_destroy();
}

void scanner_init(const char* code) {
	yy_scan_string(code);
}

