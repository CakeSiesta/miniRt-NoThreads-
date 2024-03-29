/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:00:45 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:28:26 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		intersect_triangle2(double t, t_vector origin, t_vector direction,
t_triangle *object)
{
	t_vector		*temp;
	t_vector		*point;
	double			dot_wv_wu[2];
	t_vector		*w;
	double			r[2];

	temp = scale_vectors(t, direction);
	point = add_vectors(origin, *temp);
	free(temp);
	w = substract_vectors(*point, *object->a);
	dot_wv_wu[0] = dot_vectors(*w, *object->u);
	dot_wv_wu[1] = dot_vectors(*w, *object->v);
	r[0] = (object->dot_uv * dot_wv_wu[1] - object->dot_vv *
dot_wv_wu[0]) / object->var_d;
	free(w);
	if (r[0] < 0 || r[0] > 1)
		return (0);
	r[1] = (object->dot_uv * dot_wv_wu[0] - object->dot_uu *
dot_wv_wu[1]) / object->var_d;
	if (r[1] < 0 || (r[0] + r[1] > 1))
		return (0);
	return (t);
}

double		intersect_triangle(t_vector origin, t_vector direction,
t_triangle *object)
{
	double			denom;
	double			b;
	double			t;

	t = 0;
	if (!object->prev_origin || !is_equal(object->prev_origin, &origin))
	{
		if (object->prev_origin)
			free(object->prev_origin);
		denom = -(dot_vectors(*object->normal, *object->a));
		object->var_a = dot_vectors(origin, *object->normal) + denom;
		object->prev_origin = cpy_vector(&origin);
	}
	b = dot_vectors(direction, *object->normal);
	t = -(object->var_a / b);
	if (t <= 0)
		return (0);
	return (intersect_triangle2(t, origin, direction, object));
}
