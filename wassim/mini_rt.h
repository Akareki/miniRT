/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:34:30 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/29 12:50:05 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "/home/wlalaoui/minilibx-linux/mlx.h"
# include "math.h"
# include "libftprintf/libprint.h"
# include <stdio.h>
# include <fcntl.h>

enum	e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
	double	magn;
}	t_vect;

typedef struct s_ray
{
	t_point	origin;
	t_vect	dir;
	double	magn;
	double	magn2;
}	t_ray;

typedef	struct s_camera
{
	t_point	origin;
	t_vect	orient;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_point			center;
	double			brightness_ratio;
	unsigned int	color; //bonus
}			t_light;

typedef	struct s_object
{
	enum e_obj_type	type;
	t_point			center;
	t_vect			orient;
	double			radius;
	double			radius2;
	double			height;
	unsigned int	color;
	struct s_object	*next;
}	t_object;

typedef	struct s_scene
{
	void				*mlx_p;
	void				*mlx_w;
	void				*mlx_i;
	unsigned int		size_x;
	unsigned int		size_y;
	unsigned int 		alight_color;
	double 				alight_lighting_ratio;
	t_camera			camera;
	t_light				light;
	t_object			*objectlst;
}	t_scene;

//parsing
void	free_ft_split(char **splited_str);
double	ft_atof(const char *nptr);
int		create_rgb(int r, int g, int b);
void	replace_endl_by_space(char *buffer);
//error checking
int		check_error(const char *buffer);
//error check utils
int		is_float(const char *str);
int 	is_ratio(const char *str);
int		is_rgb_str(const char *str);
int		is_coordinates(const char *str);
int		is_orient(const char *str);
int 	is_fov(const char *str);
int		is_positive_float(const char *str);

#endif
