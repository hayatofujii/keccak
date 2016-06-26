#include "keyak.h"
#include "keccak.h"

// EXPERIMENTAL: isso ou fazer a LSFR?
// rc[t] = (x^t mod x^8 + x^6 + x^5 + x^4 + 1) mod x in GF(2)[x].
extern uint64_t keccak_rc[24];

// targeting b = 1600, so l = 8
// nr = 12, cap = 256, tau = 128
void keccak_p1600(state A, uint32_t nr)
{
    uint32_t ir;

    for (ir = 12 + 2 * 8 - nr; ir < 12 + 2 * 8 - 1; ir++)
        round_b(A, keccak_rc[ir]);
}
