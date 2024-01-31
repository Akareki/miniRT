/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:55:30 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/29 15:36:08 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

int	check_a(char **row)
{
	if (!(row[1] && row[2]))
		return (free_ft_split(row), -1);
	if (is_ratio(row[1]) == -1)
		return (free_ft_split(row), -1);
	if (is_rgb_str(row[2]) == -1)
		return (free_ft_split(row), -1);
	return (0);
}

int	check_c(char **row)
{
	if (!(row[1] && row[2] && row[3]))
		return (free_ft_split(row), -1);
	if (is_coordinates(row[1]) == -1)
		return (free_ft_split(row), -1);
	if (is_orient(row[2]) == -1)
		return (free_ft_split(row), -1);
	if (is_fov(row[3]) == -1)
		return (free_ft_split(row), -1);
	return (0);
}

int	check_l(char **row)
{
	if (!(row[1] && row[2] && row[3]))
		return (free_ft_split(row), -1);
	if (is_coordinates(row[1]) == -1)
		return (free_ft_split(row), -1);
	if (is_ratio(row[2]) == -1)
		return (free_ft_split(row), -1);
	if (is_rgb_str(row[3]) == -1)
		return (free_ft_split(row), -1);
	return (0);
}

int	check_sp(char **row)
{
	if (!(row[1] && row[2] && row[3]))
		return (free_ft_split(row), -1);
	if (is_coordinates(row[1]) == -1)
		return (free_ft_split(row), -1);
	if (is_positive_float(row[2]) == -1)
		return (free_ft_split(row), -1);
	if (is_rgb_str(row[3]) == -1)
		return (free_ft_split(row), -1);
	return (0);
}

int	check_pl(char **row)
{
	if (!(row[1] && row[2] && row[3]))
		return (free_ft_split(row), -1);
	if (is_coordinates(row[1]) == -1)
		return (free_ft_split(row), -1);
	if (is_orient(row[2]) == -1)
		return (free_ft_split(row), -1);
	if (is_rgb_str(row[3]) == -1)
		return (free_ft_split(row), -1);
	return (0);
}
