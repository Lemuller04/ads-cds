#ifndef CONTROL_FLOW_HEADER
#define CONTROL_FLOW_HEADER

typedef enum {
  MAIN_MENU,
  VIEW_MENU,
} State;

/*
 * Bootstraps the application and controls its flow
 */
int start(void);

/*
 * Prints the provided string bold and red
 */
void print_error(char msg[]);

/*
 * Repeatedly asks for a int integer entry
 * from the user until a valid one is provided
 */
int get_int(char msg[], char errorMsg[]);

#endif // !CONTROL_FLOW_HEADER
