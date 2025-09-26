#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_NEIGHBORHOODS 7
#define TOTAL_DAYS_TRACKED 30

typedef struct {
  int id;
  char name[24];
  int rainData[TOTAL_DAYS_TRACKED];
} Neighborhood;

typedef struct {
  int totalDays;
  bool descending;
  int neighborhoods[TOTAL_NEIGHBORHOODS];
  int filteredNeighborhoods;
} Filter;

// Function declarations
void printWelcome();
void printMainMenu();
void printViewingMenu();
bool printFilterSetup(Filter *filter, Neighborhood n[]);
bool processFilterNeighborhood(Filter *filter, Neighborhood n[], int option);
void fillNeighborhoodsData(Neighborhood n[], char *names[]);
void fillRainData(Neighborhood n[]);
void printData(Neighborhood n[], Filter filter);
void fillFilterData(Neighborhood n[], Filter *f, int days, bool desc,
                    bool temp);

int main(void) {
  // Setting up variables for the program
  srand(time(NULL));

  // If you want do edit the name of a neighborhood, you can do it here in this
  // array If you want to add or remove a neighborhood, also edit the constant
  // value tha tracks its length
  char *neighborhoodNames[TOTAL_NEIGHBORHOODS] = {
      "Bela Vista",  "Campão",     "Balsa Velha", "Centro",
      "Monte Verde", "Costa Azul", "Vila Mariana"};
  Neighborhood neighborhoods[TOTAL_NEIGHBORHOODS];
  // Filter filter = {.totalDays = 7, .descending = true, .neighborhoods = {0}};
  Filter filter = {.filteredNeighborhoods = 0};
  fillNeighborhoodsData(neighborhoods, neighborhoodNames);
  fillFilterData(neighborhoods, &filter, 7, true, false);

  printWelcome();

  char buffer[100];
  while (true) {
    printMainMenu();

    printf("\nSelecione uma opção: ");

    // Gets input from the user
    fgets(buffer, sizeof(buffer), stdin);

    // Tries to convert the input to a short
    char *endptr;
    short option = (short)strtol(buffer, &endptr, 10);

    // Checks if the conversion was sucessfull
    if (endptr == buffer || *endptr != '\n') {
      printf("\n\033[1;31mOpção inválida! Digite apenas números.\033[0m\n");
      continue;
    }

    switch (option) {
    case 0:
      printf("Encerrando programa...\n");
      return 0;
    case 1:
      fillFilterData(neighborhoods, &filter, 30, false, false);
      printData(neighborhoods, filter);
      printViewingMenu();
      break;
    case 2:
      if (printFilterSetup(&filter, neighborhoods)) {
        printData(neighborhoods, filter);
        printViewingMenu();
      }
      break;
    default:
      printf("\n\033[1;31mOpção inválida\033[0m\n");
    }
  }
}

bool printFilterSetup(Filter *filter, Neighborhood n[]) {
  Filter tempFilter = {.descending = filter->descending,
                       .totalDays = filter->totalDays,
                       .filteredNeighborhoods = 0};
  memcpy(tempFilter.neighborhoods, filter->neighborhoods,
         sizeof(filter->neighborhoods));
  fillFilterData(n, &tempFilter, 30, false, true);

  char buffer[100];
  bool looping = true;

  printf("\nIniciando filtro...\n");
  printf("Carregando lista de bairros...\n\n");

  // Loop para filtrar os bairros
  while (looping) {
    for (int i = 0; i < TOTAL_NEIGHBORHOODS; i++) {
      bool added = false;

      for (int j = 0; j < tempFilter.filteredNeighborhoods; j++) {
        if (n[i].id == tempFilter.neighborhoods[j])
          added = true;
      }
      if (added)
        printf("(adicionado) ");
      printf("%d - %s\n", i + 1, n[i].name);
    }

    printf(
        "\nInsira o número do bairro que você de seja adicionar ao filtro;\n");
    printf("Insira '0' para cancelar e voltar;\n");
    printf("Insira '-1' para adicionar todos os bairros;\n");
    printf("Insira '-2' se você já terminou de filtrar os bairros e deseja "
           "prosseguir.\n");
    printf("Opção: ");

    fgets(buffer, sizeof(buffer), stdin);
    char *endptr;
    short option = (short)strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\n') {
      printf("\n\033[1;31mOpção inválida. Digite apenas números.\033[0m\n\n");
      continue;
    }

    switch (option) {
    case 0:
      printf("\nVoltando ao menu principal...\n");
      return false;
    case -1:
      fillFilterData(n, &tempFilter, filter->totalDays, filter->descending,
                     false);
      break;
    case -2:
      if (tempFilter.filteredNeighborhoods < 1) {
        printf("\nAo menos um bairro deve ser inserido para prosseguir.\n");
        break;
      }
      printf("\nBairros adicionados. Prosseguindo...\n");
      looping = false;
      break;
    default:
      if (option > 0 && option <= TOTAL_NEIGHBORHOODS)
        if (processFilterNeighborhood(&tempFilter, n, option)) {
          printf("\nBairro %s adicionado ao filtro.\n\n", n[option - 1].name);
          break;
        }
      printf("\n\033[1;31mOpção inválida.\033[0m\n\n");
    }

    if (tempFilter.filteredNeighborhoods == TOTAL_NEIGHBORHOODS) {
      printf("\nTodos os bairros foram adicionados.\n\n");
      looping = false;
    }
  }

  looping = true;

  while (looping) {
    printf("Selecione o período que deseja visualizar\n");
    printf("1 - 30 dias\n");
    printf("2 - 15 dias\n");
    printf("3 - 7 dias\n");
    printf("0 - Voltar\n");
    printf("Opção: ");

    fgets(buffer, sizeof(buffer), stdin);
    char *endptr;
    short option = (short)strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\n') {
      printf("\n\033[1;31mOpção inválida. Digite apenas números.\033[0m\n\n");
      continue;
    }

    switch (option) {
    case 0:
      printf("\nVoltando ao menu principal...\n");
      return false;
    case 1:
      tempFilter.totalDays = 30;
      looping = false;
      break;
    case 2:
      tempFilter.totalDays = 15;
      looping = false;
      break;
    case 3:
      tempFilter.totalDays = 7;
      looping = false;
      break;
    default:
      printf("\n\033[1;31mOpção inválida.\033[0m\n\n");
      break;
    }

    if (!looping)
      printf("\nPeríodo definido.\n");
  }

  looping = true;

  while (looping) {
    printf("\nSelecione a ordem em que deseja ver os dados:\n1 - Descrescente "
           "(últimos x "
           "dias)\n2 - Crescente (primeiros x dias)\n0 - Voltar\n");

    printf("Opção: ");
    fgets(buffer, sizeof(buffer), stdin);
    char *endptr;
    short option = (short)strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\n') {
      printf("\n\033[1;31mOpção inválida. Digite apenas números.\033[0m\n\n");
      continue;
    }

    switch (option) {
    case 0:
      printf("\nVoltando ao menu principal...\n");
      return false;
    case 1:
      tempFilter.descending = true;
      looping = false;
      break;
    case 2:
      tempFilter.descending = false;
      looping = false;
      break;
    default:
      printf("\n\033[1;31mOpção inválida.\033[0m\n\n");
      break;
    }

    if (!looping)
      printf("\nOrdem definida.\n");
  }

  fillFilterData(n, filter, tempFilter.totalDays, tempFilter.descending, false);
  for (int i = 0; i < TOTAL_NEIGHBORHOODS; i++)
    filter->neighborhoods[i] = tempFilter.neighborhoods[i];
  return true;
}

bool processFilterNeighborhood(Filter *filter, Neighborhood n[], int option) {
  // Iterates through every neoghborhood
  for (int i = 0; i < TOTAL_NEIGHBORHOODS; i++) {

    // Iterates through all neighborhoods already added to the filter
    for (int j = 0; j < filter->filteredNeighborhoods; j++) {
      if (filter->neighborhoods[j] == option - 1) {
        printf("\n\033[1;31mEste bairro já foi adicionado.\033[0m\n");
        return false;
      }
    }

    // Checks if its a valid neighborhoods
    if (n[i].id == option - 1) {
      filter->neighborhoods[filter->filteredNeighborhoods] = option - 1;
      filter->filteredNeighborhoods++;
      return true;
    }
  }
  return false;
}

void printViewingMenu() {
  char buffer[100];

  while (true) {
    printf("\n1 - Alterar visualização\n2 - Filtrar dados\n0 - voltar\n");
    printf("\nSelecione uma opção: ");

    fgets(buffer, sizeof(buffer), stdin);
    char *endptr;
    short option = (short)strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\n') {
      printf("\n\033[1;31mOpção inválida! Digite apenas números.\033[0m\n");
      continue;
    }

    switch (option) {
    case 0:
      printf("Voltando para o menu...\n");
      return;
    case 1:
      printf("wip\n");
      break;
    case 2:
      printf("wip\n");
      break;
    default:
      printf("\n\033[1;31mOpção inválida\033[0m\n");
    }
  }
}

void printWelcome() {
  printf("\nBem vindo ao RainTracker3000 - Um programa para analisar dados "
         "meteorológicos.\n");
  printf(
      "Esse programa foi feito por Leonardo Müller de Lima, para um trabalho "
      "da matéria de Algorítimo e Pensamento Computacional do curso de Análise "
      "e Desenvolvimento de Sistemas da Universidade Cruzeiro do Sul.\n");
  printf(
      "O programa utiliza dados fictícios para gerar gráficos para análise.\n");
}

void printMainMenu() {
  printf("\n************************\n");
  printf("     MENU PRINCIPAL     \n");
  printf("************************\n");
  printf("\n1 - Visualizar todos os dados\n");
  printf("2 - Visualizar dados filtrados\n");
  printf("0 - Sair\n");
}

void fillNeighborhoodsData(Neighborhood n[], char *names[]) {
  for (int i = 0; i < TOTAL_NEIGHBORHOODS; i++) {
    n[i].id = i;
    strncpy(n[i].name, names[i], sizeof(n[i].name));
    n[i].name[sizeof(n[i].name) - 1] = '\0';
  }

  fillRainData(n);
}

void fillRainData(Neighborhood n[]) {
  for (int i = 0; i < TOTAL_NEIGHBORHOODS; i++)
    for (int j = 0; j < TOTAL_DAYS_TRACKED; j++)
      n[i].rainData[j] = rand() % 101;
}

void printData(Neighborhood n[], Filter filter) {
  int startDay = filter.descending ? TOTAL_DAYS_TRACKED - 1 : 0;
  int factor = filter.descending ? -1 : 1;

  // Iterates through every filtered neighborhood
  for (int i = 0; i < filter.filteredNeighborhoods; i++) {
    int nIndex = filter.neighborhoods[i];
    printf("\nDados do bairro %s\n", n[nIndex].name);

    for (int j = startDay, limit = 0; limit < filter.totalDays;
         j += factor, limit++) {
      printf("%d | %d/01/2077 - %d milímetros\n", limit + 1, j + 1,
             n[nIndex].rainData[j]);
    }
  }
}

void fillFilterData(Neighborhood n[], Filter *f, int days, bool desc,
                    bool temp) {
  f->totalDays = days;
  f->descending = desc;
  f->filteredNeighborhoods = 0;

  for (int i = 0; i < TOTAL_NEIGHBORHOODS; i++) {
    if (!temp) {
      f->neighborhoods[i] = n[i].id;
      f->filteredNeighborhoods++;
    } else
      f->neighborhoods[i] = -1;
  }
}
