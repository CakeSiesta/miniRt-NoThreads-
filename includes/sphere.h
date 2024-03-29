/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 07:09:23 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:25:29 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <stdlib.h>
# include "vector.h"

typedef struct	s_sphere
{
	double		radius;
	t_vector	*color;
	double		shiny;
	double		var_c;
	t_vector	*difference;
	t_vector	*center;
	t_vector	*prev_origin;
}				t_sphere;

t_sphere		*new_sphere(double radius, t_vector *color,
double shiny, t_vector *center);
void			free_sphere(t_sphere *sphere);
t_sphere		*cpy_sphere(t_sphere *sphere);

#endif
