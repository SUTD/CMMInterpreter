/***********************************/
/* File: cmm.l    version 2.0      */
/* Flex version for CMM            */
/* CMM Interpreter Construction    */
/***********************************/
%option noyywrap
%{
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "cmm.tab.h"
%}

digit		[0-9]
int_num		{digit}+
real_num	{digit}+"."{digit}*
letter		[a-zA-Z]
identifier	{letter}+({letter}|{digit}|_)*({letter}+|{digit}+)|{letter}+
whitespace	[ \t]*

%%

"if"		{ return IF;}
"else"		{ return ELSE;}
"while"		{ return WHILE;}
"int"		{ yylval.dataType = Int; return INT;} 
"real"		{ yylval.dataType = Real; return REAL;}
"bool"		{ yylval.dataType = Bool; return BOOL;}
"read"		{ return READ;}
"write"		{ return WRITE;}
"main"		{ return MAIN;}

{int_num}		{ yylval.intval = atoi(yytext); return INT_VALUE;}
{real_num}		{ yylval.realval = atof(yytext); return REAL_VALUE;}
{identifier}	{ yylval.idName = copyString(yytext); return ID;}
{whitespace}	{/*Do nothing.*/}

"+"		{ return PLUS;}
"-"		{ return SUB;}
"*"		{ return MUL;}
"/"		{ return DIV;}
"<"		{ yylval.binaryOperator = 1; return REL_OP;}
">"		{ yylval.binaryOperator = 2; return REL_OP;}
"<="	{ yylval.binaryOperator = 3; return REL_OP;}
">="	{ yylval.binaryOperator = 4; return REL_OP;}
"=="	{ yylval.binaryOperator = 5; return REL_OP;}
"<>"	{ yylval.binaryOperator = 6; return REL_OP;}
"&&"	{ yylval.binaryOperator = 7; return REL_OP;}
"||"	{ yylval.binaryOperator = 8; return REL_OP;}

"="		{ return ASSIGN;}
"("		{ return LPAREN;}
")"		{ return RPAREN;}
";"		{ return SEMI;}
"{"		{ return LBRACE;}
"}"		{ return RBRACE;}
"["		{ return LBRACKET;}
"]"		{ return RBRACKET;}
","		{ return COMMA;}

"//"	{ char c = input();
		  while(c != '\n')
		  {	if (c == EOF) break;
		  	c = input();
		  }
		  lineno++;
		}
"/*"	{	char c;
			int flag = 1;
			do
			{	c = input();
				entry1:
				if (c == EOF) break;
				if (c == '\n') lineno++;
				if (c == '*')
				{	c = input();
					if (c == '/')
						flag = 0;
					else
						goto entry1;
				}
			} while (flag);
		}
\n		{lineno++;}
.		{yyerror("Mystery character %s\n", yytext);return ERROR;}

%%
/* 用于语法分析时初始化词法分析接口 */
void iniLexer(void)
{
	static int firstTime = TRUE;
	lineno = 0;
	if (firstTime)
	{	firstTime = FALSE;
		lineno++;
		yyin = source;
		yyout = listing;
	}
}
/* 词法分析器专用 
TokenType getToken(void)
{	static int firstTime = TRUE;
	TokenType currentToken;
	if (firstTime)
	{	firstTime = FALSE;
		lineno++;
		yyin = source;
		yyout = listing;
	}
	currentToken = yylex();
	strncpy(tokenString,yytext,MAXTOKENLEN);
	if (TraceScan) {
		fprintf(listing,"\t%d: ",lineno);
		printToken(currentToken);
	}
	return currentToken;
}*/
