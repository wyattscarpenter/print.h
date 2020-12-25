/*print.h - Finally, a print function!
  Simply #include "print.h" and call print on whatever you want, 1 to 32 arguments.
  32 is arbitrary, and the number of arguments print can take can be expanded straightfowardly.
  You will recieve a compile-time warning if you exceed the limit, don't worry.
  Written in and for pure C.
  Fully standard-compliant, C11 and later.
  Can print the same types of data as printf, and a few more! And you can add your own!
  In fact, the implementation of the macro uses printf, so this is sort of just a safer and more convenient way of calling printf.
  However, we can't print inline character literals, because those are by standard promoted to ints on creation, or something.
  Sorry, I don't make the rules. Use inline string literals instead.
  Arguments are evalutated only once at run time in the expanded macro, so stuff like print(i++) is safe.
  Only a handful of symbols are introduced into the namespace, most of them printing functions.
  I release this code into the public domain under CC0.
*/

#ifndef _PRINT_H
#define _PRINT_H

#include <stdio.h>

typedef struct {unsigned char nothing;} _dont_print;
//typedef struct {unsigned char nothing;} custom_type; //even though this type is structurally identical to _dont_print, it is still printed properly

//We rely on type promotion rules I frankly don't really understand.
//could replace printf. But this way the code is more likely to be correct. Also, is it already optimized out by the compiler?
void _print_char(char c, int size){printf("%c", c);}
void _print_int(long long int i, int size){printf("%lld", i);}
void _print_uint(unsigned long long int u, int size){printf("%llu", u);}
void _print_float(long double f, int size){printf("%LG", f);} //L: Long float, G: automatically chooses whether to use scientific notation
void _print_string(char *s, int size){printf("%s", s);}
void _print_pointer(void *p, int size){printf("%p", p);}
void _print_int_pointer(int *p, int size){
  if(size == sizeof(p)){
    _print_pointer(p, sizeof(p));
  } else {
    printf("{");
    if(size >= sizeof(*p)){
      printf("%d", *p); //this is complicated a bit by the fact that we don't want a trailing , at the end of our array printout.
      for(int i = 1; i < size/sizeof(*p); i++){
        printf(", %d", p[i]);
      }
    }
    printf("}");
  }
}
void _print_2d_int_pointer(void *p, int size){_print_int_pointer((int*)p, size);} //ironic that I have to take a void pointer here to erase the type info that I can't use. So close, yet so far.
//An alternative would be making n of these functions (dispatching to int (*)[n] in the _Generic), which isn't very good.
void _print_dont_print(_dont_print dont, int size){} //could also use ... instead of int size if we need to throw out a variable number of arguments in the future
//void _print_custom(custom_type c){putchar(c.nothing);} //works fine

#define _print_unit(unit) _Generic( (unit), \
  char: _print_char, \
  int: _print_int, \
  long int: _print_int, \
  long long int: _print_int, \
  float: _print_float, \
  double:  _print_float, \
  long double:  _print_float, \
  char *: _print_string, \
  void *: _print_pointer, \
  int *: _print_int_pointer, \
  int **: _print_pointer, \
  int (*)[]: _print_2d_int_pointer, \
  unsigned int: _print_uint, \
  unsigned long int: _print_uint, \
  unsigned long long int: _print_uint, \
  _dont_print: _print_dont_print \
  /*custom_type: _print_custom, //you can add your types like this */ \
) (unit, sizeof(unit))

//Now, to make the function variadic.
//"You are without doubt the worst variadicity I've ever implemented." "But you have implemented me."
#define _print_each(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _boundary_sentinel, ...) do{ /*the ol' do-while(0) trick*/ _print_unit(_1); _print_unit(_2); _print_unit(_3); _print_unit(_4); _print_unit(_5); _print_unit(_6); _print_unit(_7); _print_unit(_8); _print_unit(_9); _print_unit(_10); _print_unit(_11); _print_unit(_12); _print_unit(_13); _print_unit(_14); _print_unit(_15); _print_unit(_16); _print_unit(_17); _print_unit(_18); _print_unit(_19); _print_unit(_20); _print_unit(_21); _print_unit(_22); _print_unit(_23); _print_unit(_24); _print_unit(_25); _print_unit(_26); _print_unit(_27); _print_unit(_28); _print_unit(_29); _print_unit(_30); _print_unit(_31); _print_unit(_32); _Static_assert(_Generic((_boundary_sentinel), _dont_print: 1, default: 0 ), "Too many arguments supplied to print. Please do not do that, or simply edit the source code to expand the function."); } while(0)
#define print(...) _print_each(__VA_ARGS__, (_dont_print){1}, (_dont_print){2}, (_dont_print){3}, (_dont_print){4}, (_dont_print){5}, (_dont_print){6}, (_dont_print){7}, (_dont_print){8}, (_dont_print){9}, (_dont_print){10}, (_dont_print){11}, (_dont_print){12}, (_dont_print){13}, (_dont_print){14}, (_dont_print){15}, (_dont_print){16}, (_dont_print){17}, (_dont_print){18}, (_dont_print){19}, (_dont_print){20}, (_dont_print){21}, (_dont_print){22}, (_dont_print){23}, (_dont_print){24}, (_dont_print){25}, (_dont_print){26}, (_dont_print){27}, (_dont_print){28}, (_dont_print){29}, (_dont_print){30}, (_dont_print){31}, (_dont_print){32}, (_dont_print){0}) //the (_dont_print){x}s are arbitrary placeholders that are known by type to be ignored

#endif
