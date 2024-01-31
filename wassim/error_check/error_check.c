/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:36:05 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 15:12:12 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

int	check_row(char **row)
{
	if (!row)
		return (-1);
	if (ft_strcmp("A", row[0]) == 0 && check_a(row) == -1)
		return (-1);
	else if (ft_strcmp("C", row[0]) == 0 && check_c(row) == -1)
		return (-1);
	else if (ft_strcmp("L", row[0]) == 0 && check_l(row) == -1)
		return (-1);
	else if (ft_strcmp("sp", row[0]) == 0 && check_sp(row) == -1)
		return (-1);
	else if (ft_strcmp("pl", row[0]) == 0 && check_pl(row) == -1)
		return (-1);
	else if (ft_strcmp("cy", row[0]) == 0 && check_cy(row) == -1)
		return (-1);
	free_ft_split(row);
	return (0);
}

int	initial_check(const char *buffer)
{
	size_t	i;
	int		count_alight;
	int		count_camera;
	int		count_light;

	i = 0;
	count_alight = 0;
	count_camera = 0;
	count_light = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'A')
			count_alight++;
		else if (buffer[i] == 'C')
			count_camera++;
		else if (buffer[i] == 'L')
			count_light++;
		i++;
	}
	if (count_alight != 1 || count_camera != 1 || count_light != 1)
		return (-1);
	return (0);
}

int	ft_strcmps(char *word)
{
	const char	acceptable_words[6][3] = {"A", "C", "L", "pl", "sp", "cy"};

	if (ft_strcmp(word, acceptable_words[0]) == 0)
		return (0);
	else if (ft_strcmp(word, acceptable_words[1]) == 0)
		return (0);
	else if (ft_strcmp(word, acceptable_words[2]) == 0)
		return (0);
	else if (ft_strcmp(word, acceptable_words[3]) == 0)
		return (0);
	else if (ft_strcmp(word, acceptable_words[4]) == 0)
		return (0);
	else if (ft_strcmp(word, acceptable_words[5]) == 0)
		return (0);
	return (-1);
}

int	check_rows(char **row)
{
	size_t	i;
	char	**temp;

	i = 0;
	while (row[i])
	{
		temp = ft_split(row[i], ' ');
		if (!temp)
			return (-1);
		if (ft_strcmps(temp[0]) == -1)
			return (free_ft_split(temp), -1);
		free_ft_split(temp);
		i++;
	}
	return (0);
}

int	check_error(const char *buffer)
{
	size_t	i;
	char	**buffer_table;

	i = 0;
	if (initial_check(buffer) == -1)
		return (ft_putstr_fd("Error\nYou should have at least one, and only one ambient li\
ght, camera and light.\n", 1), -1);
	buffer_table = ft_split(buffer, '\n');
	if (!buffer_table)
		return (perror("malloc"), -1);
	if (check_rows(buffer_table) == -1)
		return (free_ft_split(buffer_table), write(1, "Error\nInvalid token", 2), -1);
	while (buffer_table[i])
	{
		if (check_row(ft_split(buffer_table[i], ' ')) == -1)
			return (free_ft_split(buffer_table), ft_putstr_fd("Error\nMake sure\
 you have the right attributes, at the right format, for each item", 1), -1);
		i++;
	}
	free_ft_split(buffer_table);
	return (0);
}
