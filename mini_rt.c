/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:34:20 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/29 15:41:27 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "libftprintf/libft/libft.h"
#include <math.h>
#include <stdio.h>


double	cast_ray(t_scene scene, t_ray ray, int *hit_object, double threshhold)
{
	double			t;
	double			sol;
	int				i;

	t = -1;
	i = 0;
	while (scene.objectarray[i])
	{
		if (scene.objectarray[i]->type == SPHERE)
			sol = sphere_intersection(*scene.objectarray[i], ray);
		if (scene.objectarray[i]->type == PLANE)
			sol = plane_intersection(*scene.objectarray[i], ray);
		if (scene.objectarray[i]->type == CYLINDER)
			sol = cylinder_intersection(*scene.objectarray[i], ray);
		if ((t < 0 && sol > threshhold) || (sol < t && sol > threshhold))
		{
			*hit_object = i;
			t = sol;
		}
		i++;
	}
	return (t);	
}

double	cast_shadow_ray(t_scene scene, t_ray ray)
{
	double			sol;
	int				i;

	i = 0;
	sol = -1;
	while (scene.objectarray[i])
	{
		if (scene.objectarray[i]->type == SPHERE)
			sol = sphere_intersection(*scene.objectarray[i], ray);
		if (scene.objectarray[i]->type == PLANE)
			sol = plane_intersection(*scene.objectarray[i], ray);
		if (scene.objectarray[i]->type == CYLINDER)
			sol = cylinder_intersection(*scene.objectarray[i], ray);
		if (sol >= 0.0001 && sol <= point_dist(ray.origin, scene.light.center))
			return (sol);
		i++;
	}
	return (-1);	
}

t_vect	object_normal(t_object *object, t_point hit_point)
{
	t_vect	normal;

	if (object->type == SPHERE)
	{
		normal = vect_between_points(object->center, hit_point);
		normalize(&normal);
	}
	if (object->type == PLANE)
	{
		normal = object->orient;
	}
	return (normal);
}

double	darken_color(unsigned int color, int light_ratio)
{
	return  (((((color >> 16) & 255) * light_ratio / 100) << 16)
	+ ((((color >> 8) & 255) * light_ratio / 100) << 8)
	+ ((color & 255) * light_ratio / 100));	
}

int	cast_shadow(t_scene scene, int hit_object, t_point hit_point, unsigned int color)
{
	t_ray	shadow_ray;
	double	t;
	int		light_ratio;

	shadow_ray.origin = hit_point;
	shadow_ray.dir = vect_between_points(hit_point, scene.light.center);
	normalize(&shadow_ray.dir);
	t = cast_shadow_ray(scene, shadow_ray);
	light_ratio = 100 * dot_product(object_normal(scene.objectarray[hit_object], hit_point), shadow_ray.dir) * scene.light.brightness_ratio;
	if (light_ratio <= 100 * scene.alight_lighting_ratio)
		light_ratio = 100 * scene.alight_lighting_ratio;
	if (t <= 0.0001 ||  t >= point_dist(hit_point, scene.light.center))
		return (darken_color(color, light_ratio));
	return (darken_color(color, 100 * scene.alight_lighting_ratio));
}

t_ray	init_ray(t_scene scene, int i, int j)
{
	t_ray	ray;

	ray.dir.x = (2 * (i / (double)scene.size_x) - 1) * tan(((double)scene.camera.fov) * M_PI / 360) * ((double) scene.size_x / scene.size_y);
	ray.dir.y = (1 - 2 * (j / (double)scene.size_y)) * tan(((double)scene.camera.fov) * M_PI / 360);
	ray.dir.z = -1;
	ray.dir = matrix_product(scene.camera.c2w, ray.dir);
	ray.origin = scene.camera.origin;
	ray.dir.magn = vect_magn(ray.dir);
	ray.dir.magn2 = vect_magn2(ray.dir);
	normalize(&ray.dir);
	return (ray);
}

unsigned int	ray_color(t_scene scene, int i, int j)
{
	t_ray			ray;
	unsigned int	color;
	int				hit_object;
	t_point			hit_point;
	double			t;


	ray = init_ray(scene, i, j);
	hit_object = -1;
	color = 0;
	t = cast_ray(scene, ray, &hit_object, 1);
	if (hit_object >= 0)
	{
		color = scene.objectarray[hit_object]->color;
		hit_point.x = ray.origin.x + t * ray.dir.x;
		hit_point.y = ray.origin.y + t * ray.dir.y;
		hit_point.z = ray.origin.z + t * ray.dir.z;
		color = cast_shadow(scene, hit_object, hit_point, color);
	}
	else
		color = scene.alight_color;
	return (color);
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


int	main(int argc, char **argv)
{
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	image_init(argc, argv, &scene);
	draw(scene);
	mlx_hook(scene.mlx_w, 17, 0, win_close, &scene);
	mlx_loop(scene.mlx_p);
}
