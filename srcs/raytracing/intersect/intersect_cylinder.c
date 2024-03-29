/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:00:17 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:27:57 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		intersect_cylinder5(double d[8], t_vector origin, t_vector direction,
t_cylinder *o)
{
	t_vector	*temp;
	t_vector	*point;
	double		denom;
	double		l[2];

	denom = -(dot_vectors(*o->orientation, *o->point2));
	l[0] = dot_vectors(origin, *o->orientation) + denom;
	l[1] = dot_vectors(direction, *o->orientation);
	d[5] = -(l[0] / l[1]);
	if (d[5] > 0)
	{
		temp = scale_vectors(d[5], direction);
		point = add_vectors(origin, *temp);
		free(temp);
		d[0] = distance_points(*point, *o->point2);
		d[1] = distance_points(*point, origin);
		free(point);
		if (d[0] < o->diameter / 2 && (!(d[2] > o->height || d[3] > o->height)))
			return (d[4]);
		if (d[0] < o->diameter / 2)
			return (d[5]);
	}
	if ((d[2] > o->height || d[3] > o->height))
		return (0);
	return (d[4]);
}

double		intersect_cylinder4(double d[8], t_vector origin, t_vector direction,
t_cylinder *o)
{
	t_vector	*temp;
	t_vector	*point;
	double		denom;
	double		l[2];

	denom = -(dot_vectors(*o->orientation, *o->point1));
	l[0] = dot_vectors(origin, *o->orientation) + denom;
	l[1] = dot_vectors(direction, *o->orientation);
	d[5] = -(l[0] / l[1]);
	if (d[5] > 0)
	{
		temp = scale_vectors(d[5], direction);
		point = add_vectors(origin, *temp);
		free(temp);
		d[0] = distance_points(*point, *o->point1);
		d[1] = distance_points(*point, origin);
		free(point);
		if (d[0] < o->diameter / 2 && (!(d[2] > o->height || d[3] > o->height)))
			return (d[4]);
		if (d[0] < o->diameter / 2)
			return (d[5]);
	}
	return (intersect_cylinder5(d, origin, direction, o));
}

double		intersect_cylinder3(double d[8], t_vector origin, t_vector direction,
t_cylinder *o)
{
	t_vector	*temp[2];
	t_vector	*point;
	double		denom;
	t_vector	*point_tmp;
	double		tt;

	temp[0] = scale_vectors(d[4], direction);
	point = add_vectors(origin, *temp[0]);
	denom = -(dot_vectors(*o->orientation, *o->point2));
	d[5] = dot_vectors(*point, *o->orientation) + denom;
	temp[1] = scale_vectors(-1, *o->orientation);
	d[6] = dot_vectors(*temp[1], *o->orientation);
	tt = -(d[5] / d[6]);
	temp[0] = scale_vectors(tt, *temp[1]);
	point_tmp = add_vectors(*point, *temp[0]);
	free(temp[1]);
	free(temp[0]);
	d[3] = distance_points(*point, *point_tmp);
	free(point_tmp);
	free(point);
	return (intersect_cylinder4(d, origin, direction, o));
}

double		intersect_cylinder2(double ret, t_vector origin, t_vector direction,
t_cylinder *object)
{
	t_vector	*temp;
	t_vector	*point;
	double		denom;
	t_vector	*point_tmp;
	double		d[8];

	d[4] = ret;
	temp = scale_vectors(ret, direction);
	point = add_vectors(origin, *temp);
	free(temp);
	denom = -(dot_vectors(*object->orientation, *object->point1));
	d[5] = dot_vectors(*point, *object->orientation) + denom;
	d[6] = dot_vectors(*object->orientation, *object->orientation);
	d[7] = -(d[5] / d[6]);
	temp = scale_vectors(d[7], *object->orientation);
	point_tmp = add_vectors(*point, *temp);
	free(temp);
	d[2] = distance_points(*point, *point_tmp);
	free(point_tmp);
	free(point);
	return (intersect_cylinder3(d, origin, direction, object));
}

double		intersect_cylinder(t_vector origin, t_vector direction,
t_cylinder *o)
{
	double var_b;
	double d[6];
	double delta;
	double ret;

	init_cylinder_intersect_cylinder(origin, o);
	var_b = dot_vectors(direction, *o->orientation);
	d[0] = dot_vectors(direction, direction) - (var_b *
var_b * o->var_a);
	d[1] = 2.0 * (dot_vectors(direction, *o->difference)) -
(2 * var_b * o->var_d * o->var_a);
	d[2] = o->var_c - ((o->diameter / 2.0) * (o->diameter / 2.0)) -
((o->var_d * o->var_d) * o->var_a);
	delta = (d[1] * d[1]) - (4.0 * d[0] * d[2]);
	if (delta < 0)
		return (0);
	d[3] = (-d[1] + sqrt(delta)) / (2.0 * d[0]);
	d[4] = (-d[1] - sqrt(delta)) / (2.0 * d[0]);
	if (d[3] < d[4])
		ret = d[3];
	else
		ret = d[4];
	return (intersect_cylinder2(ret, origin, direction, o));
}
