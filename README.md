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

Syntax tree:
  Declaration:
    Type: int
    Id: a
  Assign to: a
    Int value: 6
  Declaration:
    Type: real
    Id: factor
  Assign to: factor
    Int value: 1
  WhileLoop:
    Op: <>
      Id: a
      Int value: 0
    CompStmt:
      Assign to: factor
        Op: *
          Id: factor
          Id: a
      Assign to: a
        Op: -
          Id: a
          Int value: 1
  Write:
    Id: factor

Symbol table:
	/-----------------------------------\
	|  VarName    Type IsArray DeclLine |
	|------------ ---- ------- ---------|
	|  factor     Real    0      7      |
	|  a          Int     0      4      |
	\-----------------------------------/

That's all.  Have fun. ;-D

Notice: It does not support variable definition with declaration, which means you have to do this: **int var; var = 3;** instead of **int var = 3;** Same for arrays.