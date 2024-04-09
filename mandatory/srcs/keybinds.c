/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:23:22 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/08 04:41:19 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keycode, void *data)
{
	t_data	*data_ptr;

	data_ptr = (t_data *)data;
	if (keycode == XK_Escape)
		clean_exit(data_ptr);
	else if (keycode == XK_a || keycode == XK_A)
		data_ptr->player.side_direction = -1;
	else if (keycode == XK_d || keycode == XK_D)
		data_ptr->player.side_direction = 1;
	else if (keycode == XK_s || keycode == XK_S)
		data_ptr->player.walk_direction = -1;
	else if (keycode == XK_w || keycode == XK_W)
		data_ptr->player.walk_direction = 1;
	else if (keycode == XK_Left)
		data_ptr->player.rotation_direction = -1;
	else if (keycode == XK_Right)
		data_ptr->player.rotation_direction = 1;
	return (0);
}

int	handle_keyrelease(int keycode, void *data)
{
	t_data	*data_ptr;

	data_ptr = (t_data *)data;
	if (keycode == XK_a || keycode == XK_A)
		data_ptr->player.side_direction = 0;
	else if (keycode == XK_d || keycode == XK_D)
		data_ptr->player.side_direction = 0;
	else if (keycode == XK_s || keycode == XK_S)
		data_ptr->player.walk_direction = 0;
	else if (keycode == XK_w || keycode == XK_W)
		data_ptr->player.walk_direction = 0;
	else if (keycode == XK_Left)
		data_ptr->player.rotation_direction = 0;
	else if (keycode == XK_Right)
		data_ptr->player.rotation_direction = 0;
	return (0);
}
