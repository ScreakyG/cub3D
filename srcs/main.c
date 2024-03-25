/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:38 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/25 09:51:52 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(void *data)
{
	t_data *data_ptr;

	data_ptr = (t_data *)data;
	mlx_pixel_put(data_ptr->mlx.mlx_ptr, data_ptr->mlx.mlx_win, 100, 100, data_ptr->c_hex);
	return (0);
}

void start_game(t_data *data)
{
	mlx_loop_hook(data->mlx.mlx_ptr, &game_loop, data);
	mlx_hook(data->mlx.mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx.mlx_ptr);
}

int main(int argc, char **argv)
{
	t_data data;

	data = (t_data){0};
	check_map_validity(argc, argv, &data); // choses a verifier.
	//verifier la resolution, le fov , speed , la position du joueur.
	init_textures(&data);

	init_mlx(&data);

	start_game(&data);

	//clean_exit(&data);
}
