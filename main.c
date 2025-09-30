#include "calc_types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXBUFFER 100
ELEMENT buffer[MAXBUFFER];
int pos = 0;

int set_pri(char);
int push(ELEMENT el);
void create_number(ELEMENT*, char*);
void create_operation(ELEMENT*, char);

int main(int argc, char *argv[]) {
    ELEMENT now_el;
    char oper[MAXBUFFER];
    int o_pos = 0;
    for (int i = 1; i < argc; i++) {
        if (isdigit(argv[i][0])) {
            create_number(&now_el, argv[i]);
            if (push(now_el)) return 1;
        } else if (MAXBUFFER >= o_pos) switch (argv[i][0]) {
            case '-': case '+': case '/': case 'x': {
                for (int hier = set_pri(argv[i][0]); o_pos > 0 && hier <= set_pri(oper[o_pos-1]) && oper[o_pos-1] != 'b';) {
                    create_operation(&now_el, oper[--o_pos]);
                    if(push(now_el)) return 1;
                };
                oper[o_pos++] = argv[i][0];
                break;
            }
            case '^': {
                oper[o_pos++] = '^';
                break;
            }
            case 'b':
                oper[o_pos++] = 'b'; 
                break;
            case 'd':
                while (o_pos > 0 && oper[o_pos-1] != 'b') {
                    create_operation(&now_el, oper[--o_pos]);  
                    push(now_el);
                }
                if (o_pos == 0 || oper[o_pos-1] != 'b') {
                    error("no closed brecker");
                    return 1;
                } 
                o_pos--;
                break;
            default: 
                error("unknow operation: %c", argv[i][0]);
                return 1;
        };
    }
    while (o_pos>0) {
        create_operation(&now_el, oper[--o_pos]);
        push(now_el);
    };
    for (int i = 0; i < pos; i++) {
        switch (buffer[i].type){ 
            case NUMBER_OP: 
                printf("%d ", buffer[i].element.NUM.number);
                break;
            case OPERATION_OP:
                printf("%c ", buffer[i].element.OP.op);
                break;
        }
    }
    putchar('\n');
    return 0;
}

inline void create_number(ELEMENT* el, char *text) {
    el->type = NUMBER_OP;
    el->element.NUM.number = atoi(text);
}

inline void create_operation(ELEMENT* el, char ch) {
    el->type = OPERATION_OP;
    el->element.OP.op = ch;
}
int push(ELEMENT el) {
    if (pos <= MAXBUFFER) {
        buffer[pos++] = el; 
        return 0;
    };
    error("the stack is already full");
    return 1;
}

int set_pri(char i) {
    switch (i) {
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

