#include "calc_types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXBUFFER 100
ELEMENT buffer[MAXBUFFER];
int pos = 0;

int set_pri(char);
int push(ELEMENT el);
void create_number(ELEMENT*, int);
void create_operation(ELEMENT*, char);

int main(int argc, char *argv[]) {
    ELEMENT now_el;
    char oper[MAXBUFFER];
    int o_pos = 0;
    for (int i = 1; i < argc; i++) {
        if (isdigit(argv[i][0]) || isdigit(argv[i][1])) {
            create_number(&now_el, atoi(argv[i]));
            if (push(now_el)) return 1;
        } else if (MAXBUFFER >= o_pos) switch (argv[i][0]) {
            case '-': case '+': case '/': case 'x': {
                for (int hier = set_pri(argv[i][0]); o_pos > 0 && 
                        hier <= set_pri(oper[o_pos-1]) && oper[o_pos-1] != 'b';) {
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
                    if(push(now_el)) return 1;
                }
                if (o_pos == 0 || oper[o_pos-1] != 'b') {
                    error("unclosed brecker");
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
        if (oper[--o_pos] == 'b') {
            error("unclosed brecker");
            return 1;
        };
        create_operation(&now_el, oper[o_pos]);
        if(push(now_el)) return 1;
    };
    float answer[5];
    int answer_pos = 0;
    for (int i = 0; i < pos; i++) {
        switch (buffer[i].type) {
            case NUMBER_OP: 
                answer[answer_pos++] = buffer[i].element.NUM.number;
                break;
            case OPERATION_OP: 
                if (answer_pos < 2) {
                    error("not enought argumnets");
                    return 1; 
                }
                answer_pos-=1;
                switch (buffer[i].element.OP.op) {
                    case '-': 
                        answer[answer_pos-1] = answer[answer_pos-1] - answer[answer_pos];
                        break;
                    case '+':
                        answer[answer_pos-1] = answer[answer_pos-1] + answer[answer_pos];
                        break;
                    case 'x' :
                        answer[answer_pos-1] = answer[answer_pos-1] * answer[answer_pos]; 
                        break;
                    case '^':
                        answer[answer_pos-1] = pow(answer[answer_pos-1], answer[answer_pos]);
                        break;
                    case '/': 
                        if (answer[answer_pos]==0) {
                            error("division to zero!");
                            return 1;
                        } 
                        answer[answer_pos-1] = (float) answer[answer_pos-1] / answer[answer_pos];
                        break;
                    default:
                        error("unknown argumnet: %c", buffer[i].element.OP.op);
                        return 1;
                } 
        }
    }
    printf("%g\n", answer[0]);
    return 0;
}

inline void create_number(ELEMENT* el, int number) {
    el->type = NUMBER_OP;
    el->element.NUM.number = number;
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

