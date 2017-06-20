/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 19:11:40 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 14:50:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_buffers_2(t_env *env)
{
	float	a[2];
	float	b[2];
	cl_int	r;

	a[0] = -env->cam.w / (env->win.w - 1);
	a[1] = -env->cam.h / (env->win.h - 1);
	b[0] = env->cam.w / 2;
	b[1] = env->cam.h / 2;
	env->a = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(float) * 2, &a, &r);
	env->b = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(float) * 2, &b, &r);
}

void	create_buffers(t_env *env)
{
	t_uint	i;
	cl_int	r;

	i = 0;
	while (env->objects[i].type)
		i++;
	env->mem_objects = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_object) * i, env->objects, &r);
	env->mem_cam = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_camera), &env->cam, &r);
	env->map = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * env->img->w * env->img->h, env->img->l, &r);
	env->map2 = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * env->img->w * env->img->h, env->img->l, &r);
	env->w = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(int), &env->img->w, &r);
	env->h = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
	sizeof(int), &env->img->h, &r);
	create_buffers_2(env);
}

void	set_args(t_env *env)
{
	cl_int	r;

	r = clSetKernelArg(env->kernel, 0, sizeof(cl_mem), &env->map);
	r = clSetKernelArg(env->kernel, 1, sizeof(cl_mem), &env->mem_cam);
	r = clSetKernelArg(env->kernel, 2, sizeof(cl_mem), &env->w);
	r = clSetKernelArg(env->kernel, 3, sizeof(cl_mem), &env->h);
	r = clSetKernelArg(env->kernel, 4, sizeof(cl_mem), &env->mem_objects);
	r = clSetKernelArg(env->kernel, 5, sizeof(cl_mem), &env->a);
	r = clSetKernelArg(env->kernel, 6, sizeof(cl_mem), &env->b);
	r = clSetKernelArg(env->anti_al, 2, sizeof(cl_mem), &env->w);
	r = clSetKernelArg(env->anti_al, 3, sizeof(cl_mem), &env->h);
}

void	launch_antialiasing(t_env *env, size_t n)
{
	size_t	i;
	cl_int	r;

	i = 0;
	while (i++ < env->sample)
	{
		r = clSetKernelArg(env->anti_al, 0, sizeof(cl_mem), &env->map);
		r = clSetKernelArg(env->anti_al, 1, sizeof(cl_mem), &env->map2);
		r = clEnqueueNDRangeKernel(env->queue, env->anti_al, 1, NULL, &n,
		NULL, 0, NULL, NULL);
		clFinish(env->queue);
		r = clSetKernelArg(env->anti_al, 1, sizeof(cl_mem), &env->map);
		r = clSetKernelArg(env->anti_al, 0, sizeof(cl_mem), &env->map2);
		r = clEnqueueNDRangeKernel(env->queue, env->anti_al, 1, NULL, &n,
		NULL, 0, NULL, NULL);
		clFinish(env->queue);
	}
}

void	ft_loop(t_env *env)
{
	char	*fps;
	size_t	n;
	cl_int	r;

	n = env->img->w * env->img->h;
	ft_keys(env);
	r = clEnqueueNDRangeKernel(env->queue, env->kernel, 1, NULL, &n,
	NULL, 0, NULL, NULL);
	clFinish(env->queue);
	launch_antialiasing(env, n);
	r = clEnqueueReadBuffer(env->queue, env->map2, CL_TRUE, 0, sizeof(t_color) *
	env->img->w * env->img->h, env->img->l, 0, NULL, NULL);
	mlx_put_image_to_window(env->win.mlx, env->win.win, env->img->img, 0, 0);
	fps = ft_itoa(smlx_get_fps());
	mlx_string_put(env->win.mlx, env->win.win, 5, 5, 0xffffff, fps);
	free(fps);
}
