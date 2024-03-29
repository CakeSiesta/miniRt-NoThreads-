/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherrald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:14:06 by jherrald          #+#    #+#             */
/*   Updated: 2020/10/16 17:26:35 by jherrald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parsing_resolution(t_scene **scene, char *line)
{
	int i;
	int r;
	int res_x;
	int res_y;

	i = 1;
	if (line[i] != ' ' && line[i] != '\t')
		return (-1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if ((line[i] < '0' || line[i] > '9') || (r = ft_atoi(&line[i], &res_x)) < 0)
		return (-1);
	if ((i += r) > 0 && line[i] != ' ' && line[i] != '\t')
		return (-1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if ((line[i] < '0' || line[i] > '9') || (r = ft_atoi(&line[i], &res_y)) < 0)
		return (-1);
	i += r;
	while (line[i] == ' ' || line[i] == '\t')
		if (line[++i] && line[i] != ' ' && line[i] != '\t')
			return (-1);
	return (!((*scene)->viewport = new_canvas(res_x, res_y, 1)) ? -1 : 0);
}

// A	0.5		255,255,255
// 		intens		color
int		parsing_ambient_light(t_scene **scene, char *l)
{
	int			i[2];
	double		intensity;
	t_vector	*c;

	i[0] = 1;
	if (l[i[0]] != ' ' && l[i[0]] != '\t')
		return (-1);
	while (l[i[0]] == ' ' || l[i[0]] == '\t')
		i[0]++;
	if ((l[i[0]] < '0' || l[i[0]] > '9') ||
(i[1] = ft_atof(&l[i[0]], &intensity)) < 0)
		return (-1);
	if ((i[0] += i[1]) > 0 && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (-1);
	while (l[i[0]] == ' ' || l[i[0]] == '\t')
		i[0]++;
	if ((l[i[0]] < '0' || l[i[0]] > '9') || (i[1] = ft_atoc(&l[i[0]], &c)) < 0)
		return (-1);
	i[0] += i[1];
	while (l[i[0]] == ' ' || l[i[0]] == '\t')
		if (l[++i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
			return (-1);
	(*scene)->total_intensity += intensity;
	return ((!(add_back(&(*scene)->lights, TYPE_LIGHT,
new_default_light(TYPE_AMBIENT, intensity, c), -1))) ? 0 : -1);
}

int		parsing_point_light(t_scene **scene, char *l)
{
	int			i[3];
	t_vector	*v[2];
	double		intensity;

	i[0] = 1;
	i[1] = 0;
	i[2] = 0;
	while (i[2] < 4 && (i[0] += i[1]) && (l[i[0]] == ' ' || l[i[0]] == '\t'))
	{
		while (l[i[0]] == ' ' || l[i[0]] == '\t')
			i[0]++;
		if ((i[2] == 0) && (((l[i[0]] < '0' || l[i[0]] > '9')
		&& l[i[0]] != '-') || (i[1] = ft_atov(&l[i[0]], &v[1])) < 0))
			return (-1);
		if (((i[2] == 1) && ((l[i[0]] < '0' || l[i[0]] > '9') ||
		(i[1] = ft_atof(&l[i[0]], &intensity)) < 0)) ||
		((i[2]++ == 2) && ((l[i[0]] < '0' || l[i[0]] > '9') ||
		(i[1] = ft_atoc(&l[i[0]], &v[0])) < 0)))
			return (free_and_return_minus_one(v[1]));
	}
	if (l[i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (free_and_return_minus_one(v[1]));
	(*scene)->total_intensity += intensity;
	return ((!(add_back(&(*scene)->lights, TYPE_LIGHT,
new_point_light(v[1], intensity, v[0]), -1))) ? 0 : -1);
}

int		parsing_directional_light(t_scene **scene, char *line)
{
	(void)scene;
	(void)line;
	return (0);
}
// c 	0.0,0.0,0.0		0,0,1		70
// 			coord		orient		fov	
int		parsing_camera(t_scene **scene, char *l)
{
	int			i;
	int			r;
	int			n;
	t_vector	*vectors[2];
	int			fov;

	i = 1;
	r = 0;
	n = -1;
	while (++n < 4 && (i += r) && l[i] && (l[i] == ' ' || l[i] == '\t'))
	{
		while (l[i] == ' ' || l[i] == '\t')
			i++;
		if ((n < 2) && (((l[i] < '0' || l[i] > '9') && l[i] != '-') ||
		(r = ft_atov(&l[i], &vectors[n])) < 0))
			return (multiple_free_return(vectors, n - 1));
		if ((n == 2) && ((l[i] < '0' || l[i] > '9') ||
		(r = ft_atoi(&l[i], &fov)) < 0))
			return (multiple_free_return(vectors, 2));
	}
	if (l[i] && l[i] != ' ' && l[i] != '\t')
		return (multiple_free_return(vectors, 2));
	return ((!(add_back(&(*scene)->cameras, TYPE_CAMERA, new_camera(
vectors[0], vectors[1], fov), -1)) ? 0 : -1));
}
