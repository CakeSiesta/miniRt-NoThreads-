/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherrald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:38:27 by jherrald          #+#    #+#             */
/*   Updated: 2020/10/17 17:26:52 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Change pixel color by changing (char *data)
** (R) data[i]
** (G) data[i + 1]
** (B) data[i + 2]
*/

void	put_pixel(t_args *args, int y, int color)
{
	long long unsigned	i;

	i = ((args->x + (args->scene->viewport->width / 2)) *
(args->bpp / 8)) + (y * args->size_line);
	args->data[i] = color;
	args->data[++i] = color >> 8;
	args->data[++i] = color >> 16;
}

/*
** Function for each thread (1 thread == 1 column)
*/

void	*thread_function(t_args *args)
{
	t_vector		*obs;
	t_vector		*d;
	int				c;
	int				y;

	if (!(t_camera *)args->scene->cameras)
		return (free_cpy_scene(args->scene) ? NULL : NULL);
	obs = ((t_camera *)args->scene->cameras->object)->origin;
	y = -(args->scene->viewport->height / 2);
	while (++y <= args->scene->viewport->height / 2)
	{
		d = new_vector(
args->x * (args->scene->viewplane->width / args->scene->viewport->width),
y * (args->scene->viewplane->height / args->scene->viewport->height), 1);
		rot(d, ((t_camera *)args->scene->cameras->object)->rotation);
		c = trace_ray(*d, args->scene);
		put_pixel(args, ((-(y - (args->scene->viewport->height / 2)))), c);
		free(d);
		((t_camera *)args->scene->cameras->object)->origin = obs;
		args->scene->depth = 3;
	}
	return (free_cpy_scene(args->scene) ? NULL : NULL);
}

/*
** Init a new t_args with all arguments for thread_function
*/

t_args	*new_s_args(t_mlx *my_mlx, int i)
{
	t_args			*args;

	if (!(args = malloc(sizeof(t_args))))
		print_error_and_exit(-7);
	args->data = my_mlx->data;
	args->scene = cpy_scene(my_mlx->scene);
	args->x = 0;
	args->x = -(my_mlx->scene->viewport->width / 2) + 1 + i;
	args->bpp = my_mlx->bpp;
	args->size_line = my_mlx->size_line;
	return (args);
}

/*
** Create a new image charging each column by a thread
*/


void	create_image(t_mlx *my_mlx)
{
	int			i;
	t_args			*args;

	i = -1;
	while (++i < my_mlx->scene->viewport->width)
	{
		args = new_s_args(my_mlx, i);
		thread_function(args);
	}
	while (i) // goes from i (width - 1) down to 0
		i--;
	i = my_mlx->scene->viewport->width;
	while (--i)
		wait(NULL);
}
