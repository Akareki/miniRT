/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:23:12 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 10:41:20 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

double	sphere_valid_intersection(double a, double b, double c, double delta)
{
	double	sol1;
	double	sol2;

	sol1 = (- b - sqrt(delta)) / (2 * a);
	sol2 = (- b + sqrt(delta)) / (2 * a);
	if (sol1 >= 0.0001)
		return (sol1);
	if (sol2 >= 0.0001)
		return (sol2);
	return (-1);
}

double	cylinder_caps_intersection(double sol, t_object cylinder, t_ray ray)
{
	t_point	cap_center;
	double	t;

	cap_center = point_origin_scale_dir(cylinder.center, cylinder.height / 2, cylinder.orient);
	if (fabs(dot_product(ray.dir, cylinder.orient)) >= 0.0001)
	{
		t = dot_product(vect_between_points(ray.origin, cap_center), cylinder.orient) / dot_product(ray.dir, cylinder.orient);
		if ((t <= sol || sol < 0) && t >= 0.0001 && point_dist2(cap_center, point_origin_scale_dir(ray.origin, t, ray.dir)) <= cylinder.radius2)
			sol = t;
	}
	cap_center = point_origin_scale_dir(cylinder.center, -cylinder.height / 2, cylinder.orient);
	if (fabs(dot_product(ray.dir, cylinder.orient)) >= 0.0001)
	{
		t = dot_product(vect_between_points(ray.origin, cap_center), cylinder.orient) / dot_product(ray.dir, cylinder.orient);
		if ((t <= sol || sol < 0) && t >= 0.0001 && point_dist2(cap_center, point_origin_scale_dir(ray.origin, t, ray.dir)) <= cylinder.radius2)
			sol = t;
	}
	return sol;
}

double	cylinder_valid_intersection(double a[3], t_object cylinder, t_ray ray)
{
	double	sol1;
	double	sol2;
	double	delta;
	double	t;

	delta = a[1] * a[1] - 4 * a[2] * a[0];
	if (delta < 0)
		return (-1);
	sol1 = (- a[1] - sqrt(delta)) / (2 * a[2]);
	sol2 = (- a[1] + sqrt(delta)) / (2 * a[2]);
	if (sol1 >= 0.0001)
	{
		t = sol1 * dot_product(cylinder.orient, ray.dir) + dot_product(cylinder.orient,
				vect_between_points(cylinder.center, ray.origin));
		if (t > (- cylinder.height / 2) && t < cylinder.height / 2)
			return (sol1);
	}
	if (sol2 >= 0.0001)
	{
		t = sol2 * dot_product(cylinder.orient, ray.dir) + dot_product(cylinder.orient,
				vect_between_points(cylinder.center, ray.origin));
		if (t > (- cylinder.height / 2) && t < cylinder.height / 2)
			return (sol2);
	}
	return (-1);
}


double	cylinder_intersection(t_object cylinder, t_ray ray)
{
	double	a[3];
	double	delta;
	double	sol;

	sol = -1;
	a[2] = cross_product(ray.dir, cylinder.orient).magn2;
	a[1] = 2 * dot_product(cross_product(vect_between_points(cylinder.center, ray.origin), cylinder.orient), cross_product(ray.dir, cylinder.orient));
	a[0] = cross_product(vect_between_points(cylinder.center, ray.origin), cylinder.orient).magn2 - cylinder.radius2;
	sol = cylinder_valid_intersection(a, cylinder, ray);
	return (cylinder_caps_intersection(sol, cylinder, ray));
}

double	sphere_intersection(t_object sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol;

	sol = -1;
	a = ray.dir.magn2;
	b = 2 * dot_product(vect_between_points(sphere.center, ray.origin), ray.dir);
	c = point_dist2(sphere.center, ray.origin) - sphere.radius2;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
		sol = sphere_valid_intersection(a, b, c, delta);
	return (sol);
}

double	plane_intersection(t_object plane, t_ray ray)
{
	t_vect	po;
	double	dot_p;

	po = vect_between_points(ray.origin, plane.center);
	dot_p = dot_product(ray.dir, plane.orient);
	if (dot_p <= 0.0001 && dot_p >= -0.0001)
		return (-1);
	return (dot_product(po, plane.orient) / dot_p);
}

