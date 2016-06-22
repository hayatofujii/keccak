#include "keccak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    unsigned char test_vector[] = "";
    unsigned char output[64];

    memset(output, 0, sizeof(output));

    // sha3 512
    keccak(576, 1024, 0x06, test_vector, sizeof(test_vector) - 1, output, sizeof(output));

    size_t i;
    for (i = 0; i < sizeof(output) * sizeof(char); i++)
        printf("%02x", output[i]);

    printf("\n");

    return 0;
}
