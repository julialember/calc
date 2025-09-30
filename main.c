#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXBUFFER 20
typedef struct {
    char *text;
    int mode;
} element;

element stack[MAXBUFFER];
int pos = 0;
char* ex[MAXBUFFER];
int o_pos = 0;

void push(element);
int set_pri(char*);

int main(int argc, char* argv[]) {
    element now_el;
    for (int i = 1; i < argc; i++) {
        if (isdigit(argv[i][0])) {
            now_el.mode = 1;
            now_el.text = argv[i];
            push(now_el);
        } else if (o_pos <= MAXBUFFER) switch (argv[i][0]) {
            case '/': case 'x': case '+': case '-':  
            for (int hier = set_pri(argv[i]); o_pos > 0 && hier <= set_pri(ex[o_pos-1]);) {
                now_el.mode =0;
                now_el.text = ex[--o_pos];
                push(now_el);
            };
            ex[o_pos++] = argv[i];
            break;
            case '^': 
                for (int hier = set_pri(argv[i]); o_pos > 0 && hier < set_pri(ex[o_pos-1]);) {
                now_el.mode =0;
                now_el.text = ex[--o_pos];
                push(now_el);
            };
            ex[o_pos++] = argv[i];
            break;
            case 'b':
                ex[o_pos++] = argv[i];
                break;
            case 'd':
                while (o_pos > 0 && ex[o_pos-1][0] != 'b') {
                    now_el.mode = 0;
                    now_el.text = ex[--o_pos];
                    push(now_el);
                };
                if (o_pos == 0 || ex[o_pos][0] != 'b') {
                    printf("unclosed brecker\n");
                    return 1;
                }
                o_pos--;
                break;
        }
    };
    now_el.mode = 0;
    while (o_pos>0) {
        now_el.text = ex[--o_pos];
        push(now_el);
    };
    return 0;
}


void push(element el) {
    if (pos >= MAXBUFFER) printf("too much symbols\n");
    stack[pos++] = el;
}

int set_pri(char* op) {
    switch (op[0]) {
        case '-': case '+':
            return 1;
        case '/': case 'x':
            return 2;
        case '^':
            return 3;
        case 'b':
            return 0;
        default: return -1;
    }
}
