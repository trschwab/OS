#include <string.h>
#include <stdio.h>

char A[8] = "";
unsigned short B = 1988;

int main() {
    printf("A: %s\n", A);
    printf("B: %d\n", B);
    printf("overflow...\n");
    strcpy(A, "excessive");
    printf("A: %s\n", A);
    printf("B: %d\n", B);
}
