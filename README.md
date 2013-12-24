CMMInterpreter
==============
C Minus Minus, or C--, is a subset of C programming language.

Here is an interpreter for CMM, run in command line. It's written in C, based on GNU Flex &amp; Bison, which can be easily installed in Linux. You would already have them if you've installed Xcode on your mac.

Work flow:

![alt tag](https://raw.github.com/hukun01/CMMInterpreter/master/Work%20flow.png)

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

You don't need to write **main** function, actually it doesn't support function. It also supports comments, both /\*comment\*/ and //comment .
You can use **-t** to let the interpreter print the **syntax tree**, but you may only put the sign at the last position of line like this: **./interpreter test2.cmm -s**

Syntax tree:

![alt tag](https://raw.github.com/hukun01/CMMInterpreter/master/syntax%20Tree%20of%20test1.png)

Symbol table:

![alt tag](https://raw.github.com/hukun01/CMMInterpreter/master/symbol%20Table%20of%20test1.png)

That's all.  Have fun. ;-D

Notice: It does not support variable definition with declaration, which means you have to do this: **int var; var = 3;** instead of **int var = 3;** Same for arrays.