/* print.h
Finally, a print function!
Simply #include "print.h" and call print on whatever you want, up to 16 arguments.
(16 is arbitrary, and the number of arguments print can take can be expanded straightfowardly.)
(You will recieve no warning if you exceed the limit, further args simply will not print)
Fully standard-compliant under C11 and later.
Can print the same types of data as printf.
(In fact, the implementation of the macro uses printf, so this is sort of just a safer and more convenient way of calling printf.)
(However, we can't print inline character literals, because those are by standard promoted to ints on creation, or something.
 Sorry, I don't make the rules. Use inline string literals instead.)
Arguments are evalutated only once in the expanded macro, so stuff like print(i++) is safe.
*/

#ifndef _PRINT_H
#define _PRINT_H

#include <stdio.h>

typedef struct {char nothing;} _dont_print;
_dont_print _placeholder;


//We rely on promotion rules I don't really understand.
//TODO: could replace printf. But is it already optimized out by the compiler?
void _print_int(long long int i){printf("%lld", i);}
void _print_uint(unsigned long long int u){printf("%llu", u);}
void _print_float(long double f){printf("%LG", f);} //L: Long float, G: automatically chooses whether to use scientific notation
void _print_string(char *s){printf("%s", s);}
void _print_pointer(void *p){printf("%p", p);}
void _print_dont_print(){} 
void _print_unknown(unsigned long long int x){printf("%llX", x);} //compiler issues warning in this conversion

#define _print_unit(unit) _Generic( (unit), \
  char: putchar, \
  int: _print_int, \
  long int: _print_int, \
  long long int: _print_int, \
  float: _print_float, \
  double:  _print_float, \
  long double:  _print_float, \
  char *: _print_string, \
  void *: _print_pointer, \
  int *: _print_pointer, \
  int **: _print_pointer, \
  unsigned int: _print_uint, \
  unsigned long int: _print_uint, \
  unsigned long long int: _print_uint, \
  _dont_print: _print_dont_print, \
  default: _print_unknown \
) (unit)

//#define _halt_print_and_catch_fire(i) _Static_assert(i, "too many") //hmm TODO: check bounds at compile time

//Now, to make the function variadic.
//"You are without doubt the worst variadicity I've ever implemented." "But you have implemented me."
#define _print_each(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _bound, ...) do{ /*the ol' do-while(0) trick*/ _print_unit(_1); _print_unit(_2); _print_unit(_3); _print_unit(_4); _print_unit(_5); _print_unit(_6); _print_unit(_7); _print_unit(_8); _print_unit(_9); _print_unit(_10); _print_unit(_11); _print_unit(_12); _print_unit(_13); _print_unit(_14); _print_unit(_15); _print_unit(_16); _print_unit(_Generic((_bound), _dont_print: "", default: " etc\n" )); } while(0)
#define print(...) _print_each(__VA_ARGS__, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder, _placeholder)

#endif
