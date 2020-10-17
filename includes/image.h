/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 22:06:29 by lmartin           #+#    #+#             */
/*   Updated: 2020/10/17 14:00:44 by mkravetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

typedef struct		s_args
{
	char			*data;
	t_scene			*scene;
	int			x;
	int			bpp;
	int			size_line;
	pthread_mutex_t 	*lock;
}					t_args;

void				put_pixel(t_args *args, int y, int color);
void				*thread_function(t_args *args);
t_args				*new_s_args(t_mlx *my_mlx, int i);
void				create_image(t_mlx	*my_mlx);

#endif
