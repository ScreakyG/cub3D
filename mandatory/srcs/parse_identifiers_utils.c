/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:25:31 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/14 22:04:08 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_identifier_name(t_data *data, char **map_tab, int *j)
{
	char	*name;
	int		word_start;

	word_start = *j;
	while (map_tab[0][*j] && (map_tab[0][*j] != ' '
		&& map_tab[0][*j] != '\t' && map_tab[0][*j] != '\r'))
		(*j)++;
	name = ft_substr(map_tab[0], word_start, *j - word_start);
	if (word_is_identifier(name, data) == false)
		error_identifier_name(name, data);
	if (map_tab[0][*j] == '\0' || is_empty(&map_tab[0][*j]))
		error_identifier_value(name, data);
	return (name);
}

void	get_identifier_value(t_data *data, char **map_tab,
			int value_start, char *identifier)
{
	int		j;
	char	*value;

	j = value_start;
	if (map_tab[0] == NULL)
	{
		free(identifier);
		ft_exit_error("Error while parsing identifiers", 1, data);
	}
	while (map_tab[0][j])
		j++;
	value = ft_substr(map_tab[0], value_start, j - value_start);
	add_value_to_identifier(value, identifier, data);
	free(value);
	free(identifier);
}
