/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:34:50 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/09 16:44:16 by fgonzale         ###   ########.fr       */
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
