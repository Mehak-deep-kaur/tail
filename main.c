#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 256
void print_last_n_lines(char** circular_buffer, int n, int buffer_size) {
    int start = n;
    if (buffer_size < n) {
        start = buffer_size;
    }
    for (int i = 0; i < start; i++) {
        printf("%s", circular_buffer[(i + buffer_size) % buffer_size]);
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Error: Invalid value for 'n'.\n");
        return 1;
    }
    char** circular_buffer = (char**)malloc(n * sizeof(char*));
    if (circular_buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        circular_buffer[i] = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
        if (circular_buffer[i] == NULL) {
            printf("Error: Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(circular_buffer[j]);
            }
            free(circular_buffer);
            return 1;
        }
    }
    int buffer_size = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        strncpy(circular_buffer[buffer_size % n], line, MAX_LINE_LENGTH);
        buffer_size++;
    }
    print_last_n_lines(circular_buffer, n, buffer_size);
    for (int i = 0; i < n; i++) {
        free(circular_buffer[i]);
    }
    free(circular_buffer);
    return 0;
}
