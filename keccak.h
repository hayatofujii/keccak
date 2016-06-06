#include <stdint.h>

#ifndef KECCAK_H
#define KECCAK_H

typedef state uint64_t[5][5];

state keccak_f_b(state A);
void round_b(state A);
void theta(state A);
void rho_pi(state A, state B);
void chi(state A, state B);
void iota(state A);

#endif /* KECCAK_H */
