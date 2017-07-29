/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 12:10:09 by pribault          #+#    #+#             */
/*   Updated: 2017/06/21 00:19:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

cl_kernel	create_kernel(t_env *env, cl_device_id *device, char *file,
			char *name)
{
	cl_program	program;
	cl_int		tmp;
	char		log[4096];
	char		*line;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return ((cl_kernel)0);
	ft_get_all_lines(fd, &line);
	program = clCreateProgramWithSource(env->context, 1, (const char**)&line,
	NULL, NULL);
	tmp = clBuildProgram(program, 1, device, NULL, NULL, NULL);
	if (tmp != CL_SUCCESS)
	{
		ft_printf("\033[38;5;88mkernel error %d\n", tmp);
		clGetProgramBuildInfo(program, *device, CL_PROGRAM_BUILD_LOG, 4096,
		log, NULL);
		ft_printf("log: %s\n\033[0m", log);
	}
	free(line);
	close(fd);
	return (clCreateKernel(program, name, NULL));
}

void		init_opencl(t_env *env)
{
	cl_platform_id	platform;
	cl_device_id	device;
	cl_int			error;
	char			name[128];

	if ((error = clGetPlatformIDs(1, &platform, NULL)) != CL_SUCCESS)
	{
		ft_printf("platform error: %d / %x\n", error, error);
		return ;
	}
	if ((error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL)) !=
	CL_SUCCESS)
	{
		ft_printf("device error %d / %x\n", error, error);
		return ;
	}
	env->context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
	env->queue = clCreateCommandQueue(env->context, device, 0, NULL);
	env->kernel = create_kernel(env, &device, "raytracer.cl",
	"render_pixel");
	env->anti_al = create_kernel(env, &device, "antialiasing.cl",
	"antialiasing");
	clGetDeviceInfo(device, CL_DEVICE_NAME, 128, name, NULL);
	ft_printf("device: %s\n", name);
}

t_env		*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->win.w = 1024;
	env->win.h = 756;
	smlx_init(&env->win, env->win.w, env->win.h, "rtv1");
	env->img = smlx_new_image(&env->win, env->win.w, env->win.h);
	env->cam.q = create_quaternion(create_vector(0, 0, 0));
	env->cam.pos = create_vector(0, 0, 0);
	env->sample = 1;
	env->cam.fov_w = 0.4;
	env->cam.fov_h = 0.3;
	env->cam.d = 1;
	env->cam.w = 2 * env->cam.d * tan(env->cam.fov_w);
	env->cam.h = 2 * env->cam.d * tan(env->cam.fov_h);
	env->elem = NULL;
	env->objects = NULL;
	smlx_key_hook(&env->win);
	mlx_hook(env->win.win, 17, (1L << 17), &red_cross, env);
	mlx_loop_hook(env->win.mlx, (int(*)(void*))&ft_loop, env);
	return (env);
}

void		alloc_objects(t_env *env)
{
	t_list	*list;
	t_uint	i;

	list = env->elem;
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	env->objects = (t_object*)malloc(sizeof(t_object) * (i + 1));
	list = env->elem;
	i = 0;
	while (list)
	{
		ft_memcpy(&env->objects[i++], list->content, sizeof(t_object));
		list = list->next;
	}
	env->objects[i].type = 0;
}

void		see_list(t_object *obj)
{
	int		i;

	i = 0;
	while (obj[i].type)
	{
		ft_printf("%s\n", obj[i].name);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc < 2)
		return (1);
	env = init_env();
	if (!load_scene(env, argv[1]))
		return (1);
	env->file = ft_strdup(argv[1]);
	set_camera(env);
	init_opencl(env);
	alloc_objects(env);
	create_buffers(env);
	set_args(env);
	see_list(env->objects);
	mlx_loop(env->win.mlx);
	return (0);
}
