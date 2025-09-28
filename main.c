
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define MAXBUFFER 100
int buffer[MAXBUFFER];
size_t buffer_size = 0;

void push(int part) {
    if (buffer_size <= MAXBUFFER) buffer[buffer_size++] = part;
    else printf("too much symbols in your expr\n");
}

int pop() {
    return buffer_size > 0 ? buffer[--buffer_size] : -1;
}

void convert_to_post(char* argv[]) {
    
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (isdigit(argv[i][0]))
            push(atoi(argv[i]));
        else switch (argv[i][0]) {
            case '-':  {
                int second = pop(); 
                printf("%d\n", pop() - second); 
                break;
            };
            case '+': 
                printf("%d\n", pop() + pop());
                break;
            default: 
                printf("unknown operation\n");
                return 1;
        }
    }
    return 0;
}
