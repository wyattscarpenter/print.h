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
  _print_unit(nl);
  _print_unit("Hello world.\n");
  _print_unit(12930920L);
  _print_unit("\n");
  _print_unit(1293092034523452345);
  _print_unit("\n");
  _print_unit(1293092034523452345L);
  _print_unit("\n");
  _print_unit(12930920345234523452);
  _print_unit("\n");
  _print_unit(12930920);
  _print_unit("\n");
  _print_unit(-1293092034523452345);
  _print_unit("\n");
  _print_unit(-1);
  _print_unit("\n");
  return 0;
}