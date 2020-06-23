/* print.h
Finally, a print function!
Simply #include "print.h" and call print on whatever you want, up to 16 arguments.
(16 is arbitrary, and the number of arguments print can take can be expanded straightfowardly.)
(You will recieve a, likely inscrutable, compiler error if you exceed the limit, don't worry.)
Can print the same types of data as printf.
In fact, the implementation of the macro uses printf, so this is sort of just a type-safer way of calling that.
(except in-line character literals, because those are by standard promoted to ints on creation. Sorry, I don't make the rules.)
Arguments are evalutated only once in the expanded macro, so stuff like print(i++) is safe.
*/

#include <stdio.h>

//we count on promotion rules I don't understand
//TODO: could replace printf. But is it already optimized out by the compiler?
void _print_int(long long int i){printf("%lld", i);}
void _print_uint(unsigned long long int u){printf("%llu", u);}
void _print_float(double f){printf("%f", f);}
void _print_string(char *s){printf("%s", s);}
void _print_pointer(void *p){printf("%p", p);}
void _print_unknown(unsigned long long int x){printf("%llX", x);} //compiler issues warning in this conversion

#define _print_unit(unit) _Generic( (unit), \
  char: putchar, \
  int: _print_int, \
  long int: _print_int, \
  long long int: _print_int, \
  float: _print_float, \
  double:  _print_float, \
  char *: _print_string, \
  void *: _print_pointer, \
  unsigned int: _print_uint, \
  unsigned long int: _print_uint, \
  unsigned long long int: _print_uint, \
  default: _print_unknown \
) (unit)

//Now, to make the function variadic
// Make a FOREACH macro for up to 16 arguments
#define _FE_0(WHAT)
#define _FE_1(WHAT, X) WHAT(X); 
#define _FE_2(WHAT, X, ...) WHAT(X); _FE_1(WHAT, __VA_ARGS__)
#define _FE_3(WHAT, X, ...) WHAT(X); _FE_2(WHAT, __VA_ARGS__)
#define _FE_4(WHAT, X, ...) WHAT(X); _FE_3(WHAT, __VA_ARGS__)
#define _FE_5(WHAT, X, ...) WHAT(X); _FE_4(WHAT, __VA_ARGS__)
#define _FE_6(WHAT, X, ...) WHAT(X); _FE_5(WHAT, __VA_ARGS__)
#define _FE_7(WHAT, X, ...) WHAT(X); _FE_6(WHAT, __VA_ARGS__)
#define _FE_8(WHAT, X, ...) WHAT(X); _FE_7(WHAT, __VA_ARGS__)
#define _FE_9(WHAT, X, ...) WHAT(X); _FE_8(WHAT, __VA_ARGS__)
#define _FE_10(WHAT, X, ...) WHAT(X); _FE_9(WHAT, __VA_ARGS__)
#define _FE_11(WHAT, X, ...) WHAT(X); _FE_10(WHAT, __VA_ARGS__)
#define _FE_12(WHAT, X, ...) WHAT(X); _FE_11(WHAT, __VA_ARGS__)
#define _FE_13(WHAT, X, ...) WHAT(X); _FE_12(WHAT, __VA_ARGS__)
#define _FE_14(WHAT, X, ...) WHAT(X); _FE_13(WHAT, __VA_ARGS__)
#define _FE_15(WHAT, X, ...) WHAT(X); _FE_14(WHAT, __VA_ARGS__)
#define _FE_16(WHAT, X, ...) WHAT(X); _FE_15(WHAT, __VA_ARGS__)


//This is magic and I don't understand it
//credit to https://stackoverflow.com/a/11994395 and the answers that answer is based on
#define _GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME 
#define _FOR_EACH(action,...) _GET_MACRO(_0,__VA_ARGS__, _FE_16, _FE_15, _FE_14, _FE_13, _FE_12, _FE_11, _FE_10, _FE_9, _FE_8, _FE_7, _FE_6, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1, _FE_0)(action,__VA_ARGS__)
#define print(...) _FOR_EACH(_print_unit,__VA_ARGS__)