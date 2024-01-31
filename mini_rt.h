/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:34:30 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/31 11:12:29 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "/home/aoizel/minilibx-linux/mlx.h"
# include "math.h"
# include "libftprintf/libprint.h"
# include <stdio.h>

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
	double	magn2;
}	t_vect;

typedef struct s_ray
{
	t_point	origin;
	t_vect	dir;
}	t_ray;

typedef	struct s_matrix
{
	double	a[4][4];
}	t_matrix;

typedef	struct s_camera
{
	t_point		origin;
	t_vect		orient;
	double		fov;
	t_matrix	c2w;
}	t_camera;

typedef	struct s_object
{
	enum e_obj_type	type;
	t_point			center;
	t_vect			orient;
	double			radius;
	double			radius2;
	double			height;
	unsigned int	color;
}	t_object;

typedef struct s_light
{
	t_point			center;
	double			brightness_ratio;
	unsigned int	color; //bonus
}			t_light;

typedef	struct s_scene
{
	void				*mlx_p;
	void				*mlx_w;
	void				*mlx_i;
	int					size_x;
	int					size_y;
	t_camera			camera;
	unsigned int 		alight_color;
	double 				alight_lighting_ratio;
	t_light				light;
	t_object			**objectarray;
}	t_scene;

double	double_max(double a, double b);
double	point_dist(t_point a, t_point b);
double	point_dist2(t_point a, t_point b);
t_point	point_coord(double x, double y, double z);
t_point	point_origin_scale_dir(t_point origin, double scale, t_vect dir);
t_vect	vect_coord(double x, double y, double z);
t_vect	vect_between_points(t_point a, t_point b);
double	vect_magn(t_vect vect);
double	vect_magn2(t_vect vect);
t_vect	add_vect(t_vect v1, t_vect v2);
t_vect	sub_vect(t_vect v1, t_vect v2);
t_vect	scale_vect(double t, t_vect v);
t_vect	cross_product(t_vect v1, t_vect v2);
double	dot_product(t_vect v1, t_vect v2);
void	normalize(t_vect *vect);
t_vect	matrix_product(t_matrix m, t_vect v);
int	image_init(int argc, char **argv, t_scene *scene);
int	init_scene(int argc, char **argv, t_scene *scene);
t_matrix	c2w_matrix(t_camera camera);
double	sphere_intersection(t_object sphere, t_ray ray);
double	plane_intersection(t_object plane, t_ray ray);
double	cylinder_intersection(t_object cylinder, t_ray ray);
void	put_pixel_in_img(t_scene scene, unsigned int i,
					unsigned int j, unsigned int color);
int	win_close(t_scene *scene);

void	add_to_objectlst(t_scene *scene, t_object *object);
int	init_objects(int argc, char **argv, t_scene *scene);
#endif
