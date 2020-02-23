#include "lts.h"

// This function divide one sequence into two subsequences
void divide_for_T(char *A, char *A1, char *A2, int a1, int a2) {
    for (int i = 0; i < a1; i++)
    {
        A1[i] = A[i];
    }
    for (int i = a1; i < a1 + a2; i++)
    {
        A2[i - a1] = A[i];
    }
}

// Compute LCS for each division(divide S1 into two squence), compare and select the longest one
int LTS(int len1, char *S1, char *T) {
    char *A1 = NULL;
    char *A2 = NULL;
    A1 = (char*)malloc (len1 * sizeof(char) + 1);
    A2 = (char*)malloc (len1 * sizeof(char) + 1);
    if(A1 == NULL || A2 == NULL) {
        printf("Allocation error\n");
        exit(0);
    }

    int max_len = 0;
    int lcs_len = 0;
    int divide_i = 0;// record the separation point

    for (int i = 0; i < len1 - 1; i++)
    {
        clear(A1, i+1);
        clear(A2, len1 - i -1);
        divide_for_T(S1, A1, A2, i+1, len1 - i- 1);
        lcs_len = LCS_len (i+1, len1 - i- 1, A1, A2);
        if (lcs_len > max_len) {
            max_len = lcs_len;
            divide_i = i;
        }
    }
    clear(A1, divide_i+1);
    clear(A2, len1 - divide_i -1);
    divide_for_T(S1, A1, A2, divide_i+1, len1 - divide_i- 1);

    LCS (divide_i+1, len1 - divide_i -1, A1, A2, T);
    for(int i = 0; i < max_len; i++) {// Double the sequence such that 123 will become 123123
        T[max_len + i] = T[i];
    }

    free(A1);
    free(A2);
    A1 = NULL;
    A2 = NULL;

    return max_len*2;
}

int LCTS(int len1, int len2, char *S1, char *S2, char *CT) {
    //S1p1 and S1p2 are two subsequence of first sequebce
    // S2p1 and S2p2 are sub... of second
    char *S1p1 = NULL;
    char *S1p2 = NULL;
    char *S2p1 = NULL;
    char *S2p2 = NULL;
    S1p1 = (char*)malloc (len1 * sizeof(char) + 1);
    S1p2 = (char*)malloc (len1 * sizeof(char) + 1);
    S2p1 = (char*)malloc (len2 * sizeof(char) + 1);
    S2p2 = (char*)malloc (len2 * sizeof(char) + 1);
    if(S1p1 == NULL || S1p2 == NULL || S2p1 == NULL || S2p2 == NULL) {
        printf("Allocation error\n");
        exit(0);
    }

    int max_len = 0;
    int lcs_len = 0;
    int divide_i = 0;// stores the separation point for the first sequence
    int divide_j = 0;// store the sepqrqtion point for the second sequence

    for (int i = 0; i < len1 - 1; i++){
        clear(S1p1, i+1);
        clear(S1p2, len1 - i -1);
        divide_for_T(S1, S1p1, S1p2, i+1, len1 - i- 1);
        for (int j = 0; j < len2 - 1; j++){
            clear(S2p1, j+1);
            clear(S2p2, len2 - j -1);
            divide_for_T(S2, S2p1, S2p2, j+1, len2 - j- 1);
            lcs_len = LCS4_len (i+1, len1 - i- 1, j+1, len2 -j-1, S1p1, S1p2, S2p1, S2p2);
            if (lcs_len > max_len) {
                max_len = lcs_len;
                divide_i = i;
                divide_j = j;
            }
        }
    }
    clear(S1p1, divide_i+1);
    clear(S1p2, len1 - divide_i -1);
    divide_for_T(S1, S1p1, S1p2, divide_i+1, len1 - divide_i- 1);
    clear(S2p1, divide_j+1);
    clear(S2p2, len2 - divide_j -1);
    divide_for_T(S2, S2p1, S2p2, divide_j+1, len2 - divide_j- 1);

    LCS4 (divide_i+1, len1 - divide_i -1, divide_j+1, len2 - divide_j -1, S1p1, S1p2, S2p1, S2p2, CT);
    for(int i = 0; i < max_len; i++) {// Double the sequence from 123 to 123123
        CT[max_len + i] = CT[i];
    }

    free(S1p1);
    free(S1p2);
    free(S2p1);
    free(S2p2);
    S1p1 = NULL;
    S1p2 = NULL;
    S2p1 = NULL;
    S2p2 = NULL;

    return max_len*2;
}