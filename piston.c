#include "piston.h"

#include <stdint.h>

void piston_init(uint32_t squeeze_rate, uint32_t absorb_rate)
{
    piston_squeeze_rate = squeeze_rate;
    piston_absorb_rate = absorb_rate;
}
