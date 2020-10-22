/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherrald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:18:10 by jherrald          #+#    #+#             */
/*   Updated: 2020/10/16 17:18:12 by jherrald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "canvas.h"

t_canvas		*new_canvas(double width, double heigth, double distance)
{
	t_canvas	*canvas;

	if (!(canvas = malloc(sizeof(t_canvas))))
		print_error_and_exit(-7);
	canvas->width = width;
	canvas->height = heigth;
	canvas->distance = distance;
	return (canvas);
}
