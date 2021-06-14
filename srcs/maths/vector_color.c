/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 06:45:02 by lmartin           #+#    #+#             */
/*   Updated: 2021/06/14 09:22:58 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*color_to_rgb(unsigned int color)
{
	int	red;
	int	green;
	int	blue;

	blue = (int)(color % 256);
	green = (int)(((color - blue) / 256) % 256);
	red = (int)(((color - blue) / (256 * 256)) - green / 256);
	return (new_vector((double)red, (double)green, (double)blue));
}

int	rgb_to_color(t_vector *rgb)
{
	int	color;

	color = (int)(((int)rgb->x));
	color = (int)((color << 8) + (int)rgb->y);
	color = (int)((color << 8) + (int)rgb->z);
	return (color);
}

void	rearrange_rgb(t_vector *color)
{
	if (color->x > 255)
		color->x = 255;
	else if (color->x < 0)
		color->x = 0;
	if (color->y > 255)
		color->y = 255;
	else if (color->y < 0)
		color->y = 0;
	if (color->z > 255)
		color->z = 255;
	else if (color->z < 0)
		color->z = 0;
}
