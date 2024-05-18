#pragma once
#include <stdio.h>
#include <string.h>
#include "array.h"
#include "mesh.h"
#define _CRT_SECURE_NO_WARNINGS

#define MAX_NUMBER_MESHES 10
static mesh_t meshes[MAX_NUMBER_MESHES];
static int mesh_count = 0;

void load_mesh(char* obj_filename, char* png_filename, vect3_t scale, vect3_t translation, vect3_t rotation) {
	load_mesh_obj_data(&meshes[mesh_count], obj_filename);
	load_mesh_png_data(&meshes[mesh_count], png_filename);

	meshes[mesh_count].scale = scale;
	meshes[mesh_count].translation = translation;
	meshes[mesh_count].rotation = rotation;

	mesh_count++;
}

void load_mesh_obj_data(mesh_t* mesh, char* obj_filename) {
	FILE* file = NULL;
	fopen_s(&file, obj_filename, "r");
	char line[1024];

	text2_t* texcoords = NULL;
	if (file != NULL)
		while (fgets(line, 1024, file)) {
			// Vertex information
			if (strncmp(line, "v ", 2) == 0) {
				vect3_t vertex;
				sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				array_push(mesh->vertices, vertex);
			}
			// Texture coordinate information
			if (strncmp(line, "vt ", 3) == 0) {
				text2_t texcoord;
				sscanf_s(line, "vt %f %f", &texcoord.u, &texcoord.v);
				if (&texcoord != NULL)
					array_push(texcoords, texcoord);
			}
			// Face information
			if (strncmp(line, "f ", 2) == 0) {
				int vertex_indices[3];
				int texture_indices[3];
				int normal_indices[3];
				sscanf_s(
					line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&vertex_indices[0], &texture_indices[0], &normal_indices[0],
					&vertex_indices[1], &texture_indices[1], &normal_indices[1],
					&vertex_indices[2], &texture_indices[2], &normal_indices[2]
				);
				if (texcoords != NULL) {
					face_t face = {
						.a = vertex_indices[0],
						.b = vertex_indices[1],
						.c = vertex_indices[2],
						.a_uv = texcoords[texture_indices[0] - 1],
						.b_uv = texcoords[texture_indices[1] - 1],
						.c_uv = texcoords[texture_indices[2] - 1],
						.color = 0xFFFFFFFF
					};
					array_push(mesh->faces, face);
				}
			}
		}
}

void load_mesh_png_data(mesh_t* mesh, char* png_filename) {
	upng_t* png_image = upng_new_from_file(png_filename);
	if (png_image != NULL) {
		upng_decode(png_image);
		if (upng_get_error(png_image) == UPNG_EOK) {
			mesh->texture = png_image;
		}
	}
}

int get_num_meshes(void) {
	return mesh_count;
}

mesh_t* get_mesh(int index)
{
	return &meshes[index];
}

void free_meshes(void)
{
	for (int i = 0; i < mesh_count; i++)
	{
		upng_free(meshes[i].texture);
		array_free(meshes[i].faces);
		array_free(meshes[i].vertices);
	}

}
