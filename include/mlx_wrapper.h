#pragma once

#include "point.h"

#include <ft_array.h>
#include <libft.h>

#include <stdint.h>
#include <stdbool.h>

typedef struct window s_window;
typedef struct hooks  s_hooks;

typedef int           (*t_fnct)();

struct hooks
{
	t_fnct expose;
	t_fnct repaint;
	t_fnct key_press;
	t_fnct key_release;
	t_fnct mouse_click;
	t_fnct mouse_move;
	t_fnct mouse_drag;
};

struct window
{
	s_hooks     hooks;
	void*       mlx_ptr;
	void*       mlx_win;
	void*       mlx_img;
	uint8_t*    pixels;
	t_dimension dim;
	int         bit_per_pixel;
	int         line_size;
	int         endian;
};

#define NO_HOOKS (s_hooks){NULL, NULL, NULL, NULL, NULL, NULL, NULL}
#define NEW_WINDOW (s_window){NO_HOOKS, NULL, NULL, NULL, NULL, {0,0}, 0, 0, 0}

bool make_window(s_window* out_win, void* mlx, t_dimension dim, const char* name, s_hooks hooks);
void free_window(s_window* win);

void draw_line(s_window* win, s_point2_int from, s_point2_int to, int color);
void set_pixel(s_window* win, unsigned x, unsigned y, int color);
