#include <math.h>
#include "vector.h"

#pragma region Vector functions implenetation
vec2_t vec2_new(float x, float y)
{
	vec2_t result = { x,y };
	return result;
}
float vect2_length(vec2_t v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t vect2_add(vec2_t a, vec2_t b)
{
	vec2_t result = {
	.x = a.x + b.x,
	.y = a.y + b.y
	};
	return result;
}

vec2_t vect2_subtract(vec2_t a, vec2_t b)
{
	vec2_t result = {
	.x = a.x - b.x,
	.y = a.y - b.y
	};
	return result;
}

vec2_t vect2_mult(vec2_t v, float factor)
{
	vec2_t result = {
.x = v.x * factor,
.y = v.y * factor
	};
	return result;
}

vec2_t vect2_dev(vec2_t v, float factor)
{
	vec2_t result = {
	.x = v.x / factor,
	.y = v.y / factor
	};
	return result;
}

void vec2_normalize(vec2_t* v) {
	float length = sqrt(v->x * v->x + v->y * v->y);
	v->x /= length;
	v->y /= length;
}


vect3_t vec3_new(float x, float y, float z)
{
	vect3_t result = { x,y,z };
	return result;
}

float vect3_length(vect3_t v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
vect3_t vect3_add(vect3_t a, vect3_t b)
{
	vect3_t result = {
	.x = a.x + b.x,
	.y = a.y + b.y,
	.z = a.z + b.z
	};
	return result;
}
vect3_t vect3_subtract(vect3_t a, vect3_t b)
{
	vect3_t result = {
.x = a.x - b.x,
.y = a.y - b.y,
.z = a.z - b.z
	};
	return result;
}
vect3_t vect3_mult(vect3_t v, float factor)
{
	vect3_t result = {
	.x = v.x * factor,
	.y = v.y * factor,
	.z = v.z * factor
	};
	return result;
}
vect3_t vect3_dev(vect3_t v, float factor)
{
	vect3_t result = {
	.x = v.x / factor,
	.y = v.y / factor,
	.z = v.z / factor
	};
	return result;
}
#pragma endregion


vect3_t vec3_rotate_x(vect3_t v, float angle)
{
	vect3_t rotated_vector = {
	.x = v.x,
	.y = v.y * cos(angle) - v.z * sin(angle),
	.z = v.y * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}

vect3_t vec3_rotate_y(vect3_t v, float angle)
{
	vect3_t rotated_vector = {
	.x = v.x * cos(angle) - v.z * sin(angle),
	.y = v.y ,
	.z = v.x * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}

vect3_t vec3_rotate_z(vect3_t v, float angle)
{
	vect3_t rotated_vector = {
	.x = v.x * cos(angle) - v.y * sin(angle),
	.y = v.x * sin(angle) + v.y * cos(angle) ,
	.z = v.z
	};
	return rotated_vector;
}

vect3_t vec3_cross(vect3_t a, vect3_t b) {
	vect3_t result = {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
	return result;
}

float vec3_dot(vect3_t a, vect3_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vec3_normalize(vect3_t* v) {
	float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

vect3_t vec3_clone(vect3_t* v)
{
	vect3_t result = { v->x,v->y,v->z };
	return result;
}

///////////////////////////////////////////////////////////////////////////////
// Implementations of Vector conversion functions
///////////////////////////////////////////////////////////////////////////////
vec4_t vec4_from_vec3(vect3_t v) {
	vec4_t result = { v.x, v.y, v.z, 1.0 };
	return result;
}

vect3_t vec3_from_vec4(vec4_t v) {
	vect3_t result = { v.x, v.y, v.z };
	return result;
}

vec2_t vec2_from_vec4(vec4_t v)
{
	vec2_t result = { v.x,v.y };

	return result;
}
