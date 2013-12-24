CMMInterpreter
==============
C Minus Minus, or C--, is a subset of C programming language.

Here is an interpreter for CMM, run in command line. It's written in C, based on GNU Flex &amp; Bison, which can be easily installed in Linux. You would already have them if you've installed Xcode on your mac.

It supports following types:
* int
* real(float)
* bool
* array

loops:
* while

and standard I/O:
* read(var)
* write(var)

You don't need to write **main** function, actually it doesn't support function. It also supports comments, both /*comment*/ and //comment .
You can use **-t** to let the interpreter print the **syntax tree**, but you may only put the sign at the last position of line like this: **./interpreter test2.cmm -s**

Syntax tree:<br>
&nbsp;Declaration:<br>
&nbsp;&nbsp;Type: int<br>
&nbsp;&nbsp;Id: a<br>
&nbsp;Assign to: a<br>
&nbsp;&nbsp;Int value: 6<br>
&nbsp;Declaration:<br>
&nbsp;&nbsp;Type: real<br>
&nbsp;&nbsp;Id: factor<br>
&nbsp;Assign to: factor<br>
&nbsp;&nbsp;Int value: 1<br>
&nbsp;WhileLoop:<br>
&nbsp;&nbsp;Op: <><br>
&nbsp;&nbsp;Id: a<br>
&nbsp;&nbsp;Int value: 0<br>
&nbsp;&nbsp;CompStmt:<br>
&nbsp;&nbsp;&nbsp;Assign to: factor<br>
&nbsp;&nbsp;&nbsp;Op: *<br>
&nbsp;&nbsp;&nbsp;&nbsp;Id: factor<br>
&nbsp;&nbsp;&nbsp;&nbsp;Id: a<br>
&nbsp;&nbsp;Assign to: a<br>
&nbsp;&nbsp;&nbsp;Op: -<br>
&nbsp;&nbsp;&nbsp;&nbsp;Id: a<br>
&nbsp;&nbsp;&nbsp;&nbsp;Int value: 1<br>
&nbsp;Write:<br>
&nbsp;&nbsp;Id: factor

Symbol table:
	+-----------------------------------+<br>
	|  VarName   |Type|IsArray|DeclLine |<br>
	|------------+----+-------+---------|<br>
	|  factor    |Real|   0   |    7    |<br>
	|  a         |Int |   0   |    4    |<br>
	+-----------------------------------+

That's all.  Have fun. ;-D

Notice: It does not support variable definition with declaration, which means you have to do this: **int var; var = 3;** instead of **int var = 3;** Same for arrays.