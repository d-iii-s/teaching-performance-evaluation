#include <stdio.h>

int indent = 0;

#define LOG_CALL(function) { \
    for (int space = 0 ; space < indent ; space ++) printf (" "); \
    printf ("> %s\n", # function); \
    indent ++; \
}

#define LOG_RETURN(function) { \
    indent --; \
    for (int space = 0 ; space < indent ; space ++) printf (" "); \
    printf ("< %s\n", # function); \
}
