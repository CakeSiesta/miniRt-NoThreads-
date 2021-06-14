/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 07:46:39 by lmartin           #+#    #+#             */
/*   Updated: 2021/06/14 09:15:18 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	length_vectors(t_vector v)
{
	return (sqrt(dot_vectors(v, v)));
}

double	distance_points(t_vector p1, t_vector p2)
{
	double	sqroot;

	sqroot = sqrt(p2.x - p1.x) * (p2.x - p1.x);
	sqroot += (p2.y - p1.y) * (p2.y - p1.y);
	sqroot += (p2.z - p1.z) * (p2.z - p1.z);
	sqroot = sqrt(sqroot);
	return (sqroot);
}

double	dot_vectors(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
