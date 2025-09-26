#include "control_flow.h"
#include "data.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));
  int res = start();

  // If all goes well, the return will be zero
  switch (res) {
  case 0:
    printf("Encerrando aplicação...\n");
    return res;
  default:
    printf("Um erro inesperado aconteceu.\nEncerrando programa...\n");
    return res;
  }
}
