#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "analyze.h"

/* 行号、源文件、输出文件 */
int lineno = 0;
FILE * source;
FILE * listing;

int Parse = TRUE;
int Analyze = TRUE;
int Execute = TRUE;

int Error = FALSE;
int
main( int argc, char * argv[] )
{	TreeNode * syntaxTree;
	char pgm[120]; /* 源文件名 */
	if (argc != 2)
	{	fprintf(stderr,"usage: %s <filename>\n",argv[0]);
		exit(1);
	}
	strcpy(pgm,argv[1]) ;
	if (strchr (pgm, '.') == NULL)
		strcat(pgm,".cmm");
	source = fopen(pgm,"r");
	if (source==NULL)
	{	fprintf(stderr,"File %s not found\n",pgm);
		exit(1);
	}
	listing = stdout; /* 设置输出为标准输出流 */
	fprintf(listing,"\nCMM Interpretation: %s\n",pgm);

	if (Parse)
	{	syntaxTree = parse();
		fprintf(listing,"\nSyntax tree:\n");
		printTree(syntaxTree);
		if (! Error)
		{	if (Analyze)
			{	fprintf(listing,"\nConstructing symbol table....\n");
				buildSymTab(syntaxTree);
				if(! Error)
				{	fprintf(listing,"\nType checking....\n");
					checkNode(syntaxTree);
					if(! Error)				
						fprintf(listing,"\nResult:Type check completed.\n");
					else
						fprintf(listing,"\nResult:Types of variables have got some errors.。\n");
				}
				else
					fprintf(listing,"\nResult:Some errors occurred in symbol table construction.\n");
			}
			if(!Error && Execute)
			{	fprintf(listing,"\nExecuting....\n\n");
				execTree(syntaxTree);
				if(! Error)
					fprintf(listing,"\n\nResult:Execution Successful.\n");
				else
					fprintf(listing,"\n\nResult:Some errors occurred in Execution.\n");
			}
		}
	}
	fclose(source);
	return 0;
}
