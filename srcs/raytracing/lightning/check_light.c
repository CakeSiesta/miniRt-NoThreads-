/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:41:28 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/04 16:55:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_light_intersect_sphere(t_lightning_vectors *l_vectors,
void *object)
{
	t_vector		*temp;

	temp = substract_vectors(*l_vectors->point,
		*(((t_sphere *)object)->center));
	l_vectors->normal = scale_vectors(1 / length_vectors(*temp), *temp);
	free(temp);
}

void	check_light_intersect_plan(t_lightning_vectors *l_vectors,
void *object, t_light *light)
{
	double		k[4];
	t_vector	*temp[3];
	double		denom;
	double		t;

	temp[1] = scale_vectors(-1, *((t_plan *)object)->normal);
	denom = -(dot_vectors(*((t_plan *)object)->normal, *(
(t_plan *)object)->point));
	k[0] = dot_vectors(*light->vector, *((t_plan *)object)->normal) + denom;
	k[1] = dot_vectors(*temp[1], *((t_plan *)object)->normal);
	t = -(k[0] / k[1]);
	temp[2] = scale_vectors(t, *temp[1]);
	free(temp[1]);
	temp[0] = add_vectors(*light->vector, *temp[2]);
	free(temp[2]);
	temp[2] = substract_vectors(*light->vector, *temp[0]);
	l_vectors->normal = scale_vectors(1 / length_vectors(*temp[2]),
*temp[2]);
	free(temp[2]);
	free(temp[0]);
}

void	check_light_triangle(t_lightning_vectors *l_vectors, void *object,
t_light *light)
{
	t_vector	*v[6];
	double		k[4];
	double		t;

	v[1] = substract_vectors(*((t_triangle *)object)->b,
*((t_triangle *)object)->a);
	v[2] = substract_vectors(*((t_triangle *)object)->c,
*((t_triangle *)object)->a);
	v[0] = cross(*v[1], *v[2]);
	v[3] = scale_vectors(-1, *v[0]);
	k[0] = dot_vectors(*light->vector, *v[0]) - (dot_vectors(*v[0],
*((t_triangle *)object)->a));
	k[1] = dot_vectors(*v[3], *v[0]);
	free(v[0]);
	free(v[1]);
	free(v[2]);
	t = -(k[0] / k[1]);
	v[5] = scale_vectors(t, *v[3]);
	free(v[3]);
	v[4] = add_vectors(*light->vector, *v[5]);
	free(v[5]);
	v[5] = substract_vectors(*light->vector, *v[4]);
	l_vectors->normal = scale_vectors(1 / length_vectors(*v[5]), *v[5]);
	free(v[5]);
	free(v[4]);
}

void	check_light_square(t_lightning_vectors *l_vectors, void *object,
t_light *light)
{
	t_vector	*temp2;
	double		k[4];
	t_vector	*point;
	t_vector	*temp;
	double		t;

	temp2 = scale_vectors(-1, *((t_square *)object)->orientation);
	k[0] = dot_vectors(*light->vector, *((t_square *)object)->orientation) -
(dot_vectors(*(
(t_square *)object)->orientation, *((t_square *)object)->center));
	k[1] = dot_vectors(*temp2, *((t_square *)object)->orientation);
	t = -(k[0] / k[1]);
	temp = scale_vectors(t, *temp2);
	point = add_vectors(*light->vector, *temp);
	free(temp);
	temp = substract_vectors(*light->vector, *point);
	l_vectors->normal = scale_vectors(1 / length_vectors(*temp), *temp);
	free(temp);
	free(point);
}
