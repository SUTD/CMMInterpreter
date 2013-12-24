/***********************************/
/* File: cmm.y                     */
/* Bison grammar file about CMM    */
/* CMM Interpreter Construction    */
/***********************************/

/*预计有1个移进/归约冲突*/
%expect 1
%{

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TreeNode * savedTree; /* stores syntax tree for later return */

%}

%union{
	struct treeNode * node;
	int intval;
	double realval;
	char * idName;
	int binaryOperator;
	int dataType;
}
%token <intval> INT_VALUE
%token <realval> REAL_VALUE
%token <idName> ID
%token <dataType> INT REAL BOOL

/* 优先级声明 */
%right ASSIGN
%left PLUS SUB
%left MUL DIV
%nonassoc <binaryOperator> REL_OP
%nonassoc UMINUS
/* 声明文法中用到的tokens */
%token IF ELSE WHILE READ WRITE MAIN
%token LPAREN RPAREN SEMI LBRACE RBRACE LBRACKET RBRACKET COMMA
%token ASSIGN
%token NEWLINE ERROR

%type <node> stmt_list stmt
%type <node> if_stmt decl_stmt compound_stmt while_stmt assign_stmt read_stmt write_stmt
%type <node> exp factor bin_exp
%type <dataType> type_spec

%start program

%% /* CMM文法 */

program		: stmt_list
				{ savedTree = $1;}
			;
stmt_list	:	{ $$ = NULL; }
			| stmt_list stmt 
				{	TreeNode * t = $1;
					if (t != NULL)
					{	while (t->sibling != NULL){ t = t->sibling;}
						t->sibling = $2;
						$$ = $1;
					}
					else $$ = $2;
				}
			;
stmt		: if_stmt { $$ = $1; }
			| decl_stmt SEMI { $$ = $1; }
			| compound_stmt { $$ = $1; }
			| while_stmt { $$ = $1; }
			| assign_stmt SEMI { $$ = $1; }
			| read_stmt SEMI { $$ = $1; }
			| write_stmt SEMI { $$ = $1; }
			| error  { $$ = NULL; }
			;
compound_stmt
			: LBRACE stmt_list RBRACE
				{	$$ = newStmtNode(CompoundK);
					$$->child[0] = $2;
					$$->lineno = lineno;
				}
			;
decl_stmt	: type_spec ID 
				{	$$ = newStmtNode(DeclK);
					$$->attr.name = $2;
					/* 数组长度为0代表非数组 */
					$$->arrayLength = 0;
					$$->type = $1;
					$$->lineno = lineno;
				}
			| type_spec ID LBRACKET INT_VALUE RBRACKET
				{	$$ = newStmtNode(DeclK);
					$$->attr.name = $2;
					$$->arrayLength = $4;
					$$->type = $1;
					if($$->type == Int) {
						int int_array_temp[$4];
						$$->array.intArray = int_array_temp;
					}
					else if($$->type == Real) {
						double real_array_temp[$4];
						$$->array.realArray = real_array_temp;
					}
					$$->lineno = lineno;
				}
			;
type_spec	: INT 	{ $$ = $1; }
			| REAL 	{ $$ = $1; }
			| BOOL	{ $$ = $1; }
			;
if_stmt     : IF LPAREN bin_exp RPAREN stmt
				{	$$ = newStmtNode(IfK);
					$$->child[0] = $3;
					$$->child[1] = $5;
					$$->child[2] = NULL;
					$$->lineno = lineno;
				}
			| IF LPAREN bin_exp RPAREN stmt ELSE stmt
				{	$$ = newStmtNode(IfK);
					$$->child[0] = $3;
					$$->child[1] = $5;
					$$->child[2] = $7;
					$$->lineno = lineno;
				}
			;
while_stmt	: WHILE LPAREN bin_exp RPAREN stmt
				{	$$ = newStmtNode(WhileK);
					$$->child[0] = $3;
					$$->child[1] = $5;
					$$->lineno = lineno;
				}
			;
assign_stmt : ID ASSIGN exp
				{	$$ = newStmtNode(AssignK);
					$$->attr.name = $1;
					$$->child[0] = $3;
					$$->child[1] = NULL;
					$$->lineno = lineno;
				}
			| ID LBRACKET exp RBRACKET ASSIGN exp
				{	$$ = newStmtNode(AssignK);
					$$->attr.name = $1;
					/* child[1]不为NULL 表示引用的变量是一个数组元素 */
					/* child[0] 是数组元素的下标 */
					$$->child[0] = $3;
					$$->child[1] = $6;
					$$->lineno = lineno;
				}
			;
read_stmt   : READ LPAREN ID RPAREN
				{	$$ = newStmtNode(ReadK);
					$$->attr.name = $3;
					$$->child[0] = NULL;
					$$->lineno = lineno;
				}
			| READ LPAREN ID LBRACKET exp RBRACKET RPAREN
				{	$$ = newStmtNode(ReadK);
					$$->attr.name = $3;
					$$->child[0] = $5;
					$$->lineno = lineno;
				}
			;
write_stmt  : WRITE LPAREN exp RPAREN
				{	$$ = newStmtNode(WriteK);
					$$->child[0] = $3;
					$$->lineno = lineno;
				}
			;
exp			: factor
				{	$$ = $1; }
			| bin_exp
				{	$$ = $1; }
			;
factor		: INT_VALUE
				{	$$ = newExpNode(IntValueK);
					$$->value.int_val = $1;
					$$->type = Int;
					$$->lineno = lineno;
				}
			| REAL_VALUE
				{	$$ = newExpNode(RealValueK);
					$$->value.real_val = $1;
					$$->type = Real;
					$$->lineno = lineno;
				}
			| LPAREN exp RPAREN
				{	$$ = $2; }
			| ID
				{	$$ = newExpNode(IdK);
					$$->attr.name = $1;
					/* child[0]为NULL代表该变量不是数组，用作解释时 */
					$$->child[0] = NULL;
					$$->lineno = lineno;
				}
			| ID LBRACKET exp RBRACKET
				{	$$ = newExpNode(IdK);
					$$->attr.name = $1;
					$$->child[0] = $3;
					$$->lineno = lineno;
				}
			| error { $$ = NULL; }
			;
bin_exp     : /* 关系运算符 */
			  exp REL_OP exp
				{	$$ = newExpNode(OpK);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = $2;
					$$->lineno = lineno;
				}
			/* 算数运算符 */
			| exp PLUS exp
				{	$$ = newExpNode(OpK);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = PLUS;
					$$->lineno = lineno;
				}
			| exp SUB exp
				{	$$ = newExpNode(OpK);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = SUB;
					$$->lineno = lineno;
				}
			| exp MUL exp
				{	$$ = newExpNode(OpK);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = MUL;
					$$->lineno = lineno;
				}
			| exp DIV exp
				{	$$ = newExpNode(OpK);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = DIV;
					$$->lineno = lineno;
				}
			| SUB exp %prec UMINUS
				{	$$ = newExpNode(OpK);
					$$->child[0] = $2;
					$$->child[1] = NULL;
					$$->attr.op = UMINUS;
					$$->lineno = lineno;
				}
			;

%%

int yyerror(char * message)
{	fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
	fprintf(listing,"Current token: %s",tokenString);
	printToken(yychar);
	Error = TRUE;
	return 0;
}
/* 与主函数交互的语法分析函数 */
TreeNode * parse(void)
{	iniLexer();
	yyparse();
	return savedTree;
}
