#include "keccak.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

// https://github.com/gvanas/KeccakCodePackage/blob/master/Standalone/CompactFIPS202/Keccak-readable-and-compact.c
#define ROT64(a, offset) ((((uint64_t)a) << offset) ^ (((uint64_t)a) >> (64 - offset)))

// EXPERIMENTAL: isso ou fazer a LSFR?
// rc[t] = (x^t mod x^8 + x^6 + x^5 + x^4 + 1) mod x in GF(2)[x].
uint64_t keccak_rc[24] = {
    0x0000000000000001, 0x0000000000008082,
    0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088,
    0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B,
    0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080,
    0x0000000080000001, 0x8000000080008008,
};

// (t + 1)(t + 2) / 2
// 0 < t < 24
uint32_t keccak_rotation[5][5] = {
    { 0,  1, 62, 28, 27},
    {36, 44,  6, 55, 20},
    { 3, 10, 43, 25, 39},
    {41, 45, 15, 21,  8},
    {18,  2, 61, 56, 14},

};

void keccak(uint32_t rate, uint32_t cap, uint8_t suffix, uint8_t* in, uint64_t in_size, uint8_t* out, uint64_t out_size)
{
    state s;

    uint32_t rate_bytes = rate / 8;
    uint32_t read_size = 0;
    uint32_t i;

    if ((rate + cap != 1600) || (rate % 8 != 0))
        return;

    memset(s, 0, sizeof(state));

    // absorção
    while (in_size > 0)
    {
        read_size = (in_size < rate_bytes) ? in_size : rate_bytes;

        for (i = 0; i < read_size; i++)
            s[i] ^= in[i];

        // avançar ponteiro de leitura
        in += read_size;
        in_size -= read_size;

        if (read_size == rate_bytes)
        {
            keccak_f1600(s);
            in_size = 0;
        }
    }

    // padding 1
    s[read_size] ^= suffix;

    // se o padding estiver em read - 1, precisamos de novo espaço para a segunda parte
    if (((suffix & 0x80) != 0) && (read_size == rate - 1))
        keccak_f1600(s);

    // padding 2
    s[rate_bytes - 1] ^= 0x80;
    keccak_f1600(s);

    // extração
    while (out_size > 0)
    {
        read_size = (out_size < rate_bytes) ? out_size : rate_bytes;
        memcpy(out, s, read_size);

        // avançar ponteiro de escrita
        out += read_size;
        out_size -= read_size;

        if (out_size > 0)
            keccak_f1600(s);
    }
}

void keccak_f1600(state A)
{
    uint32_t i;

    for (i = 0; i < KECCAK_ROUNDS; i++)
    {
        // printf("Round %d\n", i);
        round_b(A, keccak_rc[i]);
    }
}


void round_b(state A, uint64_t rc)
{
    state B;

    theta(A);
    // printf("Theta:\n");
    // print_state(A);

    rho_pi(A, B);
    // printf("Rho-Pi:\n");
    // print_state(A);

    chi(A, B);
    // printf("Chi:\n");
    // print_state(A);

    iota(A, rc);
    // printf("Iota:\n");
    // print_state(A);
}

void theta(state A)
{
    uint64_t C[5];
    uint64_t D;
    int x, y;

    for (x = 0; x < 5; x++)
        C[x] = A[x + 0 * 5] ^ A[x + 1 * 5] ^ A[x + 2 * 5] ^ A[x + 3 * 5] ^ A[x + 4 * 5];

    for (x = 0; x < 5; x++)
    {
        D = C[(x + 4) % 5] ^ ROT64(C[(x + 1) % 5], 1);

        for (y = 0; y < 5; y++)
            A[x + y * 5] ^= D;
    }
}

void rho_pi(state A, state B)
{
    int x, y;

    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
            B[y + ((2 * x + 3 * y) % 5) * 5] = ROT64(A[x + y * 5], keccak_rotation[y][x]);
}

void chi(state A, state B)
{
    int x, y;

    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
           A[x + y * 5] = B[x + y * 5] ^ (~B[((x + 1) % 5) + y * 5] & B[((x + 2) % 5) + y * 5]);

}

void iota(state A, uint64_t RC)
{
    A[0] ^= RC;
}

void print_state(state s)
{
    int i;

    for (i = 0; i < 25; i++)
    {
        if (i % 5 == 0 && i != 0) printf("\n");
        printf("%0" PRIX64 " ", s[i]);
    }

    printf("\n\n");
}
