/*************************************************************/
/* File: util.c                                              */
/* Utility function implementation for the CMM interpreter   */
/* CMM Interpreter Construction                              */
/*************************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

/*	词法分析器接口：
	printToken 输出每个Token和它的类型 
	token代表Token的类型，tokenString代表当前token的具体内容
*/
void printToken( TokenType token )
{	switch (token)
	{	case IF:
		case ELSE:
		case WHILE:
		case READ:
		case WRITE:
		case INT:
		case REAL:
		case BOOL:
			fprintf(listing,
			"reserved word: %s\n", tokenString);
			break;
		case INT_VALUE: 
			fprintf(listing, 
			"Int value: %s\n", tokenString);
			break;
		case REAL_VALUE:
			fprintf(listing, 
			"Real value: %s\n", tokenString);
			break;
		case ID:
			fprintf(listing,
			"Identifier, name: %s\n", tokenString);
			break;
		case PLUS: fprintf(listing, "+\n"); break;
		case SUB: fprintf(listing, "-\n"); break;
		case MUL: fprintf(listing, "*\n"); break;
		case DIV: fprintf(listing, "/\n"); break;
		case UMINUS: fprintf(listing, "-\n"); break;
		case 1: fprintf(listing, "<\n"); break;
		case 2: fprintf(listing, ">\n"); break;
		case 3: fprintf(listing, "<=\n"); break;
		case 4: fprintf(listing, ">=\n"); break;
		case 5: fprintf(listing, "==\n"); break;
		case 6: fprintf(listing, "<>\n"); break;
		case 7: fprintf(listing, "&&\n"); break;
		case 8: fprintf(listing, "||\n"); break;
		case ASSIGN: fprintf(listing, "=\n"); break;
		case LPAREN: fprintf(listing, "(\n"); break;
		case RPAREN: fprintf(listing, ")\n"); break;
		case SEMI: fprintf(listing, ";\n"); break;
		case LBRACE: fprintf(listing, "{\n"); break;
		case RBRACE: fprintf(listing, "}\n"); break;
		case LBRACKET: fprintf(listing, "[\n"); break;
		case RBRACKET: fprintf(listing, "]\n"); break; 
		case ENDFILE: fprintf(listing, "EOF\n"); break;
		case ERROR:
			fprintf(listing,
			"ERROR: %s\n", tokenString);
			break;
		default:/* should never happen */
			fprintf(listing, "Unknown token: %d\n", token);
		}
}	//	printToken end

/*	语法分析器接口：
*/

/* newStmtNode 创建一个新的语句节点 */
TreeNode * newStmtNode(StmtKind kind)
{	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t==NULL)
		fprintf(listing,"Out of memory error at line %d\n",lineno);
	else
	{	/* 初始化一个没有子节点和兄弟节点的语句节点 */
		for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = StmtK;
		t->kind.stmt = kind;
		t->lineno = lineno;
		t->type = Int;
	}
	return t;
}

/* newExpNode 创建一个新的表达式节点 */
TreeNode * newExpNode(ExpKind kind)
{	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t==NULL)
		fprintf(listing,"Out of memory error at line %d\n",lineno);
	else
	{	for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = ExpK;
		t->kind.exp = kind;
		t->lineno = lineno;
		t->type = Int;
	}
	return t;
}

/* copyString 分配一块内存以放置新的字符串，并返回其首地址 */
char * copyString(char * s)
{	int n;
	char * t;
	if (s==NULL) return NULL;
	n = strlen(s)+1;
	t = malloc(n);
	if (t==NULL)
		fprintf(listing,"Out of memory error at line %d\n",lineno);
	else strcpy(t,s);
	return t;
}

/* 缩进数 */
static int indentCount = 0;

/* 改变需要输出的缩进的数目——宏定义 */
#define INDENT indentCount+=2
#define UNINDENT indentCount-=2

/* printSpaces 通过输出空格实现缩进 */
static void printSpaces(void)
{	int i;
	for (i=0;i<indentCount;i++)
	fprintf(listing," ");
}

/* printTree 输出语法树 */
void printTree( TreeNode * tree )
{	int i;			// 子节点计数器
	INDENT;
	while (tree != NULL)
	{	printSpaces();
		if (tree->nodekind==StmtK)
		{	
			switch (tree->kind.stmt)
			{	case IfK:
					fprintf(listing,"If\n");
					break;
				case DeclK:
					fprintf(listing,"Declaration:\n");
					INDENT;
					printSpaces();
					fprintf(listing,"Type: ");
					switch(tree->type)
					{	case Int:
							fprintf(listing,"int ");
							if(0 != tree->arrayLength)	//是数组
								fprintf(listing,"array of %d elements\n",tree->arrayLength);
							else fprintf(listing,"\n");		//不是数组
							break;
						case Real:
							fprintf(listing,"real ");
							if(0 != tree->arrayLength)
								fprintf(listing,"array of %d elements\n",tree->arrayLength);
							else fprintf(listing,"\n");
							break;
						case Bool:
							fprintf(listing,"bool ");
							if(0 != tree->arrayLength)
								fprintf(listing,"array of %d elements\n",tree->arrayLength);
							else fprintf(listing,"\n");
							break;
					}
					printSpaces();
					fprintf(listing,"Id: %s\n",tree->attr.name);
					UNINDENT;
					break;
				case CompoundK:
					fprintf(listing,"CompStmt:\n");
					break;
				case WhileK:
					fprintf(listing,"WhileLoop:\n");
					break;
				case AssignK:
					/* 检查这里是给数组元素赋值还是给一般变量赋值 */
					if(NULL == tree->child[1])
					{	fprintf(listing,"Assign to: %s\n", tree->attr.name);
						break;
					}
					else
						fprintf(listing,"Assign to: %s[]\n", tree->attr.name);
					break;
				case ReadK:
					fprintf(listing,"Read: %s\n",tree->attr.name);
					break;
				case WriteK:
					fprintf(listing,"Write:\n");
					break;
				default:
					fprintf(listing,"Unknown ExpNode kind\n");
					break;
			}
		}
		else if (tree->nodekind==ExpK)
		{	switch (tree->kind.exp)
			{	case OpK:
					fprintf(listing,"Op: ");
					switch(tree->attr.op)
					{	case PLUS: fprintf(listing, "+\n"); break;
						case SUB: fprintf(listing, "-\n"); break;
						case MUL: fprintf(listing, "*\n"); break;
						case DIV: fprintf(listing, "/\n"); break;
						case UMINUS: fprintf(listing, "-\n"); break;
						case 1: fprintf(listing, "<\n"); break;
						case 2: fprintf(listing, ">\n"); break;
						case 3: fprintf(listing, "<=\n"); break;
						case 4: fprintf(listing, ">=\n"); break;
						case 5: fprintf(listing, "==\n"); break;
						case 6: fprintf(listing, "<>\n"); break;
						case 7: fprintf(listing, "&&\n"); break;
						case 8: fprintf(listing, "||\n"); break;
					}
					break;
				case IntValueK:
					fprintf(listing,"Int value: %d\n",tree->value.int_val);
					break;
		    	case RealValueK:
					fprintf(listing,"Real value: %.2lf\n",tree->value.real_val);
					break;
		    	case IdK:
					if (tree->child[0] == NULL)
						fprintf(listing,"Id: %s\n",tree->attr.name);
					else
						fprintf(listing,"Id: %s[]\n",tree->attr.name);
					break;
		    	default:
					fprintf(listing,"Unknown ExpNode kind\n");
					break;
			}
		}
		else
			fprintf(listing,"Unknown node kind\n");
		for (i=0;i<MAXCHILDREN;i++)
			printTree(tree->child[i]);
		tree = tree->sibling;
	}
	UNINDENT;
}	//	printTree end

