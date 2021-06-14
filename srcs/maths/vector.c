/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 07:06:42 by lmartin           #+#    #+#             */
/*   Updated: 2021/06/14 09:09:52 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "vector.h"

t_vector	*new_vector(double x, double y, double z)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!(vector))
		print_error_and_exit(-7);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	*cpy_vector(t_vector *vector)
{
	return (new_vector(vector->x, vector->y, vector->z));
}

int	is_equal(t_vector *a, t_vector *b)
{
	return ((a->x == b->x && a->y == b->y && a->z == b->z));
}
