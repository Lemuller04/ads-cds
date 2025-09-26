#include "display.h"
#include "data.h"
#include <stdio.h>

void print_welcome() {
  printf("\n*****************************\n");
  printf("       RainTracker3000       \n");
  printf("*****************************\n");
  printf("Bem vindo ao RainTracker3000! Este é um programa que gera "
         "aleatoriamente dados "
         "fictícios para exibi-los de maneira ordenada e "
         "filtrada.\n");
  printf("Feito por Leonardo Müller de Lima, 2025.\n");
}

void print_main_menu() {
  printf("\n****************************\n");
  printf("       Menu Principal       \n");
  printf("****************************\n");
  printf("1 - Visualizar dados anuais\n");
  printf("0 - Sair\n");
}

void print_view_menu() {
  printf("1 - Visualizar dados mensais\n");
  printf("0 - Voltar\n");
}

void print_annual_graph(Neighborhood n[]) {
  int max_width = 50;

  printf("\nChuva média anual: \n");
  printf("--------------------+");
  printf("-------------------------------------------------\n");
  for (int i = 0; i < NEIGHBORHOODS_TRACKED; i++) {
    float average_rain = average_annual_rain(&n[i]);

    printf("%-20s|", n[i].name);

    float scale = average_rain / 100.0f * max_width;
    for (int j = 0; j < (int)scale; j++) {
      if (average_rain <= 25)
        printf("\033[1;32m#\033[0m"); // green (low rain)
      else if (average_rain <= 50)
        printf("\033[1;33m#\033[0m"); // yellow (medium rain)
      else if (average_rain <= 75)
        printf("\033[1;36m#\033[0m"); // cyan (high rain)
      else
        printf("\033[1;31m#\033[0m"); // red (extreme rain)
    }

    printf(" %.2fmm\n", average_rain);
  }
  printf("--------------------+");
  printf("-------------------------------------------------\n");
  printf("%-20s0mm------------------------------------------100mm\n", " ");
}

void print_monthly_graph(Neighborhood n[]) {
  int max_width = 50;
  char months[][20] = {"Janeiro",  "Fevereiro", "Marco",    "Abril",
                       "Maio",     "Junho",     "Julho",    "Agosto",
                       "Setembro", "Outubro",   "Novembro", "Dezembro"};

  for (int i = 0; i < NEIGHBORHOODS_TRACKED; i++) {
    printf("\nChuva média mensal do bairro %s:\n", n[i].name);
    printf("--------------------+");
    printf("-------------------------------------------------\n");

    for (int j = 0; j < MONTHS_TRACKED; j++) {
      float average_rain = average_monthly_rain(n[i].dailyRain[j]);

      printf("%-20s|", months[j]);

      float scale = average_rain / 100.0f * max_width;
      for (int k = 0; k < (int)scale; k++) {
        if (average_rain <= 25)
          printf("\033[1;32m#\033[0m"); // green
        else if (average_rain <= 50)
          printf("\033[1;33m#\033[0m"); // yellow
        else if (average_rain <= 75)
          printf("\033[1;36m#\033[0m"); // cyan
        else
          printf("\033[1;31m#\033[0m"); // red
      }

      printf(" %.2fmm\n", average_rain);
    }

    printf("--------------------+");
    printf("-------------------------------------------------\n");
    printf("%-20s0mm------------------------------------------100mm\n", " ");
  }
}
