#include <stdint.h>

#ifndef KECCAK_H
#define KECCAK_H

#define KECCAK_ROUNDS 24

typedef uint64_t state[5][5];

void keccak_f_b(state A);
void round_b(state A, int r);
void theta(state A);
void rho_pi(state A, state B);
void chi(state A, state B);
void iota(state A, int rc);

#endif /* KECCAK_H */
