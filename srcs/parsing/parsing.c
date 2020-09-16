/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:05:57 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/16 15:59:09 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			choice_parsing(t_scene **scene, char *line)
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

// sets in scene num of cameras
void		setup_cameras(t_scene **scene)
{
	int		nb_cam;
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
		cameras->next = (*scene)->cameras; //whut
		(*scene)->cameras->prev = cameras; // double whuttt
	}
	(*scene)->nb_camera = nb_cam;
}

// sets/fixes/tweeks resolution
void		setup_viewplane(t_scene **scene)
{
	if (!(*scene)->viewport)
		print_error_and_exit(-5); // resolution not specified
	if ((*scene)->viewport->height <= 0 || (*scene)->viewport->width <= 0)
		print_error_and_exit(-6); // cannot create window with value 0
	if ((*scene)->viewport->width > LIMIT_RES_X)
		(*scene)->viewport->width = LIMIT_RES_X; // resets too big X res
	if ((*scene)->viewport->height > LIMIT_RES_Y)
		(*scene)->viewport->height = LIMIT_RES_Y; // resets too big Y res
	if ((*scene)->viewport->height < (*scene)->viewport->width)
		(*scene)->viewplane = new_canvas((*scene)->viewport->width / // adjusts width && height
		(*scene)->viewport->height, 1, 1);
	else
		(*scene)->viewplane = new_canvas(1, (*scene)->viewport->height /
(*scene)->viewport->width, 1);
}

t_scene		*parsing(int fd)
{
	int				ret;
	char			*line;
	t_scene			*scene;

	scene = new_empty_scene(BACKGROUND_COLOR);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((ret = choice_parsing(&scene, line)) < 0)
			return (NULL);
		free(line);
	}
	if (ret < 0 || (ret = choice_parsing(&scene, line)) < 0)
		return (NULL);
	setup_cameras(&scene); // sets in scene num of cameras
	setup_viewplane(&scene); // sets resolution
	return (scene);
}

// open .rt file //
int			open_and_check_error(char *filename, int *fd)
{
	int		i;

	if ((*fd = open(filename, O_RDONLY)) <= 0)
		print_error_and_exit(-1); // no such file in directory // nothing to read
	i = 0;
	while (filename[i] != '.' && filename[i]) //increment till . before .rt
		i++;
	if (!filename[i])
		print_error_and_exit(-2); // extension needed AKA nothing after try. XX
	if (i < 3 || ft_strcmp(&filename[i], ".rt"))
		print_error_and_exit(-3); // invalid extension
	return (i);
}
