/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:08:25 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 10:10:09 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_point	point_origin_scale_dir(t_point origin, double scale, t_vect dir)
{
	t_point	point;

	point.x = origin.x + scale * dir.x;
	point.y = origin.y + scale * dir.y;
	point.z = origin.z + scale * dir.z;
	return (point);
}
