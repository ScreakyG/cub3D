/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:25:28 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/03 18:23:33 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void ft_exit_error(char *msg, int exit_code, t_data *data)
{
	printf("Error\n");
	printf(RED "%s\n" RESET, msg);
	if (data != NULL)
	{
		if (data->map_tab)
		{
			free_strs(data->map_tab);
			printf("Freed data->map_tab memory\n");
		}
	}
	exit(exit_code);
}
