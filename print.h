/* print.h
Finally, a print function!
Simply #include "print.h" and call print on whatever you want, 1 to 16 arguments.
(16 is arbitrary, and the number of arguments print can take can be expanded straightfowardly.)
(You will recieve a compile-time warning if you exceed the limit, don't worry)
Fully standard-compliant, C11 and later.
Can print the same types of data as printf, and a few more! Add your own!
(In fact, the implementation of the macro uses printf, so this is sort of just a safer and more convenient way of calling printf.)
(However, we can't print inline character literals, because those are by standard promoted to ints on creation, or something.
 Sorry, I don't make the rules. Use inline string literals instead.)
Arguments are evalutated only once in the expanded macro, so stuff like print(i++) is safe.
*/

#ifndef _PRINT_H
#define _PRINT_H

#include <stdio.h>

typedef struct {char nothing;} _dont_print;
//typedef struct {char nothing;} custom_type; //even though this type is structurally identical to _dont_print, it is still printed properly

//We rely on type promotion rules I frankly don't really understand.
//TODO: could replace printf. But is it already optimized out by the compiler?
void _print_int(long long int i){printf("%lld", i);}
void _print_uint(unsigned long long int u){printf("%llu", u);}
void _print_float(long double f){printf("%LG", f);} //L: Long float, G: automatically chooses whether to use scientific notation
void _print_string(char *s){printf("%s", s);}
void _print_pointer(void *p){printf("%p", p);}
void _print_dont_print(){} 
//void _print_custom(custom_type c){putchar(c.nothing);} //works fine
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
  /*custom_type: _print_custom, //you can add your types like this */ \
  default: _print_unknown \
) (unit)

//Now, to make the function variadic.
//"You are without doubt the worst variadicity I've ever implemented." "But you have implemented me."
#define _print_each(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _bound, ...) do{ /*the ol' do-while(0) trick*/ _print_unit(_1); _print_unit(_2); _print_unit(_3); _print_unit(_4); _print_unit(_5); _print_unit(_6); _print_unit(_7); _print_unit(_8); _print_unit(_9); _print_unit(_10); _print_unit(_11); _print_unit(_12); _print_unit(_13); _print_unit(_14); _print_unit(_15); _print_unit(_16); _Static_assert(_Generic((_bound), _dont_print: 1, default: 0 ), "Too many arguments supplied to print. Please do not do that, or simply edit the source code to expand the function."); } while(0)
#define print(...) _print_each(__VA_ARGS__, (_dont_print){1}, (_dont_print){2}, (_dont_print){3}, (_dont_print){4}, (_dont_print){5}, (_dont_print){6}, (_dont_print){7}, (_dont_print){8}, (_dont_print){9}, (_dont_print){10}, (_dont_print){11}, (_dont_print){12}, (_dont_print){13}, (_dont_print){14}, (_dont_print){15}, (_dont_print){16}, (_dont_print){0}) //the (_dont_print){x}s are arbitrary placeholders that are known by type to be ignored

#endif
