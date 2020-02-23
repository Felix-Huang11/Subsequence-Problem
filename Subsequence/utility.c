#include "utility.h"
#define N 10002

const char * restrict inputfile;
const char * restrict outputfile;
void clear(char *A, int len) {
    for (int i = 0; i < len; i++)
    {
        A[i] = ' ';
    }
}

// input a char array, then return the current number of input-elements of this array(Not the largest size N!!)
int getlen(char *S) {
    int len = 0;
    while (len < N && S[len] != '\n' && S[len] != '\0')
    {
        len ++;
    }
    return len;
}

// input a char array, if this array only contains digit elements, it will return 1; otherwise, return 0
int check(char *S) {
    int judge = 1;
    int i = 0;
    while (i <= N && S[i] != '\n' && S[i] != '\0')
    {
        if (isdigit(S[i]) == 0) judge = 0;// I find isdigit() method in this web page..https://www.programiz.com/c-programming/library-function/ctype.h/isdigit
        i ++;
    }
    return judge;
}

// Given S1, S2, this will prompt user input two sequences, and store these two sequences in S1, S2 respectively
void userInput(char *S1, char *S2) {

    printf("Enter the first sequence: ");
    fgets(S1, N, stdin);// I learned fgets from this web page: https://stackoverflow.com/questions/19794268/scanf-reading-enter-key
    while (check(S1) == 0)
    {
        printf("Error, non-digit character detected!\n\n");
        printf("Enter the first sequence: ");
        fgets(S1, N, stdin);
    }

    printf("Enter the second sequence: ");
    fgets(S2, N, stdin);
    while (check(S2) == 0)
    {
        printf("Error, non-digit character detected!\n\n");
        printf("Enter the first sequence: ");
        fgets(S1, N, stdin);
        printf("Enter the second sequence: ");
        fgets(S2, N, stdin);
    }

}
// ask user input one sequence
void userInputOne(char *S1) {

    printf("Enter the sequence: ");
    fgets(S1, N, stdin);// I learned fgets from this web page: https://stackoverflow.com/questions/19794268/scanf-reading-enter-key
    while (check(S1) == 0)
    {
        printf("Error, non-digit character detected!\n\n");
        printf("Enter one sequence: ");
        fgets(S1, N, stdin);
    }
}

// This function is for printing
void print_seq(int len, char *S){
    for(int i = 0; i < len; i++){
        printf("%c", S[i]);
    }
    printf("\n");
}

// This function randomly generate two sequences
void generate_seq(char *S1, char *S2) {
    int l1, l2;
    int i = 0, j = 0;
    int d = '9' - '0';
    srand(time(0));
    printf("Enter the lengths of two sequences(<=10000): ");
    if (scanf("%d", &l1) != 1) {
        printf("Invalid Input");
        exit(0);
    }
    if (scanf("%d", &l2) != 1) {
        printf("Invalid Input");
        exit(0);
    }
    
    while(i < l1) {
        char ch = (rand() % (d+1)) + '0';
        S1[i++] = ch;
    }
    while(j < l2) {
        char ch = (rand() % (d+1)) + '0';
        S2[j++] = ch;
    }

}

// This function read one sequence for the given inout file
void readone_from(const char * restrict filename, char *S) {
    FILE *fp;
    if((fp = fopen(filename, "r")) == NULL){
        printf("Openfile Error! File doesn't exist!");
        exit(1);
    }
    fgets(S, N, fp);
    if (check(S) == 0) {
        printf("Error, non-digit character detected!\n");
        exit(1);
    }
    fclose(fp);
}
// This function read two sequences from the given input file
void readtwo_from(const char * restrict filename, char *S1, char *S2) {
    FILE *fp;
    if((fp = fopen(filename, "r")) == NULL){
        printf("Openfile Error! File doesn't exist!");
        exit(1);
    }
    fgets(S1, N, fp);
    fgets(S2, N, fp);
    if (check(S1) == 0 || check(S2) == 0) {
        printf("Error, non-digit character detected!\n");
        exit(1);
    }
    fclose(fp);
}
// Write the sequence into the given output file
void write_to(const char * restrict filename, char *S, int len) {
    FILE *fp;
    if((fp = fopen(filename, "a")) == NULL){
        printf("Openfile Error!");
        exit(1);
    }
    for(int i = 0; i < len; i++){
        fprintf(fp, "%c", S[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}
// This function deal with the shell command, If user input this command, this command will store 1 into specific position, if not, store 0
void getCommand(int argc, char *argv[], int cmd[10]){
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) {
            cmd[0] = 1;
            continue;
        }
        if (strcmp(argv[i], "-c") == 0) {
            cmd[1] = 1;
            continue;
        }
        if (strcmp(argv[i], "-t") == 0) {
            cmd[2] = 1;
            continue;
        }
        if (strcmp(argv[i], "-p") == 0) {
            cmd[3] = 1;
            continue;
        }
        if (strcmp(argv[i], "-ct") == 0) {
            cmd[4] = 1;
            continue;
        }
        if (strcmp(argv[i], "-cp") == 0) {
            cmd[5] = 1;
            continue;
        }
        if (strcmp(argv[i], "-i") == 0) {
            cmd[6] = 1;
            cmd[7] = 1;
            inputfile = argv[i+1];
            continue;
        }
        if (strcmp(argv[i], "-o") == 0) {
            cmd[8] = 1;
            cmd[9] = 1;
            outputfile = argv[i+1];
            continue;
        }
        if(i > 0 && (strcmp(argv[i-1], "-i") != 0) && (strcmp(argv[i-1], "-o") != 0)) {
            report_error();
            exit(1);
        }
    }
}
// This function will be called when user input invalid command
void report_error(void) {
    printf("Invlid Option!\n");
    printf("-g: to generate an instance consisting of two sequences over the digit alphabet\n");
    printf("-c: to compute an LCS for the two input sequences\n");
    printf("-t: to compute an LTS for the input sequence\n");
    printf("-p: to compute an LPS for the input sequence\n");
    printf("-ct: to compute an LCTS for the two input sequences\n");
    printf("-cp: to compute an LCPS for the two input sequences\n");
    printf("-i inputfilename:   to read in sequence(s) from file--inputfilename\n");
    printf("-o outputfilename:  to write all the results into the file--outputfilename\n");
}