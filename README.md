CMMInterpreter
==============

An interpreter for CMM, a subset of C language. It's written in C, based on GNU Flex &amp; Bison.

It supports following types:
 * int
 * real (float)
 * bool

 and standard I/O:
 * read(var)
 * write(var)
That's all.

Notice: It does not support variable definition with declaration, which means you have to do this: **int var; var = 3;** instead of **int var = 3;**