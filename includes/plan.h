/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 05:20:57 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/29 10:24:31 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAN_H
# define PLAN_H

# include <stdlib.h>
# include "vector.h"

typedef struct	s_plan
{
	t_vector	*point;
	t_vector	*normal;
	double		shiny;
	t_vector	*color;
	double		var_a;
	t_vector	*prev_origin;
}				t_plan;

t_plan			*new_plan(t_vector *p, t_vector	*v, t_vector *c);
void			free_plan(t_plan *plan);
t_plan			*cpy_plan(t_plan *plan);

#endif
