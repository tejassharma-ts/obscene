#ifndef FILE_H
#define FILE_H

/* opening the file */
extern void file_open(const char *file_name);

/* closing the file */
extern void file_close(void);

/**
 * get_field --  getting value for specific field in csv file
 *
 * Returns:
 *          str -- the field value
 *          NULL -- end of the file
 **/
extern char *get_field(int field_num);

extern char *get_col_item(void);

/* read_next_line -- advances to the next line */
char *read_next_line(void);

/* get the next word */
char *next_word(void);

/* replace word with sequence of characters in the file */
void replace_word(char *token, char replace_with);

#endif // !FILE_H
