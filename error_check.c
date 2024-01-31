/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:36:05 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 12:53:55 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

int	check_error(const char *buffer)
{
	size_t	i;
	char	**buffer_table;

	i = 0;
	if (initial_check(buffer) == -1)
		return (-1);
	buffer_table = ft_split(buffer, '\n');
	if (!buffer_table)
		return (-1);
	while (buffer_table[i])
	{
		if (check_row(ft_split(buffer_table[i], ' ')) == -1)
			return (free_ft_split(buffer_table), -1);
		i++;
	}
	free_ft_split(buffer_table);
	return (0);
}
