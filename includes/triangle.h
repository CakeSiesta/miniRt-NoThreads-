/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 04:05:15 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:26:00 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include <stdlib.h>
# include "vector.h"

typedef struct	s_triangle
{
	t_vector	*a;
	t_vector	*b;
	t_vector	*c;
	t_vector	*u;
	t_vector	*v;
	t_vector	*normal;
	t_vector	*color;
	float		shiny;
	float		var_a;
	float		dot_uu;
	float		dot_uv;
	float		dot_vv;
	float		var_d;
	t_vector	*prev_origin;
}				t_triangle;

t_triangle		*new_triangle(t_vector *a, t_vector *b, t_vector *c,
t_vector *color);
void			free_triangle(t_triangle *triangle);
t_triangle		*cpy_triangle(t_triangle *triangle);

#endif
