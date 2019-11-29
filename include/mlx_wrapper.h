#pragma once

#include "point.h"

#include <ft_array.h>

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

enum e_key
{
	KEY_A = 0x61,
	KEY_B /* = 0x62 */,
	KEY_C /* = 0x63 */,
	KEY_D /* = 0x64 */,
	KEY_E /* = 0x65 */,
	KEY_F /* = 0x66 */,
	KEY_G /* = 0x67 */,
	KEY_H /* = 0x68 */,
	KEY_I /* = 0x69 */,
	KEY_J /* = 0x6a */,
	KEY_K /* = 0x6b */,
	KEY_L /* = 0x6c */,
	KEY_M /* = 0x6d */,
	KEY_N /* = 0x6e */,
	KEY_O /* = 0x6f */,
	KEY_P /* = 0x70 */,
	KEY_Q /* = 0x71 */,
	KEY_R /* = 0x72 */,
	KEY_S /* = 0x73 */,
	KEY_T /* = 0x74 */,
	KEY_U /* = 0x75 */,
	KEY_V /* = 0x76 */,
	KEY_W /* = 0x77 */,
	KEY_X /* = 0x78 */,
	KEY_Y /* = 0x79 */,
	KEY_Z /* = 0x7a */,
	KEY_LEFT = 0xff51,
	KEY_UP /* = 0xff52 */,
	KEY_RIGHT /* = 0xff53 */,
	KEY_DOWN /* = 0xff54 */,
	KEY_PGDOWN /* = 0xff55 */,
	KEY_PGUP /* = 0xff56 */,
	KEY_ESC = 0xff1b,
	KEY_KP_PLUS = 0xffab,
	KEY_KP_MINUS = 0xffad,
};

#define NO_HOOKS (s_hooks){NULL, NULL, NULL, NULL, NULL, NULL, NULL}

bool make_window(void* mlx, t_dimension dim, const char* name, s_hooks hooks,
				 s_window* dest);
void free_window(s_window* win);
