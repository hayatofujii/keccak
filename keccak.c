#include "keccak.h"
#include <stdint.h>

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
    {25, 39,  3, 10, 43},
    {55, 20, 36, 44, 6 },
    {28, 27,  0,  1, 62},
    {56, 14, 18,  2, 61},
    {21, 8 , 41, 45, 15}
};


void keccak_f(state A)
{
    int i;

    for (i = 0; i < KECCAK_ROUNDS; i++)
        round_b(A, keccak_rc[i]);
}


void round_b(state A, int r)
{
    state B;

    theta(A);
    rho_pi(A, B);
    chi(A, B);
    iota(A, keccak_rc[r]);
}

void theta(state A)
{
    uint64_t C[5];
    uint64_t D;
    int x, y;

    for (x = 0; x < 5; x++)
        C[x] = A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4];

    for (x = 0; x < 5; x++)
    {
        D = C[(x + 4) % 5] ^ ROT64(C[(x + 1) % 5], 1);

        for (y = 0; y < 5; y++)
            A[x][y] ^= D;
    }
}

void rho_pi(state A, state B)
{
    int x, y;

    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
            B[y][(2 * x + 3 * y) % 5] = ROT64(A[x][y], keccak_rotation[x][y]);
}

void chi(state A, state B)
{
    int x, y;

    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
           A[x][y] = B[x][y] ^ (~B[(x + 1) % 5][y] & B[(x + 2) % 5][y]);

}

void iota(state A, int RC)
{
    A[0][0] = A[0][0] ^ RC;
}
