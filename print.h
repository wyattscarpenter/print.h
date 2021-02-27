/*print.h - Finally, a print function!
  A compile-time-type-safe, variadic, free-form print() function, fully standard-compliant, C11 and later.
  Simply #include "print.h" and call print on whatever you want, 1 to 32 arguments.
  32 is arbitrary, and the number of arguments print can take can be expanded straightforwardly.
  You will receive a compile-time warning if you exceed the limit, don't worry.
  labelled_print is like print, but will also print out the names of the variables being printed, convenient for debugging.
  Written in and for pure C.
  Can print the same types of data as printf, and a few more! And you can add your own!
  In fact, the implementation of the macro uses printf, so this is sort of just a safer and more convenient way of calling printf.
  Can print arrays of any size, unless they are the same size as a pointer.
  However, we can't print inline character literals, because those are by standard promoted to ints on creation, or something.
  Sorry, I don't make the rules. Use inline string literals instead.
  Arguments are evaluated only once at run time in the expanded macro, so stuff like print(i++) is safe.
  Only a handful of symbols are introduced into the namespace, most of them printing functions.
  print cannot be used as an expression, only as a statement (it has no return value), and cannot take 0 arguments.
  This "header" file currently includes implementations, as I'm not quite sure how I want to architect it more properly.
  This header file currently #includes stdio.h, so don't bother double-including stdio.h.
  I release this code into the public domain under CC0.
*/

#ifndef _PRINT_H
#define _PRINT_H

#include <stdio.h>

typedef struct {unsigned char nothing;} _dont_print;
typedef struct {int size; void* data;} _printable_bytes;
//typedef struct {unsigned char nothing;} custom_type; //even though this type is structurally identical to _dont_print, it is still printed properly

#define printable_bytes(a) ((_printable_bytes){sizeof(a), &a}) //note that it would be absolutely fine to have this function macro and a datatype share the same name, they would not conflict. But, this is exposed to the user so we don't start it with an underscore.
#ifndef __has_builtin //check for builtins from compilers that implement this scheme (ie, gcc or clang)
 #define __has_builtin(x) 0  // compatibility for compilers that don't implement this macro
#endif

#if __has_builtin(__builtin_dump_struct)
  #define printable_struct(s) (__builtin_dump_struct(&(s), &printf),"") //suppress printing of return value using comma operator.
#else
  #define printable_struct(s) printable_bytes(s)
#endif

//These functions are all static so multiple definitions from multiple inclusions across multiple files isn't a problem.
/*//Note: I've been told a cool way to deal with a particular problem goes like:
#ifndef _print_export_status
#define _print_export_status static
#endif
_print_export_status void _print_char(void); //etc
//and you want the functions not to be static you can put
#define _print_export_status //just define it as nothing so _print_export_status produces no annotation
//somewhere to get that behavior. This is very slick, and seems better than than the stb.h method ( as used in https://github.com/nothings/stb/blob/master/stb.h ) as that requires the library user to #define STB_DEFINE somewhere for it to work at all, instead of just for the special behavior. However, I don't ACTUALLY know what problem this is supposed to solve, so I'm not going to implement it until someone actually requests it.
*/

//We rely on type promotion rules I frankly don't really understand.
//could replace printf. But this way the code is more likely to be correct. Also, is it already optimized out by the compiler?
static void _print_char(char c, int size){printf("%c", c);}
static void _print_int(long long int i, int size){printf("%lld", i);}
static void _print_uint(unsigned long long int u, int size){printf("%llu", u);}
static void _print_float(long double f, int size){printf("%LG", f);} //L: Long float, G: automatically chooses whether to use scientific notation
static void _print_string(char *s, int size){printf("%s", s);}
static void _print_pointer(void *p, int size){printf("%p", p);}
static void _print_int_pointer(int *p, int size){
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
static void _print_2d_int_pointer(void *p, int size){_print_int_pointer((int*)p, size);} //ironic that I have to take a void pointer here to erase the type info that I can't use. So close, yet so far.
//An alternative would be making n of these functions (dispatching to int (*)[n] in the _Generic), which isn't very good.
static void _print_printable_bytes(_printable_bytes a, int size){//note that the size parameter will always be sizeof int + sizeof void*, so it's ignored for our purposes here
    for(int i = 0; i < a.size; i++){
        printf("%02X", ((char*)a.data)[i]);
    }
}
static void _print_dont_print(_dont_print dont, int size){} //could also use ... instead of int size if we need to throw out a variable number of arguments in the future
//static void _print_custom(custom_type c){putchar(c.nothing);} //works fine

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
  /*doesn't work in my gcc or clang: struct []: _print_pointer, */\
  /*doesn't work in my gcc or clang: struct *: _print_pointer, */\
  unsigned int: _print_uint, \
  unsigned long int: _print_uint, \
  unsigned long long int: _print_uint, \
  _printable_bytes: _print_printable_bytes, \
  _dont_print: _print_dont_print \
  /*custom_type: _print_custom, //you can add your types like this */ \
) (unit, sizeof(unit))

//Now, to make the function variadic.
//"You are without doubt the worst variadicity I've ever implemented." "But you have implemented me."
#define _print_each(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _boundary_sentinel, ...) do{ /*the ol' do-while(0) trick*/ _print_unit(_1); _print_unit(_2); _print_unit(_3); _print_unit(_4); _print_unit(_5); _print_unit(_6); _print_unit(_7); _print_unit(_8); _print_unit(_9); _print_unit(_10); _print_unit(_11); _print_unit(_12); _print_unit(_13); _print_unit(_14); _print_unit(_15); _print_unit(_16); _print_unit(_17); _print_unit(_18); _print_unit(_19); _print_unit(_20); _print_unit(_21); _print_unit(_22); _print_unit(_23); _print_unit(_24); _print_unit(_25); _print_unit(_26); _print_unit(_27); _print_unit(_28); _print_unit(_29); _print_unit(_30); _print_unit(_31); _print_unit(_32); _Static_assert(_Generic((_boundary_sentinel), _dont_print: 1, default: 0 ), "Too many arguments supplied to print. Please do not do that, or simply edit the source code to expand the function."); } while(0)

#define print(...) _print_each(__VA_ARGS__, (_dont_print){1}, (_dont_print){2}, (_dont_print){3}, (_dont_print){4}, (_dont_print){5}, (_dont_print){6}, (_dont_print){7}, (_dont_print){8}, (_dont_print){9}, (_dont_print){10}, (_dont_print){11}, (_dont_print){12}, (_dont_print){13}, (_dont_print){14}, (_dont_print){15}, (_dont_print){16}, (_dont_print){17}, (_dont_print){18}, (_dont_print){19}, (_dont_print){20}, (_dont_print){21}, (_dont_print){22}, (_dont_print){23}, (_dont_print){24}, (_dont_print){25}, (_dont_print){26}, (_dont_print){27}, (_dont_print){28}, (_dont_print){29}, (_dont_print){30}, (_dont_print){31}, (_dont_print){32}, (_dont_print){0}) //the (_dont_print){x}s are arbitrary placeholders that are known by type to be ignored

//print (or don't!) name, separator, value, second separator
//since _print_unit is an expression, albeit void, we can use a comma operator expression list to keep things tidy!
#define _labelled_print_unit(unit) _Generic((unit), \
  _dont_print: _print_unit(unit), /* this passes along the _dont_print to be merely _print_dont_printed */\
  default: ( _print_unit(#unit), _print_unit(": "), _print_unit(unit), _print_unit(" ") ) \
)

//copied and modified from above
#define _labelled_print_each(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _boundary_sentinel, ...) do{ /*the ol' do-while(0) trick*/ _labelled_print_unit(_1); _labelled_print_unit(_2); _labelled_print_unit(_3); _labelled_print_unit(_4); _labelled_print_unit(_5); _labelled_print_unit(_6); _labelled_print_unit(_7); _labelled_print_unit(_8); _labelled_print_unit(_9); _labelled_print_unit(_10); _labelled_print_unit(_11); _labelled_print_unit(_12); _labelled_print_unit(_13); _labelled_print_unit(_14); _labelled_print_unit(_15); _labelled_print_unit(_16); _labelled_print_unit(_17); _labelled_print_unit(_18); _labelled_print_unit(_19); _labelled_print_unit(_20); _labelled_print_unit(_21); _labelled_print_unit(_22); _labelled_print_unit(_23); _labelled_print_unit(_24); _labelled_print_unit(_25); _labelled_print_unit(_26); _labelled_print_unit(_27); _labelled_print_unit(_28); _labelled_print_unit(_29); _labelled_print_unit(_30); _labelled_print_unit(_31); _labelled_print_unit(_32); _Static_assert(_Generic((_boundary_sentinel), _dont_print: 1, default: 0 ), "Too many arguments supplied to print. Please do not do that, or simply edit the source code to expand the function."); } while(0)

#define labelled_print(...) _labelled_print_each(__VA_ARGS__, (_dont_print){1}, (_dont_print){2}, (_dont_print){3}, (_dont_print){4}, (_dont_print){5}, (_dont_print){6}, (_dont_print){7}, (_dont_print){8}, (_dont_print){9}, (_dont_print){10}, (_dont_print){11}, (_dont_print){12}, (_dont_print){13}, (_dont_print){14}, (_dont_print){15}, (_dont_print){16}, (_dont_print){17}, (_dont_print){18}, (_dont_print){19}, (_dont_print){20}, (_dont_print){21}, (_dont_print){22}, (_dont_print){23}, (_dont_print){24}, (_dont_print){25}, (_dont_print){26}, (_dont_print){27}, (_dont_print){28}, (_dont_print){29}, (_dont_print){30}, (_dont_print){31}, (_dont_print){32}, (_dont_print){0})



#endif
