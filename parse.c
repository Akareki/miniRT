/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:22:32 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 13:17:29 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	parse_objects(t_scene *scene, char **buf_t, size_t i, size_t j)
{
	if (ft_strcmp("cy", buf_t[i]) == 0)
	{
		if (parse_cy(scene, buf_t, i, j) == -1)
			return (-1);
		return (0);
	}
	else if (ft_strcmp("pl", buf_t[i]) == 0)
	{
		if (parse_pl(scene, buf_t, i, j) == -1)
			return (-1);
		return (0);
	}
	else if (ft_strcmp("sp", buf_t[i]) == 0)
	{
		if (parse_sp(scene, buf_t, i, j) == -1)
			return (-1);
		return (0);
	}
	return (1);
}

int	parse_items(t_scene *scene, char **buf_t, size_t i)
{
	if (ft_strcmp("L", buf_t[i]) == 0)
	{
		if (parse_light(scene, buf_t, i) == -1)
			return (-1);
		return (0);
	}
	else if (ft_strcmp("C", buf_t[i]) == 0)
	{
		if (parse_camera(scene, buf_t, i) == -1)
			return (-1);
		return (0);
	}
	else if (ft_strcmp("A", buf_t[i]) == 0)
	{
		if (parse_ambientlight(scene, buf_t, i) == -1)
			return (-1);
		return (0);
	}
	return (1);
}

int	allocate(t_scene **scene, char ***buf_t, char *buffer)
{
	*buf_t = ft_split(buffer, ' ');
	if (!*buf_t)
		return (-1);
	*scene = malloc(sizeof(t_scene));
	if (!*scene)
		return (free_ft_split(*buf_t), -1);
	(*scene)->objectarray = malloc(sizeof(t_object) * count_objects(buffer));
	if (!(*scene)->objectarray)
		return (free(*scene), free_ft_split(*buf_t), -1);
	(*scene)->nb_objects = count_objects(buffer);
	return (0);
}

t_scene	*init_all(char *buffer)
{
	char		**buf_t;
	size_t		i;
	size_t		j;
	t_scene		*scene;
	int			return_value;

	if (allocate(&scene, &buf_t, buffer) == -1)
		return (NULL);
	i = 0;
	j = 0;
	while (buf_t[i])
	{
		return_value = parse_objects(scene, buf_t, i, j);
		if (return_value == 0)
			j++;
		else if (return_value == -1 || parse_items(scene, buf_t, i) == -1)
			return (NULL);
		i++;
	}
	free_ft_split((char **)buf_t);
	return (scene);
}

t_scene	*parse(char *file_path)
{
	int			fd;
	ssize_t		size_read;
	char		buffer[4096];
	t_scene		*scene;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size_read = read(fd, buffer, 4096);
	buffer[size_read] = '\0';
	close(fd);
	if (check_error(buffer) == -1)
		exit(1);
	replace_endl_by_space(buffer);
	scene = init_all(buffer);
	return (scene);
}
