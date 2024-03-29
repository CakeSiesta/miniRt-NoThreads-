/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 04:57:24 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:25:43 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include <stdlib.h>
# include "vector.h"

typedef struct	s_square
{
	t_vector	*center;
	t_vector	*orientation;
	t_vector	*a;
	t_vector	*b;
	t_vector	*c;
	t_vector	*d;
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*normal;
	double		size;
	t_vector	*color;
	double		shiny;
	double		var_a;
	t_vector	*prev_origin;
}				t_square;

t_square		*new_square(t_vector *center, t_vector *orientation,
double size, t_vector *color);
void			free_square(t_square *square);
t_square		*cpy_square(t_square *square);

#endif
