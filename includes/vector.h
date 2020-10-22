/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 07:02:22 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:56:01 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_lightning_vectors
{
	t_vector	*point;
	t_vector	*normal;
	t_vector	*view;
	double		shiny;
}				t_lightning_vectors;

/*
** Calculation
*/
double			length_vectors(t_vector v);
double			distance_points(t_vector p1, t_vector p2);
double			dot_vectors(t_vector v1, t_vector v2);
t_vector		*cross(t_vector u, t_vector v);
t_vector		*product_scalar(t_vector u, t_vector v);
t_vector		*add_vectors(t_vector v1, t_vector v2);
t_vector		*substract_vectors(t_vector v1, t_vector v2);
t_vector		*scale_vectors_rotation(t_vector r, t_vector v2);
t_vector		*scale_vectors(double k, t_vector v2);

/*
** Color
*/
t_vector		*color_to_rgb(unsigned int color);
int				rgb_to_color(t_vector *rgb);
void			rearrange_rgb(t_vector *color);

/*
** Vector
*/
t_vector		*new_vector(double x, double y, double z);
t_vector		*cpy_vector(t_vector *vector);
int				is_equal(t_vector *a, t_vector *b);

#endif
