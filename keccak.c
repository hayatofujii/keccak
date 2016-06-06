#include <stdint.h>

// https://github.com/gvanas/KeccakCodePackage/blob/master/Standalone/CompactFIPS202/Keccak-readable-and-compact.c
#define ROT(a, offset) ((((UINT64)a) << offset) ^ (((UINT64)a) >> (64-offset))
#define i(x, y) ((x)+5*(y))

// isso ou fazer a LSFR?
// rc[t] = (x^t mod x^8 + x^6 + x^5 +x^4 + 1) mod x in GF(2)[x].
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

state keccak_f(state A)
{
    int i;

    for (i = 0; i < rounds; i++)
        A = round(A, keccak_rc[i]);
	return A;
}


void round_b(state A, int r)
{
    state B;

    for (r = 0; r < KECCAK_ROUNDS; r++)
    {
        theta(A);
        rho_pi(A, B);
        chi(A, B);
        iota(A, keccak_rc[r]);
    }
}

void theta(state A)
{
    state C, D;

    int x, y;
    int i;

    for (x = 0; x < 5; x++)
        for (i = 0; i < 5; i++)
            C[x] ^= A[x, i];

    for (x = 0; x < 5; x++)
        D[x] = C[x - 1] ^ ROT(C[x + 1], 1);

    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
            A[x, y] ^= D[x];

    return A;
}

void rho_pi(state A, state B)
{
    int x, y;

    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
            B[y, 2 * x + 3 * y] = ROT(A[x, y], r[x, y]);

}

void chi(state A, state B)
{
    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
           A[x, y] = B[x, y] ^ (~B[x + 1, y] & B[x + 2, y]);

}

void iota(state A, int RC)
{
    A[0, 0] = A[0, 0] ^ RC;
}
