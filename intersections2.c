/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:08:00 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 15:08:33 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
