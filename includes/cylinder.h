/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:58:19 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:21:01 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include <stdlib.h>
# include "vector.h"

typedef struct	s_cylinder
{
	t_vector	*center;
	t_vector	*orientation;
	t_vector	*point1;
	t_vector	*point2;
	double		diameter;
	double		height;
	t_vector	*color;
	double		shiny;
	t_vector	*difference;
	double		var_a;
	double		var_c;
	double		var_d;
	t_vector	*prev_origin;
}				t_cylinder;

t_cylinder		*new_cylinder(t_vector *vectors[2],
double diameter, double height, t_vector *color);
void			free_cylinder(t_cylinder *cylinder);
t_cylinder		*cpy_cylinder(t_cylinder *cylinder);

#endif
