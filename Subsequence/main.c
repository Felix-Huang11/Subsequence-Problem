/* Time Table
// |    | 50   | 100  | 200  | 500  | 1000  | 2000  | 5000  | 10000  |
// | -c | 0    | 0    | 0    | 0    | 0     | 0     | 0.2   | 0.9    |
// | -t | 0    | 0    | 0    | 0.2  | 1.1   | 8.2   | 140   | 1121   |
// | -p | 0    | 0    | 0    | 0    | 0     | 0     | 0.2   | 0.9    |
// |-ct | 8.6  | 490  | 729  | -    | -     | -     | -     | -      |
// |-cp | 0.1  | 1.7  | 25.7 | 1379 | -     | -     | -     | -      |

*/
//#####################################################################################################################################################################
//# Submitting student: Zihao HUang(1596956)
//# Collaborating classmates: NO Collaborating classmates
//# Other collabrators: No
//# Reference: # I find isdigit() method in this web page..https://www.programiz.com/c-programming/library-function/ctype.h/isdigit
//            # I learned Dynamic memory allocation before lecture: https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
//              malloc, calloc, realloc, free
//            # I learned fgets from this web page: https://stackoverflow.com/questions/19794268/scanf-reading-enter-key
//#####################################################################################################################################################################

#include "main.h"
#define N 10002

int main (int argc, char *argv[]) {

    char *S1 = NULL;
    char *S2 = NULL;

    S1 = (char*)malloc(N * sizeof(char) + 1);
    S2 = (char*)malloc(N * sizeof(char) + 1);
    if(S1 == NULL || S2 == NULL) exit(0);

    extern const char * restrict inputfile;
    extern const char * restrict outputfile;

    int cmd[10];// the order in this array is -g, -c, -t, -p, -ct, -cp, -i, inputfile, -o, outputfile
    for(int i = 0; i < 10; i++) cmd[i] = 0;
    getCommand(argc, argv, cmd);// defined in utility.c
    
    if (cmd[0] == 1) {
        for(int i = 1; i < 8; i++) {
            if (cmd[i] == 1){
                report_error();// this means if you input -g, then you shouldn't input -c -p -t ect.
                exit(1);
            }
        }
        generate_seq(S1, S2);
        if (cmd[8] == 1) {// there is a output file here
            write_to(outputfile, S1, getlen(S1));
            write_to(outputfile, S2, getlen(S2));
        }
        else {// no output file
            print_seq(getlen(S1), S1);
            print_seq(getlen(S2), S2);
        }

    }
    // This condition, we need two sequences
    if (cmd[1] == 1 || cmd[4] == 1 || cmd[5] == 1) {
        if (cmd[6] == 1) readtwo_from(inputfile, S1, S2);// there is an input file
        else userInput(S1, S2);// no inputfile
        S1 = realloc(S1, getlen(S1) * sizeof(char) + 1);
        S2 = realloc(S2, getlen(S2) * sizeof(char) + 1);
        if (cmd[1] == 1) {// -c is executing
            char *S = NULL;
            S = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LCS (getlen(S1), getlen(S2), S1, S2, S);
            if (cmd[8] == 1) {// -o is executing
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LCS(length = %d) for two sequences is: \n", l);
                fclose(fp);
                write_to(outputfile, S, l);
            }
            else {
                printf("# an LCS(length = %d) for two sequences is: \n", l);
                print_seq(l, S);
            }
            free(S);
        }
        if (cmd[4] == 1) {// -ct is operating
            char *CT = NULL;
            CT = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LCTS(getlen(S1), getlen(S2), S1, S2, CT);
            if (cmd[8] == 1) {// -o is operating
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LCTS(length = %d) for two sequences is: \n", l);
                fclose(fp);
                write_to(outputfile, CT, l);
            }
            else {
                printf("# an LCTS(length = %d) for two sequences is: \n", l);
                print_seq(l, CT);
            }
            free(CT);
        }
        if (cmd[5] == 1) {// -cp is operating
            char *CP = NULL;
            CP = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LCPS(getlen(S1), getlen(S2), S1, S2, CP);
            if (cmd[8] == 1) {// -o is operating
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LCPS(length = %d) for two sequences is: \n", l);
                fclose(fp);
                write_to(outputfile, CP, l);
            }
            else {
                printf("# an LCPS(length = %d) for two sequences is: \n", l);
                print_seq(l, CP);
            }
            free(CP);
        }
        if (cmd[2] == 1) {// -t for the first sequence is operating
            char *T = NULL;
            T = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LTS(getlen(S1), S1, T);
            if (cmd[8] == 1) {// -o is operating
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LTS(length = %d) for the sequence is: \n", l);
                fclose(fp);
                write_to(outputfile, T, l);
            }
            else {
                printf("# an LTS(length = %d) for the sequence is: \n", l);
                print_seq(l, T);
            }
            free(T);
        }
        if (cmd[3] == 1) {// -p for the first sequence is operating
            char *P = NULL;
            P = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LPS(getlen(S1), S1, P);
            if (cmd[8] == 1) {// -o is operating
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LPS(length = %d) for the sequence is: \n", l);
                fclose(fp);
                write_to(outputfile, P, l);
            }
            else {
                printf("# an LPS(length = %d) for the first sequence is: \n", l);
                print_seq(l, P);
            }
            free(P);
        }
    }
    else {// this condition only need one sequence
        if (cmd[2] == 1) {// -t for this sequence is operating
            if (cmd[6] == 1) readone_from(inputfile, S1);// -i is operating
            else userInputOne(S1);
            S1 = realloc(S1, getlen(S1) * sizeof(char) + 1);
            char *T = NULL;
            T = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LTS(getlen(S1), S1, T);
            if (cmd[8] == 1) {// -o is operating
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LTS(length = %d) for the sequence is: \n", l);
                fclose(fp);
                write_to(outputfile, T, l);
            }
            else {
                printf("# an LTS(length = %d) for the sequence is: \n", l);
                print_seq(l, T);
            }
            free(T);
        }
        if (cmd[3] == 1) {// -p for this sequence is operating
            if (cmd[6] == 1) readone_from(inputfile, S1);// -i is operating
            else userInputOne(S1);
            S1 = realloc(S1, getlen(S1) * sizeof(char) + 1);
            char *P = NULL;
            P = (char*)malloc(getlen(S1) * sizeof(char) + 1);
            int l = LPS(getlen(S1), S1, P);
            if (cmd[8] == 1) {// -o is operating
                FILE *fp;
                if((fp = fopen(outputfile, "a")) == NULL){
                    printf("Openfile Error!");
                    exit(1);
                }
                fprintf(fp, "# an LPS(length = %d) for the sequence is: \n", l);
                fclose(fp);
                write_to(outputfile, P, l);
            }
            else {
                printf("# an LPS(length = %d) for the sequence is: \n", l);
                print_seq(l, P);
            }
            free(P);
        }
    }

    free(S1);
    free(S2);

    return 0;
}