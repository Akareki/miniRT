/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:34:20 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/26 13:29:08 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "libftprintf/libft/libft.h"
#include <math.h>
#include <stdio.h>

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

void	add_to_objectlst(t_scene *scene, t_object *object)
{
	t_object	*last_object;

	last_object = scene->objectlst;
	if (!last_object)
	{
		scene->objectlst = object;
		return ;
	}
	while (last_object->next)
		last_object = last_object->next;
	last_object->next = object;
}

int	init_objects(int argc, char **argv, t_scene *scene)
{
	t_object	*sphere;
	int			i;

	i = 1;
	while (argv[i])
	{
		sphere = ft_calloc(1, sizeof(t_object));
		sphere->center.x = ft_atoi(argv[i]);
		sphere->center.y = ft_atoi(argv[i + 1]);
		sphere->center.z = ft_atoi(argv[i + 2]);
		sphere->radius = ft_atoi(argv[i + 3]);
		sphere->radius2 = sphere->radius * sphere->radius;
		sphere->color = ft_atoi(argv[i + 4]);
		sphere->next = NULL;
		add_to_objectlst(scene, sphere);	
		i += 5;
	}
	return (0);
}

int	init_scene(int argc, char **argv, t_scene *scene)
{
	scene->size_x = 500;
	scene->size_y = 500;
	scene->camera.origin.x = 10;
	scene->camera.origin.y = 0;
	scene->camera.origin.z = 0;
	scene->camera.orient.x = -1;
	scene->camera.orient.y = 0;
	scene->camera.orient.z = 0;
	scene->camera.fov = 160;
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

double	vect_magn(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	vect_magn2(double x, double y, double z)
{
	return (x * x + y * y + z * z);
}

double	double_max(double a, double b)
{
	return ((a >= b) * a + (a < b) * b);
}

double	sphere_intersection(t_scene scene, t_object sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol;

	sol = -1;
	a = ray.magn2;
	b = 2 * ((sphere.center.x - scene.camera.origin.x) * ray.dir.x
		  + (sphere.center.y - scene.camera.origin.y) * ray.dir.y
		  + (sphere.center.z - scene.camera.origin.z) * ray.dir.z);
	c = vect_magn2(sphere.center.x - scene.camera.origin.x, sphere.center.y - scene.camera.origin.y ,sphere.center.z - scene.camera.origin.z) - sphere.radius2;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
		sol = (- b - sqrt(delta)) / 2 * a;
	return (sol);
}

int	cast_ray(t_scene scene, t_ray ray)
{
	t_object		*object;
	double			t;
	double			sol;
	unsigned int	color;

	t = 1000000000;
	color = 0;
	object = scene.objectlst;
	while (object)
	{
		sol = sphere_intersection(scene, *object, ray);
		if (sol < t && sol > 1)
		{
			t = sol;
			color = object->color;
		}
		object = object->next;
	}
	return (color);	
}

unsigned int	ray_color(t_scene scene, unsigned int i, unsigned int j)
{
	t_ray	ray;
	double	alpha;
	double	beta;

	alpha = atan(scene.camera.orient.y / sqrt(scene.camera.orient.x * scene.camera.orient.x + scene.camera.orient.z * scene.camera.orient.z));
	beta = M_PI_2;
	if (scene.camera.orient.z >= 0.0001 || scene.camera.orient.z <= 0.0001)
		beta = M_PI_2 - atan(scene.camera.orient.x / scene.camera.orient.z);
	ray.origin = scene.camera.origin;
	ray.dir.x = cos(beta) * (2 * (i / (double)scene.size_x) - 1) * (scene.size_x / (double)scene.size_y) * tan(((double)scene.camera.fov) * M_PI / 360) - sin(beta) + scene.camera.origin.x;
	ray.dir.y = sin(alpha) * sin(beta) * (2 * (i / (double)scene.size_x) - 1) * ((double)scene.size_x / scene.size_y) * tan(((double)scene.camera.fov) * M_PI / 360) 
				+ cos(alpha) * (1 - 2 * (j / (double)scene.size_y)) * tan(((double)scene.camera.fov) * M_PI / 360) + sin(alpha) * cos(beta) + scene.camera.origin.y;
	ray.dir.z = -cos(alpha) * sin(beta) * (2 * (i / (double)scene.size_x) - 1) * ((double)scene.size_x / scene.size_y) * tan(((double)scene.camera.fov) * M_PI / 360) 
				+ sin(alpha) * (1 - 2 * (j / (double)scene.size_y)) * tan(((double)scene.camera.fov) * M_PI / 360) - cos(alpha) * cos(beta) + scene.camera.origin.z;
	ray.magn = vect_magn(ray.dir.x, ray.dir.y, ray.dir.z);
	ray.magn2 = vect_magn2(ray.dir.x, ray.dir.y, ray.dir.z);
	//printf("Alpha %f Beta %f Ray %d %d x : %f y : %f z : %f\n",alpha, beta, i, j, ray.dir.x, ray.dir.y, ray.dir.z);
	return (cast_ray(scene, ray));
}

void	draw(t_scene scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < scene.size_y)
	{
		i = 0;
		while (i < scene.size_x)
		{
			put_pixel_in_img(scene, i, j, ray_color(scene, i, j));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(scene.mlx_p,
		scene.mlx_w, scene.mlx_i, 0, 0);
}


/*int	main(int argc, char **argv)
{
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	image_init(argc, argv, &scene);
	draw(scene);
	mlx_hook(scene.mlx_w, 17, 0, win_close, &scene);
	mlx_loop(scene.mlx_p);
}*/
