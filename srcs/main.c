/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:38 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/03 21:04:53 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_data data;
	data = (t_data){0};


	check_map_validity(argc, argv, &data);
	ft_exit_error("ALL GOOD", 0, &data);
}
