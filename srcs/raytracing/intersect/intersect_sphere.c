/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:02:59 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:28:12 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		intersect_sphere(t_vector origin,
t_vector direction, t_sphere *object)
{
	double		discriminant;
	double		k[2];
	double		t[2];

	if (!object->prev_origin || !is_equal(object->prev_origin, &origin))
	{
		if (object->difference)
			free(object->difference);
		if (object->prev_origin)
			free(object->prev_origin);
		object->difference = substract_vectors(origin, *object->center);
		object->var_c = dot_vectors(*object->difference,
*object->difference) - (object->radius * object->radius);
		object->prev_origin = cpy_vector(&origin);
	}
	k[0] = dot_vectors(direction, direction);
	k[1] = 2 * dot_vectors(*object->difference, direction);
	discriminant = k[1] * k[1] - 4 * k[0] * object->var_c;
	if (discriminant < 0)
		return (0);
	t[0] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
	t[1] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
	if (t[0] < t[1])
		return (t[0]);
	return (t[1]);
}
