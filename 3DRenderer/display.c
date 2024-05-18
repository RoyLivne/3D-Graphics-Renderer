#include "display.h"


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static uint32_t* color_buffer = NULL;
static float* z_buffer = NULL;

static SDL_Texture* color_buffer_texture = NULL;
static int window_width = 800;
static int window_height = 600;

static int render_method = 0;
static int cull_method = 0;
int get_window_width(void) {
	return window_width;
}

int get_window_height(void) {
	return window_height;
}

void set_render_method(int method)
{
	render_method = method;
}

void set_cull_method(int method)
{
	cull_method = method;
}

bool is_cull_backface(void)
{
	return cull_method == CULL_BACKFACE;
}

bool should_render_filled_triangles(void)
{
	return (render_method == RENDER_FILL_TRIANGLE ||
		render_method == RENDER_FILL_TRIANGLE_WIRE);
}

bool should_render_textured_triangle(void)
{
	return (render_method == RENDER_TEXTURED ||
		render_method == RENDER_TEXTURED_WIRED);
}

bool should_render_wireframe(void)
{
	return (render_method == RENDER_WIRE ||
		render_method == RENDER_WIRE_VERTEX ||
		render_method == RENDER_FILL_TRIANGLE_WIRE ||
		render_method == RENDER_TEXTURED_WIRED);
}

bool should_draw_vertex_points(void)
{
	return render_method == RENDER_WIRE_VERTEX;
}

void draw_grid(void) {
	for (int y = 0; y < window_height; y += 10) {
		for (int x = 0; x < window_width; x += 10) {
			color_buffer[(window_width * y) + x] = 0xFF444444;
		}
	}
}

void draw_pixel(int x, int y, uint32_t color) {
	if (x < 0 || x >= window_width || y < 0 || y >= window_height) {
		return;
	}
	color_buffer[(window_width * y) + x] = color;
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)longest_side_length;
	float y_inc = delta_y / (float)longest_side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i <= longest_side_length; i++) {
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			draw_pixel(current_x, current_y, color);
		}
	}
}

void render_color_buffer(void) {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void clear_color_buffer(uint32_t color) {
	for (int y = 0; y < window_width * window_height; y++) {
		color_buffer[y] = color;
	}
}

void clear_z_buffer(void) {
	for (int y = 0; y < window_width * window_height; y++) {
		z_buffer[y] = 1.0;
	}

}

void destroy_window(void) {
	free(color_buffer);
	free(z_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

float get_zbuffer_at(int x, int y)
{
	if (x < 0 || x >= window_width || y < 0 || y >= window_height) {
		return;
	}
	return z_buffer[(window_width * y) + x];
}

void update_zbuffer_at(int x, int y, float value)
{
	if (x < 0 || x >= window_width || y < 0 || y >= window_height) {
		return;
	}
	z_buffer[(window_width * y) + x] = value;
}

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

		return false;

	}

	//use sdl to query what is the fullscreen max. width and height
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;


	window = SDL_CreateWindow(NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS);

	if (!window) {

		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{

		return false;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	// Allocate the required memory in bytes to hold the color buffer and the z-buffer
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
	z_buffer = (float*)malloc(sizeof(float) * window_width * window_height);

	// Creating a SDL texture that is used to display the color buffer
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);

	return true;
}

