#include "print.h"

int main(void) {
  char a = 'a';
  int anint = 43;
  int ints[] = {123, 456, 789};
  char nl = '\n';
  int * pointer_to_ints = ints;
  print((void *)ints, "\n");
  //external_function();
  print("ints: ", ints, " address of ints: ", &ints, " pointer_to_ints: ", pointer_to_ints, " address of pointer_to_ints: ", &pointer_to_ints, " are they equal? ", (void *)ints == (void *)&ints, " ", (void *)pointer_to_ints==(void *)&pointer_to_ints, "\n");
  //print(); //this is not allowed, and the error message is currently mysterious
  print(""); //this is fine though
  //print("hello") //this (missing semicolon) is not allowed. Were you raised in a barn? The error you get is slightly mysterious though, sorry.
  labelled_print(ints, pointer_to_ints, "\n");
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
  _print_unit(12930920);
  _print_unit("\n");
  _print_unit(-1293092034523452345);
  _print_unit("\n");
  _print_unit( ((int[]){2913870987, 3, 7}) ); //prints compound expression (in-line array literal) fine, though you have to parenthesize it (due to how function macro arguments are parsed, I think) and my GCC will no longer warn you that the first thing here is too big and will overflow
  _print_unit( (void *) ((int[]){2913870987, 3, 7}) ); //casting to void * prints as pointer
  _print_unit("\n");
  _print_unit(-1);
  _print_unit("\n");
  print( ( (_printable_bytes){3, &(char[]){1,2,3}} ), "(should be 010203) Don't ever manually construct _printable_byte structs, by the way. This is just for testing some internals.\n" );
  print(printable_bytes("example")," should be 6578616D706C6500\n");
  struct unknown_structure {int a; int b; int c;};
  struct unknown_structure us = {};
  struct unknown_structure uss = {1, 2, 3};
  print("Let's print a struct pointer ", (void*)&us, " and now a struct (empty): ", printable_struct(us), " and now a nonempty struct: ", printable_struct(uss), ". These results will vary based on whether your compiler implements __builtin_dump_struct\n");
  //_print_unit( us )  //errors
  _print_unit(&anint); //taking the address will print a pointer, naturally.
  print("\nLet's print some arrays! ", ((int[]){}), ((int[]){1}), ((int[]){1, 2}), ((int[]){1, 2, 3}), ((int[]){1, 2, 3, 4})); //as you can see, if sizeof the array = sizeof pointer, we must print a pointer.
  int twod[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  print("\nLet's print a 2D array! ", twod); //This matches to int*[] in the _Generic expression
  int (*twodp)[3] = twod;
  print("\nLet's print a 2D array pointer! ", twodp); //This also matches to int*[] in the _Generic expression
  int *ip = ints;
  print("\n", ip, " ", *ip, " ", &ip, "\n");
  //print((custom_type){'c'}); //printing custom types also works, if you modify print.h to include them
  //print(); //produces inscrutible error at compile time from the internals of the macro
  print("\nmaxsize print. unit count: 1, ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 ", "11 ", "12 ", "13 ", "14 ", "15 ", "16 ", "17 ", "18 ", "19 ", "20 ", "21 ", "22 ", "23 ", "24 ", "25 ", "26 ", "27 ", "28 ", "29 ", "30 ", "31 ", "32\n");
  //print("\noversize print. unit count: 1, ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 ", "11 ", "12 ", "13 ", "14 ", "15 ", "16 ", "17 ", "18 ", "19 ", "20 ", "21 ", "22 ", "23 ", "24 ", "25 ", "26 ", "27 ", "28 ", "29 ", "30 ", "31 ", "32 ", "33\n"); //triggers static assert by being oversize.
  int i = 0;
  print("h");
  print("Hello friends. I have not tested thoroughly. I only tested ", 42, " cases.\nI think you will agree this is not enough. ", i++, " ", i, " ", ' ', (char)' ', (void *)2913870987, " ", 0xadae248b, " ", (void *)0, -16, " ", 1234.5, " ", 23948750293485702.0, "\n");
  //return print("bye"); //this is not allowed, print gives no return value, and the error message is currently mysterious
}
