#include <stdint.h>

#ifndef KECCAK_H
#define KECCAK_H

uint32_t keccak_rc[KECCAK_ROUNDS] = {
    0x00000001,
    0x00008082,
    0x0000808a,
    0x80008000,
    0x0000808b,
    0x80000001,
    0x80008081,
    0x00008009,
    0x0000008a,
    0x00000088,
    0x80008009,
    0x8000000a,
    0x8000808b,
    0x0000008b,
    0x00008089,
    0x00008003,
    0x00008002,
    0x00000080,
    0x0000800a,
    0x8000000a,
    0x80008081,
    0x00008080
};

typedef state uint64_t[5][5];

state keccak-f-b(state A);
void round-b(state A);
void theta(state A);
void rho-pi(state A, state B);
void chi(state A, state B);
void iota(state A);


#endif /* KECCAK_H */
