#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void clear(char *A, int len);

int getlen(char *S);

int check(char *S);

void userInput(char *S1, char *S2);

void userInputOne(char *S1);

void print_seq(int len, char *S);

void generate_seq(char *S1, char *S2);

void readone_from(const char * restrict filename, char *S);

void readtwo_from(const char * restrict filename, char *S1, char *S2);

void write_to(const char * restrict filename, char *S, int len);

void getCommand(int argc, char *argv[], int cmd[10]);

void report_error(void);

