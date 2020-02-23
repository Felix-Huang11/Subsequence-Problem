#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    time_t start_time = time(NULL);

    // char command[100];
    // sprintf(command, "./a3 -cp -i test500.in");
    // system(command);
    // for (int i = 0; i < 10; i++) {
    //     char command[100];
    //     sprintf(command, "./a3 -cp -i test500.in");
    //     system(command);

    // }

    printf("Real running time: %g sec.\n", difftime(time(NULL), start_time));

    return 0;
}
