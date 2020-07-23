#pragma once

#include <stdint.h>

typedef union color_rgb     t_color_rgb;
typedef struct color_hsl    t_color_hsl;

union color_rgb
{
	struct
	{
		uint8_t blue;
		uint8_t green;
		uint8_t red;
		uint8_t transparency;
	};
	uint8_t  components[4];
	uint32_t color;
};

struct color_hsl
{
	float hue;
	float saturation;
	float lightness;
};

#define RGB(R,G,B) (t_color_rgb){{B,G,R,0}}

t_color_hsl hsl_from_rgb(t_color_rgb rgb);
