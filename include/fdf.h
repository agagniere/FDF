#pragma once

#define SET_FLOAT_PRECISION(T)                   \
	typedef T t_real;                            \
	typedef s_point2_##T t_point2_real;          \
	typedef s_point3_##T t_point3_real

SET_FLOAT_PRECISION(float);

struct window
{
	void*       mlx_win;
	void*       mlx_img;
	uint8_t*    pixels;
	int         bits_per_pixel;
	int         line_size;
	int         endian;
	t_dimension dim;
};

struct env
{
	void*   mlx;
	t_array windows;
};
