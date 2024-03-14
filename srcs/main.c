/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:38 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/14 14:54:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_data data;
	
	data.map_tab = NULL;
	data.map_grid = NULL;
	data.idx_map_start = 0;
	data.idx_map_end = 0;
	data.height = 0;
	data.width = 0;
	data.no = NULL;
	data.so = NULL;
	data.we = NULL;
	data.ea = NULL;
	data.f = NULL;
	data.c = NULL;
	data.mlx.mlx_ptr = NULL;
	data.mlx.mlx_win = NULL;

	check_map_validity(argc, argv, &data); // choses a verifier.
	//verifier la resolution, le fov , speed , la position du joueur.
	init_mlx(&data);
	//init_textures(&data);
	ft_exit_error("ALL GOOD", 0, &data);
}
