#include <ctype.h>
#include <stdio.h>
#include <string.h>

char *trim_white_space(char *str) {
    char *out;

    if (*str == '\0')
        return NULL;

    /* remove leading spaces */
    while (isspace(*str))
        ++str;

    /* if all was spaces in str */
    if (*str == '\0')
        return NULL;

    out = str + strlen(str) - 1;

    while ((out > str) && isspace(*out)) 
        out--;

    out[1] = '\0';
    return str;
}
