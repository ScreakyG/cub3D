/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:34:50 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/01 00:55:44 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_identifiers(t_data *data)
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

void print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_tab[i])
	{
		printf("%s\n", data->map_tab[i]);
		i++;
	}
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

void print_grid(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_grid[i])
	{
		printf("%s\n", data->map_grid[i]);
		i++;
	}
}

int	str_len_skip_ws(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	return (i);
}

int	get_player_number(t_data *data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	if (!data->map_grid)
		return (0);
	while (data->map_grid[y])
	{
		x = 0;
		while (data->map_grid[y][x])
		{
			if (data->map_grid[y][x] == 'N' || data->map_grid[y][x] == 'W' || 		data->map_grid[y][x] == 'S' ||data->map_grid[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

bool only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r')
			return (false);
		i++;
	}
	return (true);
}

void error_identifier_name(char *identifier, t_data *data)
{
	printf(RED"Unknown identifier : %s\n"RESET, identifier);
	free(identifier);
	ft_exit_error("", 1, data);
}

void error_identifier_value(char *identifier, t_data *data)
{
	printf(RED"No value for identifier : %s\n"RESET, identifier);
	free(identifier);
	ft_exit_error("", 1, data);
}

int	get_player_pos(t_data *data, char axis)
{
	int	x;
	int	y;
	char **map_grid;

	y = 0;
	map_grid = data->map_grid;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (map_grid[y][x] == 'N' || map_grid[y][x] == 'S' || map_grid[y][x] == 'W' || map_grid[y][x] == 'E')
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
