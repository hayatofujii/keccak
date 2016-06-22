#include <stdint.h>

#ifndef KECCAK_H
#define KECCAK_H

#define KECCAK_ROUNDS 24

typedef uint64_t state[25];

void keccak(uint32_t rate, uint32_t cap, uint8_t suffix, uint8_t* in, uint64_t in_size, uint8_t* out, uint64_t out_size);

void keccak_f1600(state A);
void round_b(state A, uint64_t rc);
void theta(state A);
void rho_pi(state A, state B);
void chi(state A, state B);
void iota(state A, uint64_t rc);

void print_state(state s);

#endif /* KECCAK_H */
