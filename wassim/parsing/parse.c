/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:22:32 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/29 13:11:55 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

int	count_number_of_object(char *buffer)
{
	size_t	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if ((buffer[i] == 'c' && buffer[i + 1] == 'y') //cylinder
		|| (buffer[i] == 'p' && buffer[i + 1] == 'l') // plane
		|| (buffer[i] == 's' && buffer[i + 1] == 'p')) //sphere
			count++;
		i++;
	}
	return (count);
}

t_scene	*init_objects_a(char *buffer)
{
	char	**buf_t;
	char		**temp;
	size_t		i;
	size_t		j;
	t_scene *scene;

	buf_t = ft_split(buffer, ' ');
	if (!buf_t)
		exit(1); //todo : recheck this
	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit(1); //todo : recheck this
	scene->objectlst = malloc(sizeof(t_object) * count_number_of_object(buffer));
	if (!scene->objectlst)
		exit(1); //todo : recheck this
	i = 0;
	j = 0;
	while (buf_t[i])
	{
		//ft_putendl_fd(buf_t[i], 1);
		if (ft_strcmp("cy", buf_t[i]) == 0) //cylinder
		{
			scene->objectlst[j].type = CYLINDER;
			temp = ft_split(buf_t[i + 1], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].center.x = ft_atof(temp[0]);
			scene->objectlst[j].center.y = ft_atof(temp[1]);
			scene->objectlst[j].center.z = ft_atof(temp[2]);
			free_ft_split(temp);
			temp = ft_split(buf_t[i + 2], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].orient.x = ft_atof(temp[0]);
			scene->objectlst[j].orient.y = ft_atof(temp[1]);
			scene->objectlst[j].orient.z = ft_atof(temp[2]);
			free_ft_split(temp);
			scene->objectlst[j].radius = ft_atof(buf_t[i + 3]) / 2;
			scene->objectlst[j].radius2 = scene->objectlst[j].radius * scene->objectlst[j].radius;
			scene->objectlst[j].height = ft_atof(buf_t[i + 4]);
			temp = ft_split(buf_t[i + 5], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].color = create_rgb(ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]));
			free_ft_split(temp);
			j++;
		}
		else if (ft_strcmp("pl", buf_t[i]) == 0) //plane
		{
			scene->objectlst[j].type = PLANE;
			temp = ft_split(buf_t[i + 1], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].center.x = ft_atof(temp[0]);
			scene->objectlst[j].center.y = ft_atof(temp[1]);
			scene->objectlst[j].center.z = ft_atof(temp[2]);
			free_ft_split(temp);
			temp = ft_split(buf_t[i + 2], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].orient.x = ft_atof(temp[0]);
			scene->objectlst[j].orient.y = ft_atof(temp[1]);
			scene->objectlst[j].orient.z = ft_atof(temp[2]);
			free_ft_split(temp);
			temp = ft_split(buf_t[i + 3], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].color = create_rgb(ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]));
			free_ft_split(temp);
			j++;
		}
		else if (ft_strcmp("sp", buf_t[i]) == 0) //sphere
		{
			scene->objectlst[j].type = SPHERE;
			temp = ft_split(buf_t[i + 1], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].center.x = ft_atof(temp[0]);
			scene->objectlst[j].center.y = ft_atof(temp[1]);
			scene->objectlst[j].center.z = ft_atof(temp[2]);
			free_ft_split(temp);
			scene->objectlst[j].radius = ft_atof(buf_t[i + 2]) / 2;
			scene->objectlst[j].radius2 = scene->objectlst[j].radius * scene->objectlst[j].radius;
			temp = ft_split(buf_t[i + 3], ',');
			if (!temp)
				exit(1); //todo : recheck this
			scene->objectlst[j].color = create_rgb(ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]));
			free_ft_split(temp);
			j++;
		}
		else if (ft_strcmp("L", buf_t[i]) == 0)
		{
			temp = ft_split(buf_t[i + 1], ',');
			scene->light.center.x = ft_atof(temp[0]);
			scene->light.center.y = ft_atof(temp[1]);
			scene->light.center.z = ft_atof(temp[2]);
			free_ft_split(temp);
			scene->light.brightness_ratio = ft_atof(buf_t[i + 2]);
			temp = ft_split(buf_t[i + 3], ',');
			scene->light.color = create_rgb(ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]));
			free_ft_split(temp);
		}
		else if (ft_strcmp("C", buf_t[i]) == 0)
		{
			temp = ft_split(buf_t[i + 1], ',');
			scene->camera.origin.x = ft_atof(temp[0]);
			scene->camera.origin.y = ft_atof(temp[1]);
			scene->camera.origin.z = ft_atof(temp[2]);
			free_ft_split(temp);
			temp = ft_split(buf_t[i + 2], ',');
			scene->camera.orient.x = ft_atof(temp[0]);
			scene->camera.orient.y = ft_atof(temp[1]);
			scene->camera.orient.z = ft_atof(temp[2]);
			// todo : initialize orient magnitude from x,y,z
			free_ft_split(temp);
			scene->camera.fov = ft_atoi(buf_t[i + 3]);
		}
		else if (ft_strcmp("A", buf_t[i]) == 0)
		{
			scene->alight_lighting_ratio = ft_atof(buf_t[i + 1]);
			temp = ft_split(buf_t[i + 2], ',');
			scene->alight_color = create_rgb(ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]));
			free_ft_split(temp);
		}
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
	scene = init_objects_a(buffer);
	return (scene);
}

int main(int argc, char **argv)
{
	t_scene *scene;

	if (argc == 2)
	{
		scene = parse(argv[1]);
		if (!scene)
		{
			write(1, "CRASH", 5);
			exit(1);
		}
		printf("it works : %f", scene->light.center.x);
		free(scene->objectlst);
		free(scene);
	}
	else
		return (1);
}