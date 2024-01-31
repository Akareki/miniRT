/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:50:35 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 12:53:49 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_float(const char *str)
{
	size_t	i;
	int		count_dot;

	i = 0;
	count_dot = 0;
	while (str[i])
	{
		if (str[i] == '.')
			count_dot++;
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'
				|| str[i] == '-'))
			return (-1);
		i++;
	}
	if (!(count_dot == 0 || count_dot == 1))
		return (-1);
	return (0);
}

int	is_positive_float(const char *str)
{
	size_t	i;
	int		count_dot;

	i = 0;
	count_dot = 0;
	while (str[i])
	{
		if (str[i] == '.')
			count_dot++;
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
			return (-1);
		i++;
	}
	if (!(count_dot == 0 || count_dot == 1))
		return (-1);
	return (0);
}

int	is_ratio(const char *str)
{
	if (is_float(str) == -1)
		return (-1);
	if (ft_atof(str) < 0 || ft_atof(str) > 1)
		return (-1);
	return (0);
}
