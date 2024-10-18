%{
#include "parser.hpp"
#include <iostream>

extern YYSTYPE yylval;

%}

%%

\t|\n|" " {/* skip whitespace */ } 

fn 	{ return FN; }
return 	{ return RETURN; }
start  	{ return START; }
end 	{ return END; }

[0-9]+  { yylval.intval = atoi(yytext); return INT_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return IDENTIFIER; }

"+"	{ return PLUS; }
"-"	{ return MINUS; }
"="	{ return EQUAL; }
"("	{ return LPAREN; }
")"	{ return RPAREN; }
"."	{ return DOT; }
","	{ return COMMA; }

%%

int yywrap() {
	return 1;
}
