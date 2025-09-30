
typedef struct {
    int number;
} NUMBER;

typedef struct {
    char op;
} OPERATION;

typedef enum {
    NUMBER_OP, 
    OPERATION_OP,
} eltype;

typedef struct {
    eltype type;
    union {
        NUMBER NUM; 
        OPERATION OP;
    } element; 
} ELEMENT;

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
static inline void error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}
