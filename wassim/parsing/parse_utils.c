/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:38:59 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 11:50:48 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

void	free_ft_split(char **splited_str)
{
	size_t	i;

	i = 0;
	while (splited_str[i])
	{
		free(splited_str[i]);
		i++;
	}
	free(splited_str);
}

int	do_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	replace_endl_by_space(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			buffer[i] = ' ';
		i++;
	}
}

double	ft_atof(const char *nptr)
{
	double	num;
	int		sign;
	size_t	i;
	size_t	ten_pow;

	num = 0;
	sign = 1;
	i = 0;
	ten_pow = 10;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ' )
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = 10 * num + nptr[i] - '0';
		i++;
	}
	if (nptr[i] == '.')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num + ((double)(nptr[i++] - '0') / ten_pow);
		ten_pow *= 10;
	}
	return (sign * num);
}

int	count_objects(const char *buffer)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if ((buffer[i] == 'c' && buffer[i + 1] == 'y')
			|| (buffer[i] == 'p' && buffer[i + 1] == 'l')
			|| (buffer[i] == 's' && buffer[i + 1] == 'p'))
			count++;
		i++;
	}
	return (count);
}
