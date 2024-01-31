/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:16:42 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 14:48:50 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vect	vect_coord(double x, double y, double z)
{
	t_vect	vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	vect.magn = vect_magn(vect);
	vect.magn2 = vect_magn2(vect);
	return (vect);
}

t_vect	add_vect(t_vect v1, t_vect v2)
{
	t_vect	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	res.magn = vect_magn(res);
	res.magn2 = vect_magn2(res);
	return (res);
}

t_vect	sub_vect(t_vect v1, t_vect v2)
{
	t_vect	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	res.magn = vect_magn(res);
	res.magn2 = vect_magn2(res);
	return (res);
}

t_vect	cross_product(t_vect v1, t_vect v2)
{
	t_vect	cross_product;

	cross_product.x = v1.y * v2.z - v1.z * v2.y;
	cross_product.y = v1.z * v2.x - v1.x * v2.z;
	cross_product.z = v1.x * v2.y - v1.y * v2.x;
	cross_product.magn = vect_magn(cross_product);
	cross_product.magn2 = vect_magn2(cross_product);
	return (cross_product);
}

double	dot_product(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
