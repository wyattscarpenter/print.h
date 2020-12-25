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
  //print((custom_type){'c'}); //printing custom types also works, if you modify print.h to include them
  //print(); //produces inscrutible error at compile time from the internals of the macro
  print("\nmaxsize print. unit count: 1, ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 ", "11 ", "12 ", "13 ", "14 ", "15 ", "16 ", "17 ", "18 ", "19 ", "20 ", "21 ", "22 ", "23 ", "24 ", "25 ", "26 ", "27 ", "28 ", "29 ", "30 ", "31 ", "32\n");
  //print("\noversize print. unit count: 1, ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 ", "11 ", "12 ", "13 ", "14 ", "15 ", "16 ", "17 ", "18 ", "19 ", "20 ", "21 ", "22 ", "23 ", "24 ", "25 ", "26 ", "27 ", "28 ", "29 ", "30 ", "31 ", "32 ", "33\n"); //triggers static assert by being oversize.
  int i = 0;
  print("h");
  print("Hello friends. I have not tested thoroughly. I only tested ", 42, " cases.\nI think you will agree this is not enough. ", i++, " ", i, " ", ' ', (char)' ', (void *)2913870987, " ", 0xadae248b, " ", (void *)0, -16, " ", 1234.5, " ", 23948750293485702.0);
}