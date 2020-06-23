/* print.h
Finally, a print function!
Simply #include "print.h" and call print on whatever you want, up to 16 arguments.
Can print the same types of data as printf.
(except in-line character literals, because those are by standard promoted to ints on creation. Sorry, I don't make the rules.)
*/

#include <stdio.h>

//TODO: since this currently uses printf, I think the compiler does the replacement with generic in first, then warns about formatting (ie "warning: format specifies type 'long long' but the argument has type 'char' [-Wformat]"), then choses the right option. Very odd. Happens in both gcc and clang. Well, better stop using printf eventually.
#define _print_unit(unit) _Generic( (unit), \
  char: printf("%c", unit), \
  int: printf("%d", unit), \
  long int: printf("%ld", unit), \
  long long int: printf("%lld", unit), \
  float: printf("%f", unit), \
  double: printf("%f", unit), \
  char *: printf("%s", unit), \
  void *: ("%p", unit), \
  unsigned int: printf("%ud", unit), \
  unsigned long int: printf("%uld", unit), \
  unsigned long long int: printf("%ulld", unit), \
  default: printf("%x", unit) \
)