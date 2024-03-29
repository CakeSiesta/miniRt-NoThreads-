/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkravetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:48:07 by mkravetz          #+#    #+#             */
/*   Updated: 2021/06/14 16:11:11 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* i[1] = 0		i[1] == 1		i[1] == 2
** sp 0,0,0		5,23			255,255,255
*/
int	parsing_sphere(t_scene **scene, char *l)
{
	int			i[3];
	t_vector	*center;
	double		radius;
	t_vector	*color;

	i[0] = 2;
	i[2] = 0;
	i[1] = -1;
	while (++i[1] < 4 && (l[i[0]] == ' ' || l[i[0]] == '\t'))
	{
		while (l[i[0]] == ' ' || l[i[0]] == '\t')
			i[0]++;
		if (!i[1] && (((l[i[0]] < '0' || l[i[0]] > '9') && l[i[0]] != '-')))
			return (-1);
		if (!i[1])
		{
			i[2] = ft_atov(&l[i[0]], &center);
			if (i[2] < 0)
				return (-1);
		}
		if ((i[1] == 1) && ((l[i[0]] < '0' || l[i[0]] > '9')))
			return (free_and_return_minus_one(center));
		if (i[1] == 1)
		{
			i[2] = ft_atof(&l[i[0]], &radius);
			if (i[2] < 0)
				return (free_and_return_minus_one(center));
		}
		if ((i[1] == 2) && ((l[i[0]] < '0' || l[i[0]] > '9')))
			return (free_and_return_minus_one(center));
		if (i[1] == 2)
		{
			i[2] = ft_atoc(&l[i[0]], &color);
			if (i[2] < 0)
				return (free_and_return_minus_one(center));
		}
		i[0] += i[2];
	}
	if (l[i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (free_and_return_minus_one(center));
	if (!l[i[0]] && !(add_back(&(*scene)->objects, TYPE_SPHERE, new_sphere
				(radius, color, 10, center), 0.4)))
		return (0);
	else
		return (-1);
}

/* pl  0.0,0.0,0.0  0.0,0.0,1.0  0,0,255
**      pos point    3d orient    color
*/
int	parsing_plan(t_scene **scene, char *line)
{
	int			i;
	int			r;
	int			n;
	t_vector	*vectors[2];
	t_vector	*color;

	i = 2;
	r = 0;
	n = -1;
	while (++n < 4 && (i += r) > 0 && (line[i] == ' ' || line[i] == '\t'))
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if ((n < 2) && (((line[i] < '0' || line[i] > '9') && line[i] != '-')
				|| (r = ft_atov(&line[i], &vectors[n])) < 0))
			return (multiple_free_return(vectors, n - 1));
		if ((n == 2) && ((line[i] < '0' || line[i] > '9')
				|| (r = ft_atoc(&line[i], &color)) < 0))
			return (multiple_free_return(vectors, 2));
	}
	if (line[i] && line[i] != ' ' && line[i] != '\t')
		return (multiple_free_return(vectors, 2));
	return ((!(add_back(&(*scene)->objects, TYPE_PLAN, new_plan(
vectors[0], vectors[1], color), 0.5)) ? 0 : -1));
}

/* sq  0.0,0.0,20.6   1.0,0.0,0.0   12.6   255,0,255
**	      center	   3d orient     h	    color
*/
int	parsing_square(t_scene **scene, char *l)
{
	int			i[3];
	t_vector	*color;
	t_vector	*vectors[2];
	double		size;

	i[0] = 2;
	i[2] = 0;
	i[1] = -1;
	while (++i[1] < 5 && (i[0] += i[2]) && (l[i[0]] == ' ' || l[i[0]] == '\t'))
	{
		while (l[i[0]] == ' ' || l[i[0]] == '\t')
			i[0]++;
		if ((i[1] < 2) && (((l[i[0]] < '0' || l[i[0]] > '9') && l[i[0]] != '-')
				|| (i[2] = ft_atov(&l[i[0]], &vectors[i[1]])) < 0))
			return (multiple_free_return(vectors, i[1] - 1));
		if (((i[1] == 2) && ((l[i[0]] < '0' || l[i[0]] > '9')
					|| (i[2] = ft_atof(&l[i[0]], &size)) < 0))
			|| ((i[1] == 3) && ((l[i[0]] < '0' || l[i[0]] > '9')
					|| (i[2] = ft_atoc(&l[i[0]], &color)) < 0)))
			return (multiple_free_return(vectors, 2));
	}
	if (l[i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (multiple_free_return(vectors, 2));
	return ((!(add_back(&(*scene)->objects, TYPE_SQUARE, new_square(
vectors[0], vectors[1], size, color), -1)) ? 0 : -1));
}

/* tr  10.0,20.0,10.0   10.0,10.0,20.0   20.0,10.0,10.0   0,255,255
**	    pos point1	     pos point2	      pos point3	    color
*/
int	parsing_triangle(t_scene **scene, char *l)
{
	int			i[3];
	t_vector	*color;
	t_vector	*vec[3];

	i[0] = 2;
	i[2] = 0;
	i[1] = -1;
	while (++i[1] < 5 && (i[0] += i[2]) && (l[i[0]] == ' ' || l[i[0]] == '\t'))
	{
		while (l[i[0]] == ' ' || l[i[0]] == '\t')
			i[0]++;
		if ((i[1] < 3) && (((l[i[0]] < '0' || l[i[0]] > '9') && l[i[0]] != '-')
				|| (i[2] = ft_atov(&l[i[0]], &vec[i[1]])) < 0))
			return (multiple_free_return(vec, i[1] - 1));
		if ((i[1] == 3) && ((l[i[0]] < '0' || l[i[0]] > '9')
				|| (i[2] = ft_atoc(&l[i[0]], &color)) < 0))
			return (multiple_free_return(vec, 3));
	}
	if (l[i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (multiple_free_return(vec, 3));
	return ((!(add_back(&(*scene)->objects, TYPE_TRIANGLE, new_triangle(
vec[0], vec[1], vec[2], color), -1)) ? 0 : -1));
}

/*i[1] =0				1			2		3		4
** cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255
**	    center			3d orient	diam	h		color
*/
int	parsing_cylinder(t_scene **scene, char *l)
{
	int			i[3];
	t_vector	*color;
	t_vector	*vec[2];
	double		j[2];

	i[0] = 2;
	i[2] = 0;
	i[1] = -1;
	while (++i[1] < 6 && (i[0] += i[2]) && (l[i[0]] == ' ' || l[i[0]] == '\t'))
	{
		while (l[i[0]] == ' ' || l[i[0]] == '\t')
			i[0]++;
		if ((i[1] < 2) && (((l[i[0]] < '0' || l[i[0]] > '9') && l[i[0]] != '-')
				|| (i[2] = ft_atov(&l[i[0]], &vec[i[1]])) < 0))
			return (multiple_free_return(vec, i[1] - 1));
		if (((i[1] == 4) && ((l[i[0]] < '0' || l[i[0]] > '9')
					|| (i[2] = ft_atoc(&l[i[0]], &color)) < 0))
			|| ((i[1] > 1 && i[1] < 4) && ((l[i[0]] < '0' || l[i[0]] > '9')
					|| (i[2] = ft_atof(&l[i[0]], &j[i[1] - 2])) < 0)))
			return (multiple_free_return(vec, 2));
	}
	if (l[i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (multiple_free_return(vec, 2));
	return ((!(add_back(&(*scene)->objects, TYPE_CYLINDER, new_cylinder(
vec, j[0], j[1], color), -1)) ? 0 : -1));
}
