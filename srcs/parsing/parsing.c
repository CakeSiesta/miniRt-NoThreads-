/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherrald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:39:07 by jherrald          #+#    #+#             */
/*   Updated: 2021/06/23 14:11:55 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	choice_parsing(t_scene **scene, char *line)
{
	if (line[0] != '\0')
	{
		if (line[0] == 'R')
			return (parsing_resolution(scene, line));
		else if (line[0] == 'A')
			return (parsing_ambient_light(scene, line));
		else if (line[0] == 'c' && line[1] == 'y')
			return (parsing_cylinder(scene, line));
		else if (line[0] == 'c')
			return (parsing_camera(scene, line));
		else if (line[0] == 'l')
			return (parsing_point_light(scene, line));
		else if (line[0] == 's' && line[1] == 'p')
			return (parsing_sphere(scene, line));
		else if (line[0] == 's' && line[1] == 'q')
			return (parsing_square(scene, line));
		else if (line[0] == 'p' && line[1] == 'l')
			return (parsing_plan(scene, line));
		else if (line[0] == 't' && line[1] == 'r')
			return (parsing_triangle(scene, line));
		else
			return (-1);
	}
	return (0);
}

void	setup_cameras(t_scene **scene)
{
	int				nb_cam;
	t_lstobjects	*cameras;

	nb_cam = 0;
	cameras = (*scene)->cameras;
	if (cameras)
	{
		nb_cam = 1;
		while (cameras->next)
		{
			((t_lstobjects *)cameras->next)->prev = cameras;
			nb_cam++;
			cameras = cameras->next;
		}
		cameras->next = (*scene)->cameras;
		(*scene)->cameras->prev = cameras;
	}
	(*scene)->nb_camera = nb_cam;
}

void	setup_viewplane(t_scene **scene)
{
	if (!(*scene)->viewport)
		print_error_and_exit(-5);
	if ((*scene)->viewport->height <= 0 || (*scene)->viewport->width <= 0)
		print_error_and_exit(-6);
	if ((*scene)->viewport->width > LIMIT_RES_X)
		(*scene)->viewport->width = LIMIT_RES_X;
	if ((*scene)->viewport->height > LIMIT_RES_Y)
		(*scene)->viewport->height = LIMIT_RES_Y;
	if ((*scene)->viewport->height < (*scene)->viewport->width)
		(*scene)->viewplane = new_canvas((*scene)->viewport->width
				/ (*scene)->viewport->height, 1, 1);
	else
		(*scene)->viewplane = new_canvas(1, (*scene)->viewport->height
				/ (*scene)->viewport->width, 1);
}

t_scene	*parsing(int fd)
{
	int				ret;
	char			*line;
	t_scene			*scene;

	scene = new_empty_scene(BACKGROUND_COLOR);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ret = choice_parsing(&scene, line);
		if (ret < 0)
			return (NULL);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret < 0)
		return (NULL);
	setup_cameras(&scene);
	setup_viewplane(&scene);
	return (scene);
}

/*
** Returns i (= lenght of .rt file) or ERROR msg if .rt incorrect
*/
int	open_and_check_error(char *filename, int *fd)
{
	int		i;

	*fd = open(filename, O_RDONLY);
	if (*fd <= 0)
		print_error_and_exit(-1);
	i = 0;
	while (filename[i] != '.' && filename[i])
		i++;
	if (!filename[i])
		print_error_and_exit(-2);
	if (i < 1 || ft_strcmp(&filename[i], ".rt"))
		print_error_and_exit(-3);
	return (i);
}
