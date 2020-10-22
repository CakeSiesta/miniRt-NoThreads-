/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:01:49 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:28:18 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		intersect_square2(double t, t_vector origin, t_vector direction,
t_square *object)
{
	t_vector	*point;
	t_vector	*temp;
	t_vector	*ap;
	double		alpha;
	double		beta;

	temp = scale_vectors(t, direction);
	point = add_vectors(origin, *temp);
	free(temp);
	ap = substract_vectors(*point, *object->a);
	alpha = dot_vectors(*ap, *object->ab) /
dot_vectors(*object->ab, *object->ab);
	beta = dot_vectors(*ap, *object->ac) /
dot_vectors(*object->ac, *object->ac);
	free(ap);
	free(point);
	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1)
		return (t);
	return (0);
}

double		intersect_square(t_vector origin, t_vector direction,
t_square *object)
{
	double denom;
	double alpha;
	double beta;

	beta = 0;
	if (!object->prev_origin || !is_equal(object->prev_origin, &origin))
	{
		if (object->prev_origin)
			free(object->prev_origin);
		denom = -(dot_vectors(*object->normal, *object->center));
		object->var_a = dot_vectors(origin, *object->normal) + denom;
		object->prev_origin = cpy_vector(&origin);
	}
	alpha = dot_vectors(direction, *object->normal);
	beta = -(object->var_a / alpha);
	if (beta <= 0)
		return (0);
	return (intersect_square2(beta, origin, direction, object));
}
