#ifndef DATA_HEADER
#define DATA_HEADER

#define NEIGHBORHOODS_TRACKED 3
#define DAYS_TRACKED 30
#define MONTHS_TRACKED 12

typedef struct {
  char name[50];
  int dailyRain[MONTHS_TRACKED][DAYS_TRACKED];
  int id;
} Neighborhood;

/*
 * Sets up the random data for demonstration of the application
 */
void bootstrap_data(Neighborhood n[], char names[][50]);

/*
 * Calculates the average annual rain of each neighborhood
 */
float average_annual_rain(Neighborhood *n);

/*
 * Calculates the average monthly rain for a specific neighborhood
 */
float average_monthly_rain(int data[]);

#endif // !DATA_HEADER
