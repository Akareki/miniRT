/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:21:07 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/29 15:38:50 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf/libft/libft.h"
#include "mini_rt.h"

int	init_objects(int argc, char **argv, t_scene *scene)
{
	t_object	*sphere;
	t_object	*plane;
	int			i;
	int			j;

	i = 1;
	j = 0;
	scene->objectarray = ft_calloc(argc + 3, sizeof(t_object *));
	while (argv[i])
	{
		sphere = ft_calloc(1, sizeof(t_object));
		sphere->type = SPHERE;
		sphere->center.x = ft_atoi(argv[i]);
		sphere->center.y = ft_atoi(argv[i + 1]);
		sphere->center.z = ft_atoi(argv[i + 2]);
		sphere->radius = ft_atoi(argv[i + 3]);
		sphere->radius2 = sphere->radius * sphere->radius;
		sphere->color = (255 << (8 * ((i / 4) % 3))) + (127 << (8 * ((i / 4) % 6))) + (63 << (8 * ((i / 4) % 12)));
		scene->objectarray[j] = sphere;
		i += 4;
		j++;
	}
	plane = ft_calloc(1, sizeof(t_object));
	plane->type = PLANE;
	plane->center.x = 0;
	plane->center.y = 0.5;
	plane->center.z = 0;
	plane->orient.x = 0;
	plane->orient.y = 1;
	plane->orient.z = 0;
	plane->color = 255255;
	normalize(&plane->orient);
	scene->objectarray[j] = plane;
	plane = ft_calloc(1, sizeof(t_object));
	plane->type = CYLINDER;
	plane->center.x = 0;
	plane->center.y = 0;
	plane->center.z = 0;
	plane->orient.x = 0;
	plane->orient.y = 1;
	plane->orient.z = 0;
	plane->color = 0x00FF0000;
	plane->radius = 1;
	plane->radius2 = 1;
	normalize(&plane->orient);
	scene->objectarray[j + 1] = plane;
	return (0);
}

t_matrix	c2w_matrix(t_camera camera)
{
	t_vect		vert;
	t_vect		right;
	t_vect		up;
	t_matrix	c2w;

	vert = vect_coord(0, 1, 0);
	right = cross_product(camera.orient, vert);
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
	scene->camera.origin = point_coord(10, 10, 10);
	scene->camera.orient = vect_coord(-1, -1, -1);
	scene->light.center = point_coord(7, 7, 7);
	scene->light.brightness_ratio = 0.8;
	scene->alight_color = 0x00777777;
	scene->alight_lighting_ratio = 0.2;
	normalize(&scene->camera.orient);
	scene->camera.fov = 90;
	scene->camera.c2w = c2w_matrix(scene->camera);
	init_objects(argc, argv, scene);
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

