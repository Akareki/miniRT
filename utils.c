/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:13:20 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/29 08:20:20 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	vect_magn(t_vect vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

double	vect_magn2(t_vect vect)
{
	return (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}

double	double_max(double a, double b)
{
	return ((a >= b) * a + (a < b) * b);
}

double	point_dist(t_point a, t_point b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
}

double	point_dist2(t_point a, t_point b)
{
	return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

