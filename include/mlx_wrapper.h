#pragma once

#include "point.h"

#include <ft_array.h>
#include <libft.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct window t_window;
typedef struct hooks  t_hooks;

typedef int (*t_fnct)();

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
	t_hooks     hooks;
	void*       mlx_ptr;
	void*       mlx_win;
	void*       mlx_img;
	uint8_t*    pixels;
	t_dimension dim;
	int         bit_per_pixel;
	int         line_size;
	int         endian;
};

#define NO_HOOKS (t_hooks){NULL, NULL, NULL, NULL, NULL, NULL, NULL}
#define NEW_WINDOW (t_window){NO_HOOKS, NULL, NULL, NULL, NULL, {0,0}, 0, 0, 0}

bool make_window(t_window* out_win, void* mlx, t_dimension dim, const char* name, t_hooks hooks);
void free_window(t_window* win);

void draw_line(t_window* win, t_point2_int from, t_point2_int to, int color);
void set_pixel(t_window* win, unsigned x, unsigned y, int color);

bool is_in_frame(t_window* win, unsigned x, unsigned y);
