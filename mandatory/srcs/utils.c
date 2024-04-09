/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:34:50 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 00:24:42 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_identifiers(t_data *data)
{
	if (data->no != NULL)
		printf("%s\n", data->no);
	if (data->so != NULL)
		printf("%s\n", data->so);
	if (data->we != NULL)
		printf("%s\n", data->we);
	if (data->ea != NULL)
		printf("%s\n", data->ea);
	if (data->f != NULL)
		printf("%s\n", data->f);
	if (data->c != NULL)
		printf("%s\n", data->c);
}

int	get_number_lines(char *map_arg)
{
	int		map_fd;
	int		number;
	char	*line;

	map_fd = open(map_arg, O_RDONLY);
	if (map_fd == -1)
		ft_exit_error(strerror(errno), errno, NULL);
	number = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		number++;
		free(line);
		line = get_next_line(map_fd);
	}
	close (map_fd);
	return (number);
}

void	print_grid(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_grid[i])
	{
		printf("%s\n", data->map_grid[i]);
		i++;
	}
}

int	get_player_pos(t_data *data, char axis)
{
	int		x;
	int		y;
	char	**map_grid;

	y = 0;
	map_grid = data->map_grid;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (map_grid[y][x] == 'N' || map_grid[y][x] == 'S'
			|| map_grid[y][x] == 'W' || map_grid[y][x] == 'E')
			{
				if (axis == 'x')
					return (x);
				else if (axis == 'y')
					return (y);
			}
			x++;
		}
		y++;
	}
	return (0);
}
