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
	float		diameter;
	float		height;
	t_vector	*color;
	float		shiny;
	t_vector	*difference;
	float		var_a;
	float		var_c;
	float		var_d;
	t_vector	*prev_origin;
}				t_cylinder;

t_cylinder		*new_cylinder(t_vector *vectors[2],
float diameter, float height, t_vector *color);
void			free_cylinder(t_cylinder *cylinder);
t_cylinder		*cpy_cylinder(t_cylinder *cylinder);

#endif
