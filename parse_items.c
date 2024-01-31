/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:35:04 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 13:31:21 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	parse_cy(t_scene *s, char **buf_t, size_t i, size_t j)
{
	char	**t;

	s->objectarray[j].type = CYLINDER;
	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].center.x = ft_atof(t[0]);
	s->objectarray[j].center.y = ft_atof(t[1]);
	s->objectarray[j].center.z = ft_atof(t[2]);
	free_ft_split(t);
	t = ft_split(buf_t[i + 2], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].orient.x = ft_atof(t[0]);
	s->objectarray[j].orient.y = ft_atof(t[1]);
	s->objectarray[j].orient.z = ft_atof(t[2]);
	free_ft_split(t);
	s->objectarray[j].radius = ft_atof(buf_t[i + 3]) / 2;
	s->objectarray[j].radius2 = s->objectarray[j].radius * s->objectarray[j].radius;
	s->objectarray[j].height = ft_atof(buf_t[i + 4]);
	t = ft_split(buf_t[i + 5], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
}

int	parse_pl(t_scene *s, char **buf_t, size_t i, size_t j)
{
	char	**t;

	s->objectarray[j].type = PLANE;
	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].center.x = ft_atof(t[0]);
	s->objectarray[j].center.y = ft_atof(t[1]);
	s->objectarray[j].center.z = ft_atof(t[2]);
	free_ft_split(t);
	t = ft_split(buf_t[i + 2], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].orient.x = ft_atof(t[0]);
	s->objectarray[j].orient.y = ft_atof(t[1]);
	s->objectarray[j].orient.z = ft_atof(t[2]);
	free_ft_split(t);
	t = ft_split(buf_t[i + 3], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
}

int	parse_sp(t_scene *s, char **buf_t, size_t i, size_t j)
{
	char	**t;

	s->objectarray[j].type = SPHERE;
	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].center.x = ft_atof(t[0]);
	s->objectarray[j].center.y = ft_atof(t[1]);
	s->objectarray[j].center.z = ft_atof(t[2]);
	free_ft_split(t);
	s->objectarray[j].radius = ft_atof(buf_t[i + 2]) / 2;
	s->objectarray[j].radius2 = s->objectarray[j].radius * s->objectarray[j].radius;
	t = ft_split(buf_t[i + 3], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->objectarray[j].color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
	return (0);
}

int	parse_light(t_scene *s, char **buf_t, size_t i)
{
	char	**t;

	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->light.center.x = ft_atof(t[0]);
	s->light.center.y = ft_atof(t[1]);
	s->light.center.z = ft_atof(t[2]);
	free_ft_split(t);
	s->light.brightness_ratio = ft_atof(buf_t[i + 2]);
	t = ft_split(buf_t[i + 3], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->light.color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
	return (0);
}

int	parse_camera(t_scene *s, char **buf_t, size_t i)
{
	char	**t;

	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->camera.origin = point_coord(ft_atof(t[0]), ft_atof(t[1]), ft_atof(t[2]));
	free_ft_split(t);
	t = ft_split(buf_t[i + 2], ',');
	if (!t)
		return (free(s->objectarray), free(s), free_ft_split(buf_t), -1);
	s->camera.orient = vect_coord(ft_atof(t[0]), ft_atof(t[1]), ft_atof(t[2]));
	normalize(&s->camera.orient);
	free_ft_split(t);
	s->camera.fov = ft_atoi(buf_t[i + 3]);
	return (0);
}
