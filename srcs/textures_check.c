/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:12:52 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/13 18:40:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void check_permissions(char *filename, t_data *data)
{
	int	tmp_fd;

	tmp_fd = open(filename, O_RDONLY);
	if (tmp_fd == -1)
	{
		//printf("%s : ", filename);
		ft_exit_error(strerror(errno), errno, data);
	}
	else
		close(tmp_fd);
}

static void check_texture_file(char *filename, t_data *data)
{
	int	end;
	
	if (!filename || filename[0] == '\0')
		ft_exit_error("Error with texture file", 1 ,data);
	if (ft_strlen(filename) < 4)
		ft_exit_error("File is not 'xpm' extension", 1, data);
	end = ft_strlen(filename);
	end -= 4;
	if (ft_strncmp(&filename[end], ".xpm", ft_strlen(&filename[end])))
		ft_exit_error("File is not 'xpm' extension", 1, data);
	if (is_directory(filename))
		ft_exit_error("A texture file is a diretory", 1 ,data);
	check_permissions(filename, data);
}

void verify_textures(t_data *data)
{
	check_texture_file(data->no, data);
	check_texture_file(data->so, data);
	check_texture_file(data->ea, data);
	check_texture_file(data->we, data);
}