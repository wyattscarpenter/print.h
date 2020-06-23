#include "print.h"

int main(void) {
  char a = 'a';
  char nl = '\n';
  _print_unit(a);
  _print_unit(nl);
  _print_unit('\n');
  _print_unit(nl);
  _print_unit('a');
  _print_unit(nl);
  _print_unit(27);
  return 0;
}