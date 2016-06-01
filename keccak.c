#include <stdint.h>
#inlcude 

#define ROT (???, x)

state keccak-f(state A)
{
    int i;

    for (i = 0; i < rounds; i++)
        A = round(A, keccak_rc[i]);
	return A;
}


void round(state A, int r)
{
    state B;

    for (r = 0; r < KECCAK_ROUNDS; r++)
    {
        theta(A);
        rho-pi(A, B);
        chi(A, B);
        iota(A, r);
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

void rho-pi(state A, state B)
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

