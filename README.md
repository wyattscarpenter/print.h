# print.h
Finally, a print function! A compile-time-type-safe, variadic, free-form print() function, fully standard-compliant, C11 and later.

Have you ever wanted to write, eg, `print("here's some string", some_other_variable)`? Well, now you can, and it will usually just work! print.h can print the same types of data as printf, and a few more! And you can add your own!

And now, further information from the top comment of the print.h file:

Simply #include "print.h" and call print on whatever you want, 1 to 32 arguments.

32 is arbitrary, and the number of arguments print can take can be expanded straightforwardly.

You will receive a compile-time warning if you exceed the limit, don't worry.

labelled_print is like print, but will also print out the names of the variables being printed, convenient for debugging.

Written in and for pure C.

In fact, the implementation of the macro uses printf, so this is sort of just a safer and more convenient way of calling printf.

Can print arrays of any size, unless they are the same size as a pointer.

However, we can't print inline character literals, because those are by standard promoted to ints on creation, or something. Sorry, I don't make the rules. Use inline string literals instead.

Arguments are evaluated only once at run time in the expanded macro, so stuff like print(i++) is safe.

Only a handful of symbols are introduced into the namespace, most of them printing functions.

print cannot be used as an expression, only as a statement (it has no return value), and cannot take 0 arguments.

The "header" file currently includes implementations.

The header file currently #includes stdio.h, so don't bother double-including stdio.h.

I release this code into the public domain under CC0.
