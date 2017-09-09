#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE *input, *output;
    char *message = argv[3];
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    return 0;
}
