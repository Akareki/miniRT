/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:50:22 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 16:01:00 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	cast_ray(t_scene scene, t_ray ray, int *hit_object, double threshhold)
{
	double			t;
	double			sol;
	int				i;

	t = -1;
	i = 0;
	while (i < scene.nb_objects)
	{
		if (scene.objectarray[i].type == SPHERE)
			sol = sphere_intersection(scene.objectarray[i], ray);
		if (scene.objectarray[i].type == PLANE)
			sol = plane_intersection(scene.objectarray[i], ray);
		if (scene.objectarray[i].type == CYLINDER)
			sol = cylinder_intersection(scene.objectarray[i], ray);
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
	while (i < scene.nb_objects)
	{
		if (scene.objectarray[i].type == SPHERE)
			sol = sphere_intersection(scene.objectarray[i], ray);
		if (scene.objectarray[i].type == PLANE)
			sol = plane_intersection(scene.objectarray[i], ray);
		if (scene.objectarray[i].type == CYLINDER)
			sol = cylinder_intersection(scene.objectarray[i], ray);
		if (sol >= 0.0001 && sol <= point_dist(ray.origin, scene.light.center))
			return (sol);
		i++;
	}
	return (-1);
}

t_vect	cylinder_normal(t_object cylinder, t_point hit_point)
{
	t_vect	normal;

	if (cross_product(vect_between_points(cylinder.center, hit_point),
			cylinder.orient).magn < cylinder.radius - 0.0001)
	{
		if (dot_product(cylinder.orient, vect_between_points(cylinder.center,
					hit_point)) > 0.0001)
			normal = cylinder.orient;
		if (dot_product(cylinder.orient, vect_between_points(cylinder.center,
					hit_point)) < -0.0001)
			normal = scale_vect(-1, cylinder.orient);
		normalize(&normal);
		return (normal);
	}
	normal = sub_vect(vect_between_points(cylinder.center, hit_point),
			scale_vect(dot_product(vect_between_points(cylinder.center,
						hit_point), cylinder.orient), cylinder.orient));
	normalize(&normal);
	return (normal);
}

t_vect	object_normal(t_scene scene, t_object object, t_point hit_point)
{
	t_vect	normal;

	if (object.type == SPHERE)
	{
		normal = vect_between_points(object.center, hit_point);
		if (point_dist(scene.camera.origin, object.center) <= object.radius)
			normal = scale_vect(-1, normal);
		normalize(&normal);
	}
	if (object.type == PLANE)
	{
		normal = object.orient;
		if (dot_product(object.orient, vect_between_points(scene.camera.origin,
					object.center)) > 0.0001)
			normal = scale_vect(-1, normal);
	}
	if (object.type == CYLINDER)
	{
		normal = cylinder_normal(object, hit_point);
	}
	return (normal);
}

double	darken_color(unsigned int color, int light_ratio)
{
	return (((((color >> 16) & 255) * light_ratio / 1000) << 16)
		+ ((((color >> 8) & 255) * light_ratio / 1000) << 8)
		+ ((color & 255) * light_ratio / 1000));
}
