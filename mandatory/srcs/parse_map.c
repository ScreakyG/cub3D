/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:34 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 01:36:44 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	characters_check(char *str)
{
	int		i;
	int		j;
	bool	found;
	char	*charset;

	charset = "01NWSE \t\r";
	i = 0;
	while (str[i])
	{
		j = -1;
		found = false;
		while (charset[++j])
		{
			if (str[i] == charset[j])
			{
				found = true;
				break ;
			}
		}
		if (found == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	verify_top_line(char *str)
{
	int	i;
	int	wall_nb;

	i = 0;
	wall_nb = 0;
	if (!str || !str[i])
		return (false);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
			i++;
		if (str[i] == '1')
			wall_nb++;
		else if (str[i] == '\0' && wall_nb > 1)
			return (true);
		else if (str[i] != '1')
			return (false);
		i++;
	}
	if (wall_nb > 1)
		return (true);
	else
		return (false);
}

static bool	verify_bottom_line(char *str)
{
	int	i;
	int	wall_nb;

	i = 0;
	wall_nb = 0;
	if (!str || str[i] == '\0')
		return (false);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
			i++;
		if (str[i] == '1')
			wall_nb++;
		else if (str[i] == '\0' && wall_nb > 1)
			return (true);
		else if (str[i] != '1')
			return (false);
		i++;
	}
	if (wall_nb > 1)
		return (true);
	else
		return (false);
}

void	check_if_closed_map(t_data *data)
{
	if (data->idx_map_end - data->idx_map_start < 3)
		ft_exit_error("Map miniumum size is 3 lines", 1, data);
	if (verify_top_line(data->map_tab[data->idx_map_start]) == false)
		ft_exit_error("Top of map not closed", 1, data);
	if (verify_left_side(data) == false)
		ft_exit_error("Sides not closed", 1, data);
	if (verify_right_side(data) == false)
		ft_exit_error("Sides not closed", 1, data);
	if (verify_bottom_line(data->map_tab[data->idx_map_end - 1]) == false)
		ft_exit_error("Bottom of map not closed", 1, data);
}

void	parse_map(t_data *data)
{
	int	i;

	skip_white_lines(data);
	i = data->idx_map_start;
	while (data->map_tab[i])
	{
		if (characters_check(data->map_tab[i]) == false)
			ft_exit_error("Invalid characters in map", 1, data);
		i++;
	}
	get_map_end_idx(data);
	check_if_closed_map(data);
	create_map_grid(data);
}
