#include "print.h"

int main(void) {
  char a = 'a';
  int ints[] = {123, 456, 789};
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
  _print_unit(12930920345234523452); //warns for unsignedness
  _print_unit("\n");
  _print_unit(12930920);
  _print_unit("\n");
  _print_unit(-1293092034523452345);
  _print_unit("\n");
  _print_unit(-1);
  _print_unit("\n");
  _print_unit(ints); //warns for unsupported type
  _print_unit("\n");
  int i = 0;
  print("Hello friends. ", "I have not tested throughly, ", "I only tested ", 42, " cases.\n", "I think you will agree this is not enough. ", i++, " ", i, " ", ' ', (char)' ', 2913870987, " ", (void *)0, -8);
  return 0;
}