#ifndef TRIE_H
#define TRIE_H

/* storing every ascii characters */
#define CHAR_SIZE 255

struct trie {
    int is_leaf;
    struct trie *childrens[CHAR_SIZE];
};

/* 
 * create_trie -- create initial node for trie tree
 *
 * Returns:
 *          trie node
 */
extern struct trie *create_trie(void); 

/* 
 * trie_search -- insert a string to the trie
 *
 * Params:
 *          root -- root of the trie tree
 *          str -- string to search for
 * */
extern void trie_insert(struct trie *root, char *str);

/* 
 * trie_search -- search string in the trie 
 *
 * Params:
 *          root -- root of the trie tree
 *          str -- string to search for
 * Returns:
 *          1 -- found 
 *          0 -- not found
 * */
extern int trie_search(struct trie *root, char *str);
#endif
