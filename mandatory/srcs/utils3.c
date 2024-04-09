/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:23:37 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 00:48:59 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*fill_color_buffer(t_texture *texture, int *addr)
{
	int	y;
	int	x;
	int	*clr_buf;

	y = 0;
	x = 0;
	clr_buf = malloc(sizeof(int) * (texture->width * texture->height));
	if (!clr_buf)
		return (NULL);
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			clr_buf[(y * texture->width) + x] = addr[(y * texture->width) + x];
			x++;
		}
		y++;
	}
	return (clr_buf);
}

void	init_img(t_img *img)
{
	img->addr = NULL;
	img->img = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->line_length = 0;
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

void	error_identifier_name(char *identifier, t_data *data)
{
	printf(RED"Unknown identifier : %s\n"RESET, identifier);
	free(identifier);
	ft_exit_error("", 1, data);
}

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_tab[i])
	{
		printf("%s\n", data->map_tab[i]);
		i++;
	}
}
