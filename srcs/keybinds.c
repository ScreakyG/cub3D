/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:23:22 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/25 09:31:02 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keycode, void *data)
{
	t_data *data_ptr;

	data_ptr = (t_data *)data;
	if (keycode == XK_Escape)
		clean_exit(data_ptr);
	return (0);
}

