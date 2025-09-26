#include "control_flow.h"
#include "data.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>

int start(void) {
  // Standard error messages
  char invalid_char_err[] = "Caractere inválido. Use apenas números.";
  char invalid_option_err[] =
      "Opção inválida. Escolha uma das opções disponíveis.";
  /*
   * Fictional neighborhood names
   * If you want to add, remove, or change a neighborhood name,
   * you can do it here, int his array. Just remember to also
   * update the constat NEIGHBORHOODS_TRACKED at include/data.h
   */
  char neighborhood_names[][50] = {"Jardim Bela Vista", "Belford Roxo",
                                   "Leblon"};

  State state = MAIN_MENU;
  Neighborhood neighborhoods[NEIGHBORHOODS_TRACKED];
  bootstrap_data(neighborhoods, neighborhood_names);

  print_welcome();

  while (1) {
    // --- Render current menu ---
    switch (state) {
    case MAIN_MENU:
      print_main_menu();
      break;
    case VIEW_MENU:
      print_view_menu();
      break;
    }

    int option = get_int("\nDigite a opção desejada: ", invalid_char_err);

    // --- Process option ---
    switch (option) {
    case 0:
      switch (state) {
      case MAIN_MENU:
        return 0;
      case VIEW_MENU:
        state = MAIN_MENU;
      }
      break;
    case 1:
      switch (state) {
      case MAIN_MENU:
        state = VIEW_MENU;
        print_annual_graph(neighborhoods);
        break;
      case VIEW_MENU:
        print_monthly_graph(neighborhoods);
        state = MAIN_MENU;
        break;
      }
      break;
    default:
      print_error(invalid_option_err);
    }
  }
}

void print_error(char msg[]) { printf("\n\033[1;31m%s\033[0m\n", msg); }

int get_int(char msg[], char errorMsg[]) {
  char buffer[100];

  while (1) {
    printf("%s", msg);

    // Gets input from the user
    fgets(buffer, sizeof(buffer), stdin);

    // Tries to convert the input to a int
    char *endptr;
    int n = (int)strtol(buffer, &endptr, 10);

    // Checks if the conversion was sucessfull
    if (endptr == buffer || *endptr != '\n') {
      print_error(errorMsg);
      continue;
    }

    return n;
  }
}
