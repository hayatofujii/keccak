#include "keccak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
#if 0
    uint8_t test_vector[] = "";
    uint8_t output[64];

    memset(output, 0, sizeof(output));
    // sha3 512
    keccak(576, 1024, 0x06, test_vector, sizeof(test_vector) * sizeof(uint8_t) - 1, output, sizeof(output) * sizeof(uint8_t));

    size_t i;
    for (i = 0; i < (sizeof(output) * sizeof(uint8_t)); i++)
        printf("%02x", output[i]);
    printf("\n");
#endif

    return 0;
}
