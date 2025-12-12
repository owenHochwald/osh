#include <stdio.h>
#include <string.h>
#include <_stdlib.h>

// read in a block, realloc more size if needed
#define BUFFER_SIZE 1024
char * osh_read_line(void) {
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char *buffer = (char*) malloc(sizeof(char) * buffer_size);
    int c; // current character

    if (!buffer) {
        printf("Some sort of buffer allocation error");
        exit(EXIT_FAILURE);
    }

    // reader loop
    while (1) {
        c = getchar();

        // replace with null termination and finish
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
         } else {
            buffer[position++] = c;
         }
        position++;

        // need to realloc b/c we're gonna exceed
        if (position >= buffer_size) {
            buffer_size += BUFFER_SIZE;
            buffer = (char*) realloc(buffer, buffer_size);
            if (!buffer) {
                printf("Some sort of buffer reallocation error");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char *read_line(void) {
    char *line = NULL;
    size_t buffsize = 0; // getline will make buffer for us

    if (getline(&line, &buffsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS); // if we have an EOF
        } else {
            perror("Error reading line");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

// tokenizer
#define TOK_BUFFSIZE 64
#define TOK_DELIM " \t\n\a\r"
char ** osh_split_line(char * line) {
    int buffer_size = TOK_BUFFSIZE;
    int position = 0;
    char **tokens = (char **) malloc(buffer_size * sizeof(char*));
    char *token;

    // just safety for us
    if (!tokens) {
        printf("Some sort of token allocation error");
        exit(EXIT_FAILURE);
    }

    // delim the line we're reading in
    token = strtok(line, TOK_DELIM);

    while (token != NULL) {
        tokens[position++] = token;

        // reallocate if we have to
        if (position >= buffer_size) {
            buffer_size += TOK_BUFFSIZE;
            tokens = (char **) realloc(tokens, buffer_size * sizeof(char*));
            if (!tokens) {
                printf("Some sort of token reallocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM); // continue where we left off
    }

    tokens[position] = NULL;
    return tokens;
}

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
    } while (status); // use returned status for exit determination
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
