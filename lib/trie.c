#include "trie.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

static int trie_setup = FALSE; /* TRUE if the trie is setup */

static struct trie *init_trie() {
    struct trie *node = (struct trie *)malloc(sizeof(struct trie));
    node->is_leaf = FALSE;

    /* nulling childrens */
    for (int i = 0; i < CHAR_SIZE; ++i) {
        node->childrens[i] = NULL;
    }
    return node;
}

/* create trie root node */
extern struct trie *create_trie(void) {
    trie_setup = TRUE;
    return init_trie();
}

static struct trie *create_trie_node() {
    struct trie *node = (struct trie *)malloc(sizeof(struct trie));
    node->is_leaf = FALSE;

    for (int i = 0; i < CHAR_SIZE; i++) {
        node->childrens[i] = NULL;
    }

    return node;
}

static void trie_insert_util(struct trie *head, char *str) {
    /* start from the root node */
    struct trie *cur = head;
    while (str && *str != '\0') {
        /* create a new node if the path doesn't exist */
        if (cur->childrens[(int)*str] == NULL) {
            cur->childrens[(int)*str] = create_trie_node();
        }

        /* go to the next node */
        cur = cur->childrens[(int)*str];

        /* move to the next childrens */
        str++;
    }

    /* mark the headrent node as a leaf */
    cur->is_leaf = TRUE;
}

/* insert string to the trie tree */
void trie_insert(struct trie *head, char *str) {
    if (!trie_setup) {
        fprintf(stderr, "Error: create_trie must be called initially");
        abort();
    }

    if (!str)
        return;

    trie_insert_util(head, str);
}

/* search a string in a trie tree */
int trie_search(struct trie *head, char *str) {
    if (!trie_setup) {
        fprintf(stderr, "Error: create_trie must be called initially");
        abort();
    }

    if (head == NULL) {
        return FALSE;
    }

    /* we don't want to modify str because we would be needing the full length
     * of the word including ", ., ;.
     */
    char *new_str = strdup(str);

    char *temp_str = new_str;
    /* clean string such as '"nigga"' 'nigga.' 'nigga;' */
    char *end;
    while (*temp_str == '"' || *temp_str == '.' || *temp_str == ';' ||
           *temp_str == ',')
        ++temp_str;

    end = temp_str + strlen(temp_str) - 1;
    while ((end > temp_str) &&
           (*end == '"' || *end == '.' || *end == ';' || *end == ',' || *end == '?'))
        --end;
    end[1] = '\0';

    /* convert all the characters to lowercase */
    register int i = 0;
    while (temp_str[i] != '\0') {
        temp_str[i] = tolower(temp_str[i]);
        ++i;
    }

    while (*temp_str) {
        head = head->childrens[(int)*temp_str];
        if (head == NULL) {
            return FALSE;
        }
        ++temp_str;
    }

    free(new_str);
    return head->is_leaf;
}
