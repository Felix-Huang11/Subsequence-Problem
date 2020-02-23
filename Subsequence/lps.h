#include <stdlib.h>
#include "utility.h"
#include "lcs.h"

void reverse (char *A, char *A1, int len);

int LPS(int len2, char *S2, char *P);

int LCPS(int len1, int len2,  char *S1, char *S2, char *CP);
