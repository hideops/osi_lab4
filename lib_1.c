#include <math.h>
#include "contracts.h"

float sin_integral(float a, float b, float e) {
    float sum = 0.0f;
    for (float x = a; x < b; x += e)
        sum += sinf(x) * e;
    return sum;
}

int prime_count(int a, int b) {
    int count = 0;
    for (int i = a; i <= b; i++) {
        if (i < 2) continue;
        int is_prime = 1;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) count++;
    }
    return count;
}