#include "lps.h"

// get the reverse sequence of given squence, this is used for compute LPS
void reverse (char *A, char *A1, int len) {
    for (int i = 0; i < len; i++)
    {
        A1[i] = A[len - 1 - i];
    }
}

// Compute LCS between the original sequence and the reverse of original sequence
int LPS(int len2, char *S2, char *P) {
    int max_len = 0;
    char *R = NULL;
    R = (char*)malloc (len2 * sizeof(char) + 1);
    if(R == NULL){
        printf("LPS Allocation Error!");
        exit(0);
    }
    reverse(S2, R, len2);
    max_len = LCS(len2, len2, S2, R, P);

    free(R);
    R = NULL;

    return max_len;
}

// compute the lcps for the two sequences
int LCPS(int len1, int len2,  char *S1, char *S2, char *CP) {
    int max_len = 0;
    char *R1 = NULL;// store the reverse of the first sequence
    char *R2 = NULL;// store the reverse of the second sequence
    R1 = (char*)malloc (len1 * sizeof(char) + 1);
    R2 = (char*)malloc (len2 * sizeof(char) + 1);
    if(R1 == NULL || R2 == NULL){
        printf("LPS Allocation Error!");
        exit(0);
    }
    reverse(S1, R1, len1);
    reverse(S2, R2, len2);
    max_len = LCS4(len1, len1, len2, len2, S1, R1, S2, R2, CP);
    if (max_len % 2 == 0 && CP[(max_len-1)/2] != CP[(max_len-1)/2 + 1]) {// avoid some violation
        for(int i = (max_len-1)/2; i < max_len-1; i++){
            CP[i] = CP[i+1];
        }
        max_len -= 1;
    }

    free(R1);
    R1 = NULL;
    free(R2);
    R2 = NULL;

    return max_len;
}