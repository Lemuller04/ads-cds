#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include "data.h"

/*
 * Prints the welcome message
 */
void print_welcome();

/*
 * Prints respective menus
 */
void print_main_menu();
void print_view_menu();

/*
 * Prints the data in a graph format
 */
void print_annual_graph(Neighborhood n[]);
void print_monthly_graph(Neighborhood n[]);

#endif // !DISPLAY_HEADER
