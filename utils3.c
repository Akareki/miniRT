/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:19:29 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 14:48:29 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vect	scale_vect(double t, t_vect v)
{
	t_vect	res;

	res.x = t * v.x;
	res.y = t * v.y;
	res.z = t * v.z;
	res.magn = vect_magn(res);
	res.magn2 = vect_magn2(res);
	return (res);
}

void	normalize(t_vect *vect)
{
	if (vect->magn >= 0.0001)
	{
		vect->x = vect->x / vect->magn;
		vect->y = vect->y / vect->magn;
		vect->z = vect->z / vect->magn;
		vect->magn = 1;
		vect->magn2 = 1;
	}
}

t_point	point_coord(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vect	vect_between_points(t_point a, t_point b)
{
	t_vect	vect;

	vect = vect_coord(b.x - a.x, b.y - a.y, b.z - a.z);
	vect.magn = vect_magn(vect);
	vect.magn2 = vect_magn2(vect);
	return (vect);
}

t_vect	matrix_product(t_matrix m, t_vect v)
{
	t_vect	res;

	res.x = m.a[0][0] * v.x + m.a[0][1] * v.y + m.a[0][2] * v.z;
	res.y = m.a[1][0] * v.x + m.a[1][1] * v.y + m.a[1][2] * v.z;
	res.z = m.a[2][0] * v.x + m.a[2][1] * v.y + m.a[2][2] * v.z;
	return (res);
}
