/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:14:39 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/29 08:14:50 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	put_pixel_in_img(t_scene scene, unsigned int i,
					unsigned int j, unsigned int color)
{
	int				bits_pixel;
	int				size_line;
	int				endian;
	char			*img;

	img = mlx_get_data_addr(scene.mlx_i, &bits_pixel, &size_line, &endian);
	if (endian == 0)
	{
		img[4 * i + 0 + size_line * j] = color & 0xff;
		img[4 * i + 1 + size_line * j] = (color >> 8) & 0xff ;
		img[4 * i + 2 + size_line * j] = (color >> 16) & 0xff;
	}
	if (endian == 1)
	{
		img[4 * i + 3 + size_line * j] = color & 0xff;
		img[4 * i + 2 + size_line * j] = (color >> 8) & 0xff ;
		img[4 * i + 1 + size_line * j] = (color >> 16) & 0xff;
	}
}

int	win_close(t_scene *scene)
{
	if (scene->mlx_i)
		mlx_destroy_image(scene->mlx_p, scene->mlx_i);
	if (scene->mlx_w)
		mlx_destroy_window(scene->mlx_p, scene->mlx_w);
	if (scene->mlx_p)
	{
		mlx_destroy_display(scene->mlx_p);
		free(scene->mlx_p);
	}
	exit(0);
}
