#include <assert.h>
#include "ui.h"

// In my_sum.c
int my_sum(int a, int b) {
  return a + b;
}

// In test_my_sum.c
int main(int argc, char *argv[]) {
  assert(1 == updateMenu(MENU1));
  assert(12 == updateMenu(MENU2));
  assert(13 == updateMenu(MENU3));
  // ...
  return(0);
}

