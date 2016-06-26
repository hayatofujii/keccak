#include <stdint.h>

#ifndef PISTON_H
#define PISTON_H

uint32_t piston_squeeze_rate;
uint32_t piston_absorb_rate;

void piston_init(uint32_t squeeze_rate, uint32_t absorb_rate);

void piston_crypt();
void piston_inject(uint32_t* in);
void piston_spark();
void piston_get_tag(uint32_t* out, uint32_t out_size);

#endif /* PISTON_H */
