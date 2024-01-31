/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:15:35 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/31 11:18:56 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

int	parse_ambientlight(t_scene *s, char **buf_t, size_t i)
{
	char	**temp;

	s->alight_lighting_ratio = ft_atof(buf_t[i + 1]);
	temp = ft_split(buf_t[i + 2], ',');
	if (!temp)
		return (free(s->objectlst), free(s), free_ft_split(buf_t), -1);
	s->alight_color = do_rgb(ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
	free_ft_split(temp);
	return (0);
}
