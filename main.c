#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXBUFFER 20
typedef struct {
    int num;
    int mode;
} element;

element stack[MAXBUFFER];
int pos = 0;
int ex[MAXBUFFER];
int o_pos = 0;

void push(element);
int set_pri(char);

int main(int argc, char* argv[]) {
    printf("args: ");
    for (int i = 1; i < argc; i++) printf("%d: %s\n", i, argv[i]);
    element now_el;
    for (int i = 1; i < argc; i++) {
        if (isdigit(argv[i][0])) {
            now_el.mode = 1;
            now_el.num = atoi(argv[i]);
            push(now_el);
        } else if (o_pos <= MAXBUFFER) {
            for (int hier = set_pri(argv[i][0]); hier <= set_pri(ex[o_pos]) && o_pos > 0; o_pos--) {
                now_el.mode = 0;
                now_el.num = ex[o_pos];
                push(now_el);
            }
            ex[o_pos++] = argv[i][0];
            printf("oper: %c\n", (char)ex[o_pos-1]);
        }
    }
    while (o_pos >= 0) {
        now_el.mode = 0;
        now_el.num = ex[o_pos--];
        push(now_el);
    }
    for (int i = 0; i < pos; i++) {
        if (stack[i].mode) printf("%d ", stack[i].num); else printf("%c ", (char) stack[i].num);
    };
    putchar('\n');
    return 0;
}

void push(element el) {
    if (pos >= MAXBUFFER) printf("too much symbols\n");
    stack[pos++] = el;
}

int set_pri(char op) {
    switch (op) {
        case '-': case '+':
            return 1;
        case '/': case 'x':
            return 2;
        case '^':
            return 3;
        case '(':
            return 0;
        default: return -1;
    }
}
