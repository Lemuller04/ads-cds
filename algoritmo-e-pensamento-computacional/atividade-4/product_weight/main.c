#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_weights(float arr[], char mas[]);
void bubble_sort(float arr[], int n, bool ascending);
void print_error(char msg[]);
float get_float(char msg[], char errorMsg[]);

#define MAX_WEIGHTS 10

int main(void) {
  float weights[MAX_WEIGHTS];

  // Read 10 items from the user
  printf("Insira o peso de 10 items em KGs\n");
  for (int i = 0; i < MAX_WEIGHTS; i++) {
    printf("%dº", i + 1);
    weights[i] = get_float(" item: ", "Insira um número válido");
  }

  print_weights(weights, "\nItems na ordem que foram inseridos: \n");
  bubble_sort(weights, MAX_WEIGHTS, true);
  print_weights(weights, "\nItems em ordem crescente: \n");
  bubble_sort(weights, MAX_WEIGHTS, false);
  print_weights(weights, "\nItems em ordem decrescente: \n");
}

// Prints the array in a standardized way
void print_weights(float arr[], char msg[]) {
  printf("%s", msg);
  for (int i = 0; i < MAX_WEIGHTS; i++) {
    printf("%.2fkg", arr[i]);
    if (i != MAX_WEIGHTS - 1)
      printf(", ");
  }
  printf("\n");
}

void bubble_sort(float arr[], int n, bool ascending) {
  float temp;
  int i, j;
  bool reordered;

  // Iterates over the array
  for (i = 0; i < n - 1; i++) {
    reordered = false; // reset each pass

    for (j = 0; j < n - i - 1; j++) {

      // Compares according to the ascnding option
      if ((ascending && arr[j] > arr[j + 1]) ||
          (!ascending && arr[j] < arr[j + 1])) {
        reordered = true;

        // Swaps using the temp variable
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
    if (!reordered)
      return; // already sorted
  }
}

// Prints a provided string in red
void print_error(char msg[]) { printf("\n\033[1;31m%s\033[0m\n", msg); }

float get_float(char msg[], char errorMsg[]) {
  char buffer[100];

  while (1) {
    printf("%s", msg);

    // Gets input from the user
    fgets(buffer, sizeof(buffer), stdin);

    // Tries to convert the input to a float
    char *endptr;
    float n = (float)strtof(buffer, &endptr);

    // Checks if the conversion was sucessfull
    if (endptr == buffer || *endptr != '\n') {
      print_error(errorMsg);
      continue;
    }

    return n;
  }
}
