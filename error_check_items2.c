/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_items2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:36:03 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 12:54:01 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_cy(char **row)
{
	if (!(row[1] && row[2] && row[3] && row[4] && row[5]))
		return (free_ft_split(row), -1);
	if (is_coordinates(row[1]) == -1)
		return (free_ft_split(row), -1);
	if (is_orient(row[2]) == -1)
		return (free_ft_split(row), -1);
	if (is_positive_float(row[3]) == -1)
		return (free_ft_split(row), -1);
	if (is_positive_float(row[4]) == -1)
		return (free_ft_split(row), -1);
	if (is_rgb_str(row[5]) == -1)
		return (free_ft_split(row), -1);
	return (0);
}
