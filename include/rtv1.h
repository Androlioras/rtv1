/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 12:42:41 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 23:43:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <OpenCL/cl.h>
# include "ft_printf.h"
# include "libsmlx.h"

/*
**	macros for attribute struct
*/

# define MAX_PARAMS		6

# define STRING			1
# define FLOAT			2
# define INT			4
# define UCHAR			8
# define UINT			16

/*
**	macros for object type in the elem list
*/

# define CAMERA			1
# define LIGHT_SPOT		2
# define SPHERE			4
# define PLAN			8
# define CONE			16
# define CYLINDER		32

# define STRING_CHARS	"abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define STRING_LEN		128

# define STEP			1
# define ROTATION		PI / 84

typedef struct			s_vec
{
	float				x;
	float				y;
	float				z;
}						t_vec;

typedef struct			s_collision
{
	t_vec				point;
	char				collision;
}						t_collision;

typedef struct			s_ray
{
	t_vec				pos;
	t_vec				dir;
}						t_ray;

typedef struct			s_quat
{
	float				w;
	float				x;
	float				y;
	float				z;
}						t_quat;

typedef struct			s_camera
{
	t_vec				pos;
	t_quat				q;
	float				w;
	float				h;
	float				d;
	float				fov_w;
	float				fov_h;
}						t_camera;

typedef struct			s_object
{
	char				name[STRING_LEN];
	t_uchar				type;
	t_color				color;
	t_uchar				ref;
	t_quat				angle;
	t_vec				norm;
	t_vec				pos;
	t_vec				i;
	float				r;
	float				d;
	float				fov_w;
	float				fov_h;
}						t_object;

typedef struct			s_attribute
{
	char				*name;
	t_uchar				n_params;
	t_uchar				params[MAX_PARAMS];
	void				(*func)(t_object*, char**);
}						t_attribute;

typedef struct			s_element
{
	char				*name;
	t_uchar				n_params;
	char				**params;
	t_uchar				macro;
}						t_element;

typedef struct			s_env
{
	t_win				win;
	t_image				*img;
	t_camera			cam;
	t_list				*elem;
	cl_command_queue	queue;
	cl_context			context;
	cl_kernel			kernel;
	cl_kernel			anti_al;
	t_object			*objects;
	char				*file;
	cl_mem				map;
	cl_mem				map2;
	cl_mem				mem_cam;
	cl_mem				w;
	cl_mem				h;
	cl_mem				mem_objects;
	cl_mem				a;
	cl_mem				b;
	size_t				sample;
}						t_env;

void					ft_exit(t_env *env, int k);
void					ft_loop(t_env *env);
int						red_cross(t_env *env);
void					ft_keys(t_env *env);

char					load_scene(t_env *env, char *scene);
void					alloc_objects(t_env *env);
void					set_camera(t_env *env);

t_element				*get_elements(void);
t_attribute				*get_attributes(void);

char					get_elem(t_env *env, t_element *elem, char *line,
						int *i);
char					get_attrib(t_env *env, t_attribute *attr, char *line,
						int *i);

void					set_name(t_object *obj, char **params);
void					set_color(t_object *obj, char **params);
void					set_position(t_object *obj, char **params);
void					set_radius(t_object *obj, char **params);
void					set_distance(t_object *obj, char **params);
void					set_angle(t_object *obj, char **params);
void					set_intensity(t_object *obj, char **params);
void					set_fov(t_object *obj, char **params);
void					set_alpha(t_object *obj, char **params);
void					set_reflection(t_object *obj, char **params);
void					set_normal(t_object *obj, char **params);

/*
**	raytracer functions
*/

void					create_buffers(t_env *env);
void					set_args(t_env *env);

void					calc_vectors(t_env *env);
void					launch_raytracer(t_env *env, t_ray *ray, t_pixel *p);

/*
**	vectors functions
*/

t_vec					create_vector(float x, float y, float z);
t_vec					rotate_vector(t_vec *a, t_quat *q);
void					normalize_vector(t_vec *a);

/*
**	quaternions functions
*/

t_quat					create_quaternion(t_vec rot);
t_vec					convert_quaternion_to_angle(t_quat *q);
t_quat					multiply_quaternion(t_quat *q1, t_quat *q2);
void					normalize_quaternion(t_quat *q);
double					get_quaternion_norm(t_quat *q);

#endif
