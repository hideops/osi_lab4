#include <stdio.h>
#include "contracts.h"

float sin_integral(float a, float b, float e);
int prime_count(int a, int b);

int main() {
    int cmd;
    while (scanf("%d", &cmd) == 1) {
        if (cmd == 1) {
            float a, b, e;
            scanf("%f %f %f", &a, &b, &e);
            printf("%f\n", sin_integral(a, b, e));
        } else if (cmd == 2) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", prime_count(a, b));
        }
    }
    return 0;
}