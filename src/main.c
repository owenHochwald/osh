#include <stdio.h>
#include <_stdlib.h>


char * osh_read_line(void);

char ** osh_split_line(char * line);

int osh_execute(char ** args);

// Read commands, parse into program, execute commands
void osh_loop(void) {
    char * line;
    char ** args;
    int status;

    do {
        printf("> ");
        line = osh_read_line();
        args = osh_split_line(line);
        status = osh_execute(args);

        free(line);
        free(args);
    } while (status);
}

// LIFETIME:
// 1. Init, 2. Interpret, 3. Terminate
int main(void) {
    // Init

    // Interpret. Run command loop
    printf("Hello, World!\n");
    osh_loop();

    // Terminate


    return EXIT_SUCCESS;
}
