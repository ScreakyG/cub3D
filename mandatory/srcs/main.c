/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:38 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/18 15:12:17 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(void *data)
{
	t_data	*data_ptr;
	t_img	img;

	data_ptr = (t_data *)data;
	data_ptr->img = mlx_new_image(data_ptr->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(data_ptr->img, &img.bpp,
			&img.line_length, &img.endian);
	movements(data_ptr);
	cast_all_rays(data_ptr);
	render_projection(data_ptr, &img);
	mlx_put_image_to_window(data_ptr->mlx.mlx_ptr, data_ptr->mlx.mlx_win,
		data_ptr->img, 0, 0);
	mlx_destroy_image(data_ptr->mlx.mlx_ptr, data_ptr->img);
	return (0);
}

void	start_game(t_data *data)
{
	mlx_loop_hook(data->mlx.mlx_ptr, &game_loop, data);
	mlx_hook(data->mlx.mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx.mlx_win, KeyRelease,
		KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->mlx.mlx_win, DestroyNotify, 0, &clean_exit, data);
	mlx_loop(data->mlx.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	check_map_validity(argc, argv, &data);
	if (FOV < 20 || FOV > 120)
		ft_exit_error("FOV Recommended between 60-110", 1, &data);
	init_mlx(&data);
	init_textures(&data);
	init_player(&data);
	start_game(&data);
}
