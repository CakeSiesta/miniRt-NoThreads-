/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 07:11:17 by lmartin           #+#    #+#             */
/*   Updated: 2020/10/19 16:59:09 by jherrald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "sphere.h"

t_sphere		*new_sphere(double radius, t_vector *color, double shiny,
t_vector *center)
{
	t_sphere	*sphere;

	if (!(sphere = malloc(sizeof(t_sphere))))
		print_error_and_exit(-7);
	sphere->radius = radius;
	sphere->color = color;
	sphere->center = center;
	sphere->shiny = shiny;
	sphere->var_c = 0;
	sphere->difference = NULL;
	sphere->prev_origin = NULL;
	return (sphere);
}

void			free_sphere(t_sphere *sphere)
{
	free(sphere->center);
	free(sphere->color);
	if (sphere->difference)
		free(sphere->difference);
	if (sphere->prev_origin)
		free(sphere->prev_origin);
	free(sphere);
}

t_sphere		*cpy_sphere(t_sphere *sphere)
{
	t_sphere	*new;

	if (!(new = malloc(sizeof(t_sphere))))
		print_error_and_exit(-7);
	new->center = cpy_vector(sphere->center);
	new->color = cpy_vector(sphere->color);
	new->radius = sphere->radius;
	new->shiny = sphere->shiny;
	new->var_c = 0;
	new->difference = NULL;
	new->prev_origin = NULL;
	return (new);
}
