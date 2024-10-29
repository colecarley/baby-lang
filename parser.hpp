/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 2 "parser.y"

#include <iostream>
#include <string>
#include "ast.hpp"

void yyerror(ASTNode** root, const char* code, const char* s);
void baby_parse(ASTNode** root, const char* code);

extern int yylex();
extern void scanner_destroy();
extern void scanner_init(const char* code);

#line 62 "parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FN = 258,                      /* FN  */
    RETURN = 259,                  /* RETURN  */
    LBRACE = 260,                  /* LBRACE  */
    RBRACE = 261,                  /* RBRACE  */
    END = 262,                     /* END  */
    IDENTIFIER = 263,              /* IDENTIFIER  */
    INT_LITERAL = 264,             /* INT_LITERAL  */
    PLUS = 265,                    /* PLUS  */
    MINUS = 266,                   /* MINUS  */
    STAR = 267,                    /* STAR  */
    SLASH = 268,                   /* SLASH  */
    LESS = 269,                    /* LESS  */
    GREATER = 270,                 /* GREATER  */
    LESS_EQUAL = 271,              /* LESS_EQUAL  */
    GREATER_EQUAL = 272,           /* GREATER_EQUAL  */
    EQUAL_EQUAL = 273,             /* EQUAL_EQUAL  */
    NOT_EQUAL = 274,               /* NOT_EQUAL  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    IF = 277,                      /* IF  */
    ELSE = 278,                    /* ELSE  */
    COMMA = 279,                   /* COMMA  */
    EQUAL = 280,                   /* EQUAL  */
    LPAREN = 281,                  /* LPAREN  */
    RPAREN = 282,                  /* RPAREN  */
    SEMICOLON = 283,               /* SEMICOLON  */
    BB_EOF = 284                   /* BB_EOF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "parser.y"

	int intval;
	char* id;
    ASTNode* node;
    ASTNodeBlock* block;
    ASTNodeParameters* param_list;
    ASTNodeArguments* arg_list;

#line 117 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (ASTNode** root, const char* code);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
