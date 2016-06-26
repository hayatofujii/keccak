#include <stdint.h>

#ifndef ENGINE_H
#define ENGINE_H

typedef enum
{
    engine_fresh = 0,
    engine_encrypt,
    engine_end_of_crypt,
    engine_eom,
} engine_state;

void engine_init();
void _engine_spark();
void engine_crypt();
void engine_inject(uint32_t* in, uint32_t in_size);
void engine_get_tags(uint32_t* out, uint32_t out_size);

void engine_inject_collective(uint32_t* in, uint32_t in_size, uint8_t diverse_flag);


#endif /* PISTON_H */
