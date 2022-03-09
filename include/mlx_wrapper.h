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

#define NO_HOOKS                                                    \
    (struct hooks)                                                  \
    {                                                               \
        .expose      = NULL,                                        \
        .repaint     = NULL,                                        \
        .key_press   = NULL,                                        \
        .key_release = NULL,                                        \
        .mouse_click = NULL,                                        \
        .mouse_move  = NULL,                                        \
        .mouse_drag  = NULL                                         \
    }

#define NEW_WINDOW                                                  \
    (struct window)                                                 \
    {                                                               \
        .hooks         = NO_HOOKS,                                  \
        .mlx_ptr       = NULL,                                      \
        .mlx_win       = NULL,                                      \
        .mlx_img       = NULL,                                      \
        .pixels        = NULL,                                      \
        .dim           = {0, 0},                                    \
        .bit_per_pixel = 0,                                         \
        .line_size     = 0,                                         \
        .endian        = 0                                          \
    }

bool make_window(t_window* out_win, void* mlx, t_dimension dim, const char* name, t_hooks hooks);
void free_window(t_window* win);

void draw_line(t_window* win, t_point2_int from, t_point2_int to, int color);
void set_pixel(t_window* win, unsigned x, unsigned y, int color);

bool is_in_frame(t_window* win, unsigned x, unsigned y);
