#include "lcs.h"

// Given 4 char type digits, return the maximum one
char max(char a, char b, char c, char d){
    char m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    if (d > m) m = d;

    return m;
}

// input two sequences S1, S2, compute LCS and stored in S
int LCS (int len1, int len2, char *S1, char *S2, char *S) {
    int commonlen;
    int *table[len1 + 1];
    for (int i = 0; i < len1 + 1; i++)
    {
        table[i] = NULL;
        table[i] = (int*) malloc ((len2 + 1) * sizeof(int));

        if (table[i] == NULL) {
            printf("LCS Allocation Error!");
            exit(0);
        }
    }
    // int table[len1+1][len2+1];//the row represent the first row-th elements of S1, the colomn represents the first colomn-th elements of S2
    for (int p = 0; p <= len1; p++)
    {
        for (int q = 0; q <= len2; q++)
        {
            if (p == 0 || q == 0) table[p][q] = 0;// set the 0-th row and 0-th colomn be 0
            else if (S1[p-1] == S2[q -1]) {
                table[p][q] = table[p-1][q-1] + 1;// if p-th value in S1 equal to q-th value in S2, current common length increased by 1
            }
            else {
                table[p][q] = (table[p-1][q] >= table[p][q-1] ? table[p-1][q] : table[p][q-1]);
                // compare the largest common length of (S1 without the last element and S2) and (S2 without the last element and S1)
            }
        }
        
    }
    commonlen = table[len1][len2];
    // find and store lcs
    int x = commonlen;
    int p = len1;
    while (x > 0) {
        if (S1[len1-1] == S2[len2-1]) {// from last element on, if same, then compare last second one...
        S[x - 1] = S1[len1-1];
        len1 --;
        len2 --;
        x --;
        }
        else {
            // if not same, then compare the last second of S1 with last element of S2 AND compare the last second of S2 with last of S1
            table[len1-1][len2] > table[len1][len2-1] ? len1 -- : len2 --;
        }
    }

    for (int i = 0; i < p + 1; i++)
    {
        free(table[i]);
        table[i] = NULL;
    }
    return commonlen;

}

// For the function, only compute the length of the LCS
int LCS_len (int len1, int len2, char *S1, char *S2) {

    int commonlen;
    int *table[len1 + 1];
    for (int i = 0; i < len1 + 1; i++)
    {
        table[i] = (int*) malloc ((len2 + 1) * sizeof(int));
    }
    // int table[len1+1][len2+1];//the row represent the first row-th elements of S1, the colomn represents the first colomn-th elements of S2
    for (int p = 0; p <= len1; p++)
    {
        for (int q = 0; q <= len2; q++)
        {
            if (p == 0 || q == 0) table[p][q] = 0;// set the 0-th row and 0-th colomn be 0
            else if (S1[p-1] == S2[q-1]) {
                table[p][q] = table[p-1][q-1] + 1;// if p-th value in S1 equal to q-th value in S2, current common length increased by 1
            }
            else {
                table[p][q] = (table[p-1][q] >= table[p][q-1] ? table[p-1][q] : table[p][q-1]);
                // compare the largest common length of (S1 without the last element and S2) and (S2 without the last element and S1)
            }
        }
        
    }
    commonlen = table[len1][len2];
    for (int i = 0; i < len1 + 1; i++)
    {
        free(table[i]);
        table[i] = NULL;
    }
    return commonlen;
}

// This function compute 4 sequences' LCS
int LCS4 (int a, int b, int c, int d, char *A, char *B, char *C, char *D, char *S) {

    int commonlen;
    char ***table[a+1];
    // The code below is dynamic allocate a 4 dimentional array
    for (int i1 = 0; i1 <= a; i1++){
        table[i1] = (char***) malloc ((b + 1) * sizeof(*table[i1]) + 1);
        if(table[i1] == NULL) {
            printf("Allocation Error!");
            exit(1);
        }
        for(int i2 = 0; i2 <= b; i2++){
            table[i1][i2] = (char**) malloc ((c + 1) * sizeof(*table[i1][i2]) + 1);
            if(table[i1][i2] == NULL) {
                printf("Allocation Error!");
                exit(1);
            }
            for (int i3 = 0; i3 <= c; i3++){
                table[i1][i2][i3] = (char*) malloc ((d + 1) * sizeof(char) + 1);
                if(table[i1] == NULL) {
                    printf("Allocation Error!");
                    exit(1);
                }
            }
        }
    }
    // fill the table
    for (int i1 = 0; i1 <= a; i1++)
        for(int i2 = 0; i2 <= b; i2++)
            for (int i3 = 0; i3 <= c; i3++)
                for (int i4 = 0; i4 <= d; i4++)
                {
                    if(i1 == 0 || i2 == 0 || i3 == 0 || i4 == 0) table[i1][i2][i3][i4] = '0';// base case, initialize the table
                    else if (A[i1-1] == B[i2-1] && B[i2-1] == C[i3-1] && C[i3-1] == D[i4-1]) {
                        table[i1][i2][i3][i4] = table[i1-1][i2-1][i3-1][i4-1] + 1;
                    }
                    else table[i1][i2][i3][i4] = max(table[i1-1][i2][i3][i4], table[i1][i2-1][i3][i4], table[i1][i2][i3-1][i4], table[i1][i2][i3][i4-1]);
                }
    
    commonlen = table[a][b][c][d] - '0';
    // find and store lcs
    int x = commonlen;
    int i1 = a, i2 = b, i3 = c, i4 = d;
    while (x > 0) {
        if (A[i1-1] == B[i2-1] && B[i2-1] == C[i3-1] && C[i3-1] == D[i4-1]) {// from last element on, if same, then compare last second one...
        S[x - 1] = A[i1-1];
        i1 --; i2 --; i3--; i4--;
        x --;
        }
        else {
            // if not same, then compare the last second of S1 with last element of S2 AND compare the last second of S2 with last of S1
            if (table[i1-1][i2][i3][i4] == max(table[i1-1][i2][i3][i4], table[i1][i2-1][i3][i4], table[i1][i2][i3-1][i4], table[i1][i2][i3][i4-1])) i1--;
            else if (table[i1][i2-1][i3][i4] == max(table[i1-1][i2][i3][i4], table[i1][i2-1][i3][i4], table[i1][i2][i3-1][i4], table[i1][i2][i3][i4-1])) i2--;
            else if (table[i1][i2][i3-1][i4] == max(table[i1-1][i2][i3][i4], table[i1][i2-1][i3][i4], table[i1][i2][i3-1][i4], table[i1][i2][i3][i4-1])) i3--;
            else i4--;
        }
    }
// the code below is to free the memmory
    for (int i1 = 0; i1 <= a; i1++){
        for(int i2 = 0; i2 <= b; i2++){
            for (int i3 = 0; i3 <= c; i3++){
                free(table[i1][i2][i3]);
                table[i1][i2][i3] = NULL;
            }
            free(table[i1][i2]);
            table[i1][i2] = NULL;
        }
        free(table[i1]);
        table[i1] = NULL;
    }

    return commonlen;
}

// This function only compute the length of LCS
int LCS4_len (int a, int b, int c, int d, char *A, char *B, char *C, char *D) {

    int commonlen;
    char ***table[a+1];
    for (int i1 = 0; i1 <= a; i1++){
        table[i1] = (char***) malloc ((b + 1) * sizeof(*table[i1]) + 1);
        if(table[i1] == NULL) {
            printf("Allocation Error!");
            exit(1);
        }
        for(int i2 = 0; i2 <= b; i2++){
            table[i1][i2] = (char**) malloc ((c + 1) * sizeof(*table[i1][i2]) + 1);
            if(table[i1][i2] == NULL) {
                printf("Allocation Error!");
                exit(1);
            }
            for (int i3 = 0; i3 <= c; i3++){
                table[i1][i2][i3] = (char*) malloc ((d + 1) * sizeof(char) + 1);
                if(table[i1] == NULL) {
                    printf("Allocation Error!");
                    exit(1);
                }
            }
        }
    }
    for (int i1 = 0; i1 <= a; i1++)
        for(int i2 = 0; i2 <= b; i2++)
            for (int i3 = 0; i3 <= c; i3++)
                for (int i4 = 0; i4 <= d; i4++)
                {
                    if(i1 == 0 || i2 == 0 || i3 == 0 || i4 == 0) table[i1][i2][i3][i4] = '0';
                    else if (A[i1-1] == B[i2-1] && B[i2-1] == C[i3-1] && C[i3-1] == D[i4-1]) {
                        table[i1][i2][i3][i4] = table[i1-1][i2-1][i3-1][i4-1] + 1;
                    }
                    else table[i1][i2][i3][i4] = max(table[i1-1][i2][i3][i4], table[i1][i2-1][i3][i4], table[i1][i2][i3-1][i4], table[i1][i2][i3][i4-1]);
                }
    
    commonlen = table[a][b][c][d] - '0';
    // the code below is to free the memmory
    for (int i1 = 0; i1 <= a; i1++){
        for(int i2 = 0; i2 <= b; i2++){
            for (int i3 = 0; i3 <= c; i3++){
                free(table[i1][i2][i3]);
                table[i1][i2][i3] = NULL;
            }
            free(table[i1][i2]);
            table[i1][i2] = NULL;
        }
        free(table[i1]);
        table[i1] = NULL;
    }
    return commonlen;
}