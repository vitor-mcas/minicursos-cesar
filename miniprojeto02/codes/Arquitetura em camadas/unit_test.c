#include <assert.h>
#include "ui.h"

// In my_sum.c exemple
int my_sum(int a, int b) {
  return a + b;
}

int main(int argc, char *argv[]) {
  assert(1 == updateMenu(MENU1));
  assert(12 == updateMenu(MENU2));
  assert(13 == updateMenu(MENU3));

  /* Test my_sum */
  assert(2 == my_sum(1, 1));
  assert(-2 == my_sum(-1, -1));
  assert(0 == my_sum(0, 0));
  // ...
  return(0);
}

