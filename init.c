/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:21:07 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 15:25:56 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix	c2w_matrix(t_camera camera)
{
	t_vect		vert;
	t_vect		right;
	t_vect		up;
	t_matrix	c2w;

	vert = vect_coord(0, 1, 0);
	right = cross_product(camera.orient, vert);
	if (right.magn < 0.0001)
		right = vect_coord(1, 0, 0);
	normalize(&right);
	up = cross_product(right, camera.orient);
	normalize(&up);
	c2w.a[0][0] = right.x;
	c2w.a[1][0] = right.y;
	c2w.a[2][0] = right.z;
	c2w.a[0][1] = up.x;
	c2w.a[1][1] = up.y;
	c2w.a[2][1] = up.z;
	c2w.a[0][2] = -camera.orient.x;
	c2w.a[1][2] = -camera.orient.y;
	c2w.a[2][2] = -camera.orient.z;
	return (c2w);
}

int	init_scene(int argc, char **argv, t_scene *scene)
{
	scene->size_x = 1920;
	scene->size_y = 1080;
	scene->camera.c2w = c2w_matrix(scene->camera);
	return (1);
}

int	image_init(int argc, char **argv, t_scene *scene)
{
	void		*mlx_p;
	void		*mlx_w;
	void		*mlx_i;

	mlx_p = mlx_init();
	if (!mlx_p)
		win_close(scene);
	scene->mlx_p = mlx_p;
	init_scene(argc, argv, scene);
	mlx_w = mlx_new_window(mlx_p, scene->size_x, scene->size_y,
			"mini_rt");
	if (!mlx_w)
		win_close(scene);
	scene->mlx_w = mlx_w;
	mlx_i = mlx_new_image(mlx_p, scene->size_x, scene->size_y);
	if (!mlx_i)
		win_close(scene);
	scene->mlx_i = mlx_i;
	return (0);
}
