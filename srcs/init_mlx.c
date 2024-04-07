/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:45:02 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/07 07:04:25 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_mlx(t_data *data)
{
	int	size_x;
	int size_y;

	data->mlx.mlx_ptr = mlx_init();
	if (!data->mlx.mlx_ptr)
		ft_exit_error("Mlx init error", 1, data);
	mlx_get_screen_size(data->mlx.mlx_ptr, &size_x, &size_y);
	if (WIN_WIDTH > size_x || WIN_HEIGHT > size_y)
	{
		printf(RED"Error with choosen resolution, maximum resolution for your screen is %d * %d\n"RESET, size_x, size_y);
		ft_exit_error("", 1, data);
	}
	if (WIN_WIDTH <= 0 || WIN_HEIGHT <= 0)
	{
		printf(RED"Error with choosen resolution, it should be superior to 0\n"RESET);
		ft_exit_error("", 1, data);
	}
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->mlx.mlx_win)
		ft_exit_error("Mlx win init error", 1, data);
}
