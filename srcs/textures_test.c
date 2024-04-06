/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:30:35 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/05 23:04:13 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void textures_test(t_data *data)
{
	(void)data;
	uint32_t *wallTexture;

	wallTexture = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)TEXTURE_SIZE * (uint32_t)TEXTURE_SIZE);
	if (!wallTexture)
	{
		printf("Error malloc wall texture\n");
		exit(12);
	}
	for (int x = 0; x < TEXTURE_SIZE; x++)
		for (int y = 0; y < TEXTURE_SIZE; y++)
			wallTexture[(TEXTURE_SIZE * y) + x] = (x % 8 && y % 8) ? 0xFF0000FF : 0xFF000000;
	data->wall_texture_test = wallTexture;
}
