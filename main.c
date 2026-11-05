#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sodium/core.h>

int main(void) {
    // INIT
    // - init CSPRNG
    if (sodium_init() < 0) {
        return 1;
    }
    // - init srand
    srand((unsigned int)time(NULL));



    printf("Hello, World!\n");
    return 0;
}
