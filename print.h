/* print.h
Finally, a print function!
Simply #include "print.h" and call print on whatever you want, up to 16 arguments.
Can print the same types of data as printf.
(except in-line character literals, because those are by standard promoted to ints on creation. Sorry, I don't make the rules.)
Your arguments should be evalutated only once in the expanded macro, so stuff like print(i++) should be safe.
*/

#include <stdio.h>

//we count on promotion rules I don't understand
void _print_int(long long int i){printf("%lld", i);}
void _print_uint(unsigned long long int u){printf("%llu", u);}
void _print_float(double f){printf("%f", f);}
void _print_string(char *s){printf("%s", s);}
void _print_pointer(void *p){printf("%p", p);}
void _print_unknown(unsigned int x){printf("%x", x);}

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