#include "keccak.h"

#ifndef KEYAK_H
#define KEYAK_H

void keccak_p1600(state A, uint32_t nr);

void keyak(uint64_t b, uint32_t nr, uint8_t pi, uint8_t c, uint8_t tau);

#endif /* KEYAK_H */
