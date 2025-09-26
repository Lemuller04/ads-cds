#include "data.h"
#include <stdlib.h>
#include <string.h>

void bootstrap_data(Neighborhood n[], char names[][50]) {
  for (int i = 0; i < NEIGHBORHOODS_TRACKED; i++) {

    // Sets neighborhood ID
    n[i].id = i;

    // Sets neighborhood name, based on the names array
    strncpy(n[i].name, names[i], sizeof(n[i].name) - 1);
    n[i].name[sizeof(n[i].name) - 1] = '\0';

    // Iterates through every month, then every day, and sets a random rainfall
    // data
    for (int j = 0; j < MONTHS_TRACKED; j++) {
      for (int k = 0; k < DAYS_TRACKED; k++) {
        n[i].dailyRain[j][k] = rand() % 101;
      }
    }
  }
}

float average_monthly_rain(int data[]) {
  float sum = 0;

  for (int i = 0; i < DAYS_TRACKED; i++) {
    sum += data[i];
  }

  return sum / DAYS_TRACKED;
}

float average_annual_rain(Neighborhood *n) {
  int total_days = DAYS_TRACKED * MONTHS_TRACKED;
  int sum = 0;

  for (int i = 0; i < MONTHS_TRACKED; i++) {
    for (int j = 0; j < DAYS_TRACKED; j++) {
      sum += n->dailyRain[i][j];
    }
  }

  return 1.0 * sum / total_days;
}
