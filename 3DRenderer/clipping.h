#pragma once
#ifndef CLIPPING_H
#define CLIPPING_H
#define MAX_NUM_VERTICES 10
#define MAX_NUM_POLY_TRIANGLES 10
#include "vector.h"
#include "Triangle.h"
enum {
	LEFT_FRUSTUM_PLANE,
	RIGHT_FRUSTUM_PLANE,
	TOP_FRUSTUM_PLANE,
	BOTTOM_FRUSTUM_PLANE,
	NEAR_FRUSTUM_PLANE,
	FAR_FRUSTUM_PLANE
};

typedef struct {
	vect3_t point;
	vect3_t normal;
} plane_t;


typedef struct {
	vect3_t vertices[MAX_NUM_VERTICES];
	text2_t texcoords[MAX_NUM_VERTICES];
	int num_vertices;
} polygon_t;

void init_frustum_planes(float fovx,float fovy, float z_near, float z_far);
void clip_polygon(polygon_t* polygon);
void clip_polygon_against_plane(polygon_t* polygon, int plane);
polygon_t create_polygon_from_triangle(vect3_t v0, vect3_t v1, vect3_t v2,text2_t t0,text2_t t1, text2_t t2);
void triangles_from_polygon(polygon_t* p, triangle_t triangles[], int* numberTriangles);
#endif

