/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:34:30 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 13:05:43 by wlalaoui         ###   ########.fr       */
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
	int					objectlstsize;
}	t_scene;

//parsing utils
void	free_ft_split(char **splited_str);
double	ft_atof(const char *nptr);
int		do_rgb(int r, int g, int b);
void	replace_endl_by_space(char *buffer);
int		count_objects(const char *buffer);
//parse items
int		parse_cy(t_scene *s, char **buf_t, size_t i, size_t j);
int		parse_pl(t_scene *s, char **buf_t, size_t i, size_t j);
int		parse_sp(t_scene *s, char **buf_t, size_t i, size_t j);
int 	parse_light(t_scene *s, char **buf_t, size_t i);
int		parse_camera(t_scene *s, char **buf_t, size_t i);
int		parse_ambientlight(t_scene *s, char **buf_t, size_t i);

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
//error check items
int	check_a(char **row);
int	check_c(char **row);
int	check_l(char **row);
int	check_sp(char **row);
int check_pl(char **row);
int	check_cy(char **row);

#endif
