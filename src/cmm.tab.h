/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_VALUE = 258,
     REAL_VALUE = 259,
     ID = 260,
     INT = 261,
     REAL = 262,
     BOOL = 263,
     ASSIGN = 264,
     SUB = 265,
     PLUS = 266,
     DIV = 267,
     MUL = 268,
     REL_OP = 269,
     UMINUS = 270,
     IF = 271,
     ELSE = 272,
     WHILE = 273,
     READ = 274,
     WRITE = 275,
     MAIN = 276,
     LPAREN = 277,
     RPAREN = 278,
     SEMI = 279,
     LBRACE = 280,
     RBRACE = 281,
     LBRACKET = 282,
     RBRACKET = 283,
     COMMA = 284,
     NEWLINE = 285,
     ERROR = 286
   };
#endif
/* Tokens.  */
#define INT_VALUE 258
#define REAL_VALUE 259
#define ID 260
#define INT 261
#define REAL 262
#define BOOL 263
#define ASSIGN 264
#define SUB 265
#define PLUS 266
#define DIV 267
#define MUL 268
#define REL_OP 269
#define UMINUS 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define READ 274
#define WRITE 275
#define MAIN 276
#define LPAREN 277
#define RPAREN 278
#define SEMI 279
#define LBRACE 280
#define RBRACE 281
#define LBRACKET 282
#define RBRACKET 283
#define COMMA 284
#define NEWLINE 285
#define ERROR 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "cmm.y"
{
	struct treeNode * node;
	int intval;
	double realval;
	char * idName;
	int binaryOperator;
	int dataType;
}
/* Line 1529 of yacc.c.  */
#line 120 "cmm.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

