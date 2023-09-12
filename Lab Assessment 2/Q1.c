#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
void ascending(const int *a);
void descending(const int *a);
int main(void) {
    int a[SIZE] = {0};
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % SIZE;
    }
    puts("Data items in original order");
    for (int i = 0; i < SIZE; i++) {
        printf("%4d", a[i]);
    }
    char g;
    printf("\nEnter A for Ascending and D for Descending: ");
    scanf(" %c", &g);
    switch (g) {
        case 'A':
        case 'a':
            ascending(a);
            break;
        case 'D':
        case 'd':
            descending(a);
            break;
        default:
            printf("Invalid input\n");
            break;
    }
    return 0;
}

void ascending(const int *a) {
    int *b = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        b[i] = a[i];
    }
    for (int pass = 1; pass < SIZE; pass++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (b[i] > b[i + 1]) {
                int hold = b[i];
                b[i] = b[i + 1];
                b[i + 1] = hold;
            }
        }
    }
    puts("Data items in ascending order");
    for (int i = 0; i < SIZE; i++) {
        printf("%4d", b[i]);
    }
    puts("");
    free(b);
}
void descending(const int *a) {
    int *b = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        b[i] = a[i];
    }
    for (int pass = 1; pass < SIZE; pass++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (b[i] < b[i + 1]) {
                int hold = b[i];
                b[i] = b[i + 1];
                b[i + 1] = hold;
            }
        }
    }
    puts("Data items in descending order");
    for (int i = 0; i < SIZE; i++) {
        printf("%4d", b[i]);
    }
    puts("");
    free(b);
}
