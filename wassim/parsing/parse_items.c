/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:35:04 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 11:37:57 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

int	parse_cy(t_scene *s, char **buf_t, size_t i, size_t j)
{
	char	**t;

	s->objectlst[j].type = CYLINDER;
	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].center.x = ft_atof(t[0]);
	s->objectlst[j].center.y = ft_atof(t[1]);
	s->objectlst[j].center.z = ft_atof(t[2]);
	free_ft_split(t);
	t = ft_split(buf_t[i + 2], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].orient.x = ft_atof(t[0]);
	s->objectlst[j].orient.y = ft_atof(t[1]);
	s->objectlst[j].orient.z = ft_atof(t[2]);
	free_ft_split(t);
	s->objectlst[j].radius = ft_atof(buf_t[i + 3]) / 2;
	s->objectlst[j].radius2 = s->objectlst[j].radius * s->objectlst[j].radius;
	s->objectlst[j].height = ft_atof(buf_t[i + 4]);
	t = ft_split(buf_t[i + 5], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
}

int	parse_pl(t_scene *s, char **buf_t, size_t i, size_t j)
{
	char	**t;

	s->objectlst[j].type = CYLINDER;
	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].center.x = ft_atof(t[0]);
	s->objectlst[j].center.y = ft_atof(t[1]);
	s->objectlst[j].center.z = ft_atof(t[2]);
	free_ft_split(t);
	t = ft_split(buf_t[i + 2], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].orient.x = ft_atof(t[0]);
	s->objectlst[j].orient.y = ft_atof(t[1]);
	s->objectlst[j].orient.z = ft_atof(t[2]);
	free_ft_split(t);
	s->objectlst[j].radius = ft_atof(buf_t[i + 3]) / 2;
	s->objectlst[j].radius2 = s->objectlst[j].radius * s->objectlst[j].radius;
	s->objectlst[j].height = ft_atof(buf_t[i + 4]);
	t = ft_split(buf_t[i + 5], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
}

int	parse_sp(t_scene *s, char **buf_t, size_t i, size_t j)
{
	char	**t;

	s->objectlst[j].type = SPHERE;
	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].center.x = ft_atof(t[0]);
	s->objectlst[j].center.y = ft_atof(t[1]);
	s->objectlst[j].center.z = ft_atof(t[2]);
	free_ft_split(t);
	s->objectlst[j].radius = ft_atof(buf_t[i + 2]) / 2;
	s->objectlst[j].radius2 = s->objectlst[j].radius * s->objectlst[j].radius;
	t = ft_split(buf_t[i + 3], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->objectlst[j].color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
	return (0);
}

int	parse_light(t_scene *s, char **buf_t, size_t i)
{
	char	**t;

	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->light.center.x = ft_atof(t[0]);
	s->light.center.y = ft_atof(t[1]);
	s->light.center.z = ft_atof(t[2]);
	free_ft_split(t);
	s->light.brightness_ratio = ft_atof(buf_t[i + 2]);
	t = ft_split(buf_t[i + 3], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->light.color = do_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_ft_split(t);
	return (0);
}

int	parse_camera(t_scene *s, char **buf_t, size_t i)
{
	char	**t;

	t = ft_split(buf_t[i + 1], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->camera.origin.x = ft_atof(t[0]);
	s->camera.origin.y = ft_atof(t[1]);
	s->camera.origin.z = ft_atof(t[2]);
	free_ft_split(t);
	t = ft_split(buf_t[i + 2], ',');
	if (!t)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->camera.orient.x = ft_atof(t[0]);
	s->camera.orient.y = ft_atof(t[1]);
	s->camera.orient.z = ft_atof(t[2]);
	// todo : initialize orient magnitude from x,y,z
	free_ft_split(t);
	s->camera.fov = ft_atoi(buf_t[i + 3]);
	return (0);
}
