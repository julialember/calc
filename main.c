
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("at least 3 args");
        return 1;
    };
    int first = atoi(argv[1]);
    int second = atoi(argv[3]);
    switch (argv[2][0]) {
        case '-':
            printf("%d\n", first - second);
            break;
        case '+':
            printf("%d\n", first + second);
            break;
        case '/':
            if (second == 0) {
                printf("you can't div to 0\n");
                return 1;
            };
            printf("%g\n", (float) first/second);
            break;
        case 'x':
            printf("%d\n", first * second);
            break;
        default:
            printf("unknown operation\n");
            return 1;
    }
    return 0;
}
