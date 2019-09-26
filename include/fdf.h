#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <ft_array.h>
#include "point.h"

#define SET_FLOAT_PRECISION(T)                   \
	typedef T t_real;                            \
	typedef s_point2_##T t_point2_real;          \
	typedef s_point3_##T t_point3_real

SET_FLOAT_PRECISION(float);

typedef struct env    s_env;
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
	void*       mlx_win;
	void*       mlx_img;
	uint8_t*    pixels;
	int         bit_per_pixel;
	int         line_size;
	int         endian;
	t_dimension dim;
	s_hooks     hooks;
};

struct env
{
	void*   mlx;
	t_array windows;
	t_array points;
};

t_array parse_fdf(const char* filename);
bool    add_window(s_env* env, t_dimension dim, const char* name);
void    free_window(s_window* win, void* mlx);
