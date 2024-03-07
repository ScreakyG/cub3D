/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:25:04 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/07 19:44:48 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool is_directory(char *filename)
{
	int	tmp_fd;

	tmp_fd = open(filename, __O_DIRECTORY);
	if (tmp_fd >= 0)
	{
		close (tmp_fd);
		return (true);
	}
	return (false);
}

static void get_map(char *map_arg, t_data *data)
{
	int 	map_fd;
	char	*line;
	int		i;

	i = 0;
	map_fd = open(map_arg, O_RDONLY);
	if (map_fd == -1)
		ft_exit_error(strerror(errno), errno, NULL); //Data ne contient rien de malloc a ce stade.
	data->map_tab = malloc((get_number_lines(map_arg) + 1) * sizeof(char *));
	if (!data->map_tab)
	{
		close(map_fd);
		ft_exit_error("Map copy failed", 1, data);
	}
	line = get_next_line(map_fd);
	while (line)
	{
		data->map_tab[i] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	data->map_tab[i] = NULL;
	close(map_fd);
}

static void	check_file_extension(char **argv)
{
	int	end;

	if (!argv || !argv[1])
		ft_exit_error("Error with argv", 1, NULL);
	if (ft_strlen(argv[1]) < 4)
		ft_exit_error("Error with map extension, use .cub extension", 1, NULL);
	end = ft_strlen(argv[1]);
	end -= 4;
	if (ft_strncmp(&argv[1][end], ".cub", ft_strlen(&argv[1][end])))
		ft_exit_error("Error with map extension, use .cub extension", 1, NULL);
	if (is_directory(argv[1]))
		ft_exit_error("Map file is a directory", 1, NULL);
}

void	check_map_validity(int argc, char **argv, t_data *data)
{
	if (argc != 2)
		ft_exit_error("Please use a .cub map as argument : ./cub3D map.cub", 1, data);
	check_file_extension(argv);
	get_map(argv[1], data);
	parse_identifiers(data);
	parse_map(data);


	//print_identifiers(data);
	//print_map(data);
}
