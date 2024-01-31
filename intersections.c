/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:23:12 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/29 15:34:39 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

double	valid_intersection(double a, double b, double c, double delta)
{
	double	sol1;
	double	sol2;

	sol1 = (- b - sqrt(delta)) / 2 * a;
	sol2 = (- b + sqrt(delta)) / 2 * a;
	if (sol1 >= 0.0001)
		return (sol1);
	if (sol2 >= 0.0001)
		return (sol2);
	return (-1);
}

double	cylinder_intersection(t_object cylinder, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol;

	sol = -1;
	a = vect_magn2(cross_product(ray.dir, cylinder.orient));
	b = 2 * dot_product(cross_product(vect_between_points(point_coord(0, 0, 0), ray.origin), cylinder.orient), cross_product(ray.dir, cylinder.orient));
	c = vect_magn2(cross_product(vect_between_points(point_coord(0, 0, 0), ray.origin), cylinder.orient)) - cylinder.radius2;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
		sol = valid_intersection(a, b, c, delta);
	return (sol);
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
		sol = valid_intersection(a, b, c, delta);
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

