#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x;
	float y;

} vec2_t;


typedef struct {
	float x;
	float y;
	float z;
} vect3_t;

typedef struct {
	float x, y, z, w;
} vec4_t;

/// <summary>
/// Vector 2D functions
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
vec2_t vec2_new(float x, float y);
float vect2_length(vec2_t v); 
vec2_t vect2_add(vec2_t a, vec2_t b);
vec2_t vect2_subtract(vec2_t a, vec2_t b);
vec2_t vect2_mult(vec2_t v, float factor);
vec2_t vect2_dev(vec2_t v, float factor);
void vec2_normalize(vec2_t* v);
/// <summary>
/// Vector 3D functions
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
vect3_t vec3_new(float x, float y,float z);
float vect3_length(vect3_t v);
vect3_t vect3_add(vect3_t a, vect3_t b);
vect3_t vect3_subtract(vect3_t a, vect3_t b);
vect3_t vect3_mult(vect3_t v, float factor);
vect3_t vect3_dev(vect3_t v, float factor);
vect3_t vec3_cross(vect3_t a, vect3_t b);
float vec3_dot(vect3_t a, vect3_t b);
void vec3_normalize(vect3_t* v);
vect3_t vec3_clone(vect3_t* v);

vect3_t vec3_rotate_x(vect3_t v, float angle);
vect3_t vec3_rotate_y(vect3_t v, float angle);
vect3_t vec3_rotate_z(vect3_t v, float angle);

////////////////////////////////////////////////////////////////////////////////
// Vector conversion functions
////////////////////////////////////////////////////////////////////////////////
vec4_t vec4_from_vec3(vect3_t v);
vect3_t vec3_from_vec4(vec4_t v);
vec2_t vec2_from_vec4(vec4_t v);

#endif // !VECTOR_H
