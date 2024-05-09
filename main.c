#include "include/file.h"
#include "include/trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *file_name = "profanity_en.csv";
const char *to_clean;
char replace_with = '*';

int main(int argc, char *argv[]) {
    const char *prog_name = argv[0];

    if (argc == 1) {
        fprintf(stderr,
                "Usage %s <file_to_clean> -r<replace_obscene-word_with>",
                prog_name);
        exit(8);
    }

    to_clean = argv[1];

    char *first_col_token;  /* store token of first field */
    char *second_col_token; /* store token of second field */

    /* creating trie to store all the obscenity words */
    struct trie *t1 = create_trie();

    /* opening the file */
    file_open(file_name);

    /* read next line from the input file until we hit EOF */

    while (read_next_line() != NULL) {

        first_col_token = get_col_item();  /* will return first col item */
        second_col_token = get_col_item(); /* will return first col item */

        /* TODO: check if the word(first_col_token) is already present in the
         * trie maybe a hasmap would suitabe */
        /* insert the token to trie */
        trie_insert(t1, first_col_token);
        trie_insert(t1, second_col_token);
    }

    /* closing the file */
    file_close();

    /* read the file to clean */
    file_open(to_clean);

    if ((argc > 2) && argv[2][0] == '-' && argv[2][1] == 'r') {
        replace_with = argv[2][2];
    }

    while (argc) {
        printf("%s\n", *argv);
        ++argv;
        --argc;
    }
    char *token;
    while ((token = next_word()) != NULL) {
        if (trie_search(t1, token) == 1) {
            replace_word(token, replace_with);
        }
    }

    /* close */
    file_close();
    return 0;
}
