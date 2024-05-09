#include "../include/token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* max line read at once */
#define SIZE 1000

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct {
    FILE *in_file;   /* the input file itself */
    char line[SIZE]; /* line to read from input file */
    char token[50];  /* token in a file */
} struct_file;

static int token_init = FALSE; /* TRUE if reading token from a single line sequentially */
struct_file file = {NULL, "", ""};

static int initial_read =
    FALSE; /* True if we have ready initial line of vulgur file */

char *read_next_line() {
    token_init = FALSE; /* time to process next line for tokenization */
    return fgets(file.line, sizeof(file.line), file.in_file);
}

void file_open(const char *file_name) {
    if (file.in_file) {
        fprintf(stderr, "Error: some other file is already open");
        abort();
    }

    file.in_file = fopen(file_name, "r+");
    if (!file.in_file) {
        fprintf(stderr, "Error: could not open the file %s", file_name);
        abort();
    }
    if (!initial_read) {
        initial_read = TRUE;
        /* ignore the first line */
        read_next_line();
    }
}

void file_close(void) {
    if (file.in_file) {
        fclose(file.in_file);
        file.in_file = NULL;
    }
}

static void fill_space(char *token) {
    if (token == NULL)
        return;

    while (*token != '\0') {
        if (isspace(*token)) {
            *token = '-';
        }
        ++token;
    }
}

char *get_col_item(void) {
    static char *token;
    if (!token_init) {
        token_init = TRUE;
        token = strtok(file.line, ",");
        return token;
    }
    token = strtok(NULL, ",");
    return token;
}

char *get_field(int field_num) {
    static char *token;
    token = strtok(file.line, ",");

    while (token != NULL) {
        if ((--field_num) == 0) {
            /* remove new line character */
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }

            /* trim trailing and leading spaces */
            token = trim_white_space(token);

            /* include - between spaces in the token */
            fill_space(token);
            return token;
        }
        token = strtok(NULL, ",");
    }

    /* should never reach here */
    return "";
}

void replace_word(char *token, char replace_with) {
    /* +1 to correctly place pointer to the start of the word */
    size_t len_token = strlen(token) + 1;

    // Go back by len_token
    if (fseek(file.in_file, -len_token, SEEK_CUR)) {
        fprintf(stderr, "fseek() failed in file");
        file_close();
        abort();
    }

    while (len_token > 1) {
        fputc(replace_with, file.in_file);
        --len_token;
    }
}

char *next_word(void) {
    int ch;
    int i = 0;

    /* advance util we hit a character(non-space)*/
    while ((ch = fgetc(file.in_file)) != EOF && isspace(ch))
        ;

    /* reached the end? */
    if (ch == EOF)
        return NULL;

    /* *
     *
     * " 69" pointer in in_file will point to 6 after above code gets executed
     * now when below line is executed in_file pointer will points to 9 hence
     * we lost the character 6 first character in order to fix it we need to
     * push 6 back to stream
     *
     * */
    ungetc(ch, file.in_file);
    while ((ch = fgetc(file.in_file)) != EOF) {
        if (isspace(ch))
            break;
        file.token[i] = ch;
        ++i;
    }
    file.token[i] = '\0';
    return file.token;
}
