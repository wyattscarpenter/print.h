/* print.h
Finally, a print function!
Simply #include "print.h" and call print on whatever you want, up to 16 arguments.
Can print the same types of data as printf.
(except in-line character literals, because those are by standard promoted to ints on creation. Sorry, I don't make the rules.)
*/

#include <stdio.h>

#define _print_unit(unit) _Generic( (unit), \
  char: printf("%c", unit), \
  int: printf("%d", unit), \
  long int: printf("%ld", unit), \
  long long int: printf("%ld", unit), \
  default: printf("%x", unit) \
)