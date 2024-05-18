#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include "vector.h"
#include <stdint.h>

typedef struct {
	vect3_t direction;
} light_t;

uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor);

void init_light(vect3_t direction);
vect3_t get_light_direction();
#endif // !LIGHT_H