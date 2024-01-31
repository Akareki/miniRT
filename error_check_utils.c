/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:48:00 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 13:25:54 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_rgb_str(const char *str)
{
	char	**temp;
	size_t	i;
	int		comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (-1);
		i++;
	}
	if (comma_count != 2)
		return (-1);
	temp = ft_split(str, ',');
	if (!temp)
		return (-1);
	if (ft_atoi(temp[0]) < 0 || ft_atoi(temp[0]) > 255 || ft_atoi(temp[1]) < 0
		|| ft_atoi(temp[1]) > 255
		|| ft_atoi(temp[2]) < 0 || ft_atoi(temp[2]) > 255)
		return (free_ft_split(temp), -1);
	free_ft_split(temp);
	return (0);
}

int	is_coordinates(const char *str)
{
	size_t	i;
	int		comma_count;
	int		ncomma_count;

	i = 0;
	comma_count = 0;
	ncomma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		if (str[i] == '.')
			ncomma_count++;
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '.'
			&& str[i] != '-')
			return (-1);
		i++;
	}
	if (comma_count != 2 || ncomma_count > 3)
		return (-1);
	return (0);
}

int	is_orient_next(const char *str)
{
	char	**temp;

	temp = ft_split(str, ',');
	if (!temp)
		return (-1);
	if (ft_atof(temp[0]) < -1 || ft_atof(temp[0]) > 1 || ft_atof(temp[1]) < -1
		|| ft_atof(temp[1]) > 1 || ft_atof(temp[2]) < -1 || ft_atof(temp[2]) > 1)
		return (free_ft_split(temp), -1);
	free_ft_split(temp);
}

int	is_orient(const char *str)
{
	char	**temp;
	size_t	i;
	int		comma_count;
	int		ncomma_count;

	i = 0;
	comma_count = 0;
	ncomma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		if (str[i] == '.')
			ncomma_count++;
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '.'
			&& str[i] != '-')
			return (-1);
		i++;
	}
	if (comma_count != 2 || ncomma_count > 3)
		return (-1);
	if (is_orient_next(str) == -1)
		return (-1);
	return (0);
}

int	is_fov(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	if (ft_atoi(str) < 0 || ft_atoi(str) > 180)
		return (-1);
	return (0);
}
