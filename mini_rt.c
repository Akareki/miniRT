/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:34:20 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 15:55:44 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	cast_shadow(t_scene scene, int hit_object,
				t_point hit_point, unsigned int color)
{
	t_ray	shadow_ray;
	double	t;
	int		light_ratio;

	shadow_ray.origin = hit_point;
	shadow_ray.dir = vect_between_points(hit_point, scene.light.center);
	normalize(&shadow_ray.dir);
	t = cast_shadow_ray(scene, shadow_ray);
	light_ratio = 1000
		* dot_product(object_normal(scene,
				scene.objectarray[hit_object], hit_point), shadow_ray.dir)
		* scene.light.brightness_ratio;
	if (light_ratio <= 1000 * scene.alight_lighting_ratio)
		light_ratio = 1000 * scene.alight_lighting_ratio;
	if (t <= 0.0001 || t >= point_dist(hit_point, scene.light.center))
		return (darken_color(color, light_ratio));
	return (darken_color(color, 1000 * scene.alight_lighting_ratio));
}

t_ray	init_ray(t_scene scene, int i, int j)
{
	t_ray	ray;

	ray.dir.x = (2 * (i / (double)scene.size_x) - 1)
		* tan(((double)scene.camera.fov) * M_PI / 360)
		* ((double) scene.size_x / scene.size_y);
	ray.dir.y = (1 - 2 * (j / (double)scene.size_y))
		* tan(((double)scene.camera.fov) * M_PI / 360);
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
		color = scene.objectarray[hit_object].color;
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
	t_scene	*scene;

	scene = parse(argv[1]);
	if (!scene)
		return (1);
	image_init(argc, argv, scene);
	draw(*scene);
	mlx_hook(scene->mlx_w, 17, 0, win_close, scene);
	mlx_loop(scene->mlx_p);
}
