#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "contracts.h"

float sin_integral(float a, float b, float e) {
    float sum = 0.0f;
    for (float x = a; x < b; x += e)
        sum += (sinf(x) + sinf(x + e)) * 0.5f * e;
    return sum;
}

int prime_count(int a, int b) {
    if (b < 2) return 0;
    if (a < 2) a = 2;
    
    int size = b + 1;
    char *is_prime = (char*)malloc(size * sizeof(char));
    if (!is_prime) return -1;
    
    memset(is_prime, 1, size);
    is_prime[0] = is_prime[1] = 0;
    
    for (int i = 2; i * i <= b; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= b; j += i) {
                is_prime[j] = 0;
            }
        }
    }   
    
    int count = 0;
    for (int i = a; i <= b; i++) {
        if (is_prime[i]) count++;
    }
    
    free(is_prime);
    return count;
}