#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "contracts.h"

static sin_integral_func *sin_integral = NULL;
static prime_count_func *prime_count = NULL;

static float stub_sin(float a, float b, float e) {
    (void)a; (void)b; (void)e;
    return 0.0f;
}

static int stub_prime(int a, int b) {
    (void)a; (void)b;
    return 0;
}

void load_library(const char *path, void **lib) {
    if (*lib) {
        dlclose(*lib);
        *lib = NULL;
    }

    *lib = dlopen(path, RTLD_LAZY);
    if (*lib == NULL) {
        write(STDERR_FILENO, "warning: failed to load library\n", 32);
        sin_integral = stub_sin;
        prime_count = stub_prime;
        return;
    }

    sin_integral = (sin_integral_func*)dlsym(*lib, "sin_integral");
    if (!sin_integral) {
        sin_integral = stub_sin;
        write(STDERR_FILENO, "warning: sin_integral not found\n", 32);
    }

    prime_count = (prime_count_func*)dlsym(*lib, "prime_count");
    if (!prime_count) {
        prime_count = stub_prime;
        write(STDERR_FILENO, "warning: prime_count not found\n", 31);
    }
}

int main() {
    void *lib = NULL;
    int toggle = 0;

    load_library("./lib_1.so", &lib);

    int cmd;
    while (scanf("%d", &cmd) == 1) {
        if (cmd == 0) {
            toggle = !toggle;
            load_library(toggle ? "./lib_2.so" : "./lib_1.so", &lib);
        } else if (cmd == 1) {
            float a, b, e;
            scanf("%f %f %f", &a, &b, &e);
            printf("%f\n", sin_integral(a, b, e));
        } else if (cmd == 2) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", prime_count(a, b));
        } else {
            printf("Invalid command\n");
        }
    }

    if (lib) {
        dlclose(lib);
    }
    return 0;
}