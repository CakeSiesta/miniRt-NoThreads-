/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:02:57 by lmartin           #+#    #+#             */
/*   Updated: 2020/10/19 16:59:05 by jherrald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_KEY_H
# define HANDLE_KEY_H

# define KEYCODE_Q 12
# define KEYCODE_E 14
# define KEYCODE_A 0
# define KEYCODE_D 2
# define KEYCODE_S 1
# define KEYCODE_W 13
# define KEYCODE_R 15
# define KEYCODE_F 3
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_UP 125
# define KEYCODE_DOWN 126
# define KEYCODE_1 84
# define KEYCODE_2 83
# define KEYCODE_G 5
# define KEYCODE_B 11

int		exit_program(void);
int		handle_key(int keycode, t_mlx *my_mlx);

#endif
