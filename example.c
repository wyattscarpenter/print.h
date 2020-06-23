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
  _print_unit(ints); //just a pointer... can't razzmatazz the compiler into convincing itself it knows the size. or can I? TODO
  int *ip = ints;
  print("\n", ip, " ", *ip, " ", &ip, "\n");
  //print("\n", 1, " ",  2, " ",  3, " ",  4, " ",  5, " ",  6, " ",  7, " ",  8, " ",  9, " ",  10, " ",  11, " ",  12, "\n"); //triggers static assert by being oversize.
  int i = 0;
  print("h");
  print("Hello friends. I have not tested thoroughly. I only tested ", 42, " cases.\nI think you will agree this is not enough. ", i++, " ", i, " ", ' ', (char)' ', (void *)2913870987, " ", 0xadae248b, " ", (void *)0, -16);
}