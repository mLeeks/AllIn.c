#include <stdio.h>
#include <sodium/core.h>

int main(void) {
    // INIT
    // - init CSPRNG
    if (sodium_init() < 0) {
        return 1;
    }


    printf("Hello, World!\n");
    return 0;
}
