#include "colors.h"
#include "fdf.h"

#include <ft_prepro.h>

t_color_hsl hsl_from_rgb(t_color_rgb rgb)
{
	const unsigned min    = MIN(rgb.red, rgb.green, rgb.blue);
	const unsigned max    = MAX(rgb.red, rgb.green, rgb.blue);
	const float    chroma = max - min;
	t_color_hsl    hsl    = {0, 0, (min + chroma / 2.) / 255.};

	if (chroma > 0)
	{
		hsl.saturation = (hsl.lightness > 0.5 ? chroma / (510. - max - min) : chroma / (max + min));

		if (max == rgb.red)
			hsl.hue = (rgb.green - rgb.blue) / chroma + (rgb.green < rgb.blue ? 6. : 0.);
		else if (max == rgb.green)
			hsl.hue = (rgb.blue - rgb.red) / chroma + 2.;
		else
			hsl.hue = (rgb.red - rgb.green) / chroma + 4.;
		hsl.hue /= 6.;
	}
	return hsl;
}
