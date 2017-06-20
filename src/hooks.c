/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 14:50:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 17:41:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_keys_3(t_env *env)
{
	t_quat	q;

	if (env->win.keys.tab[123] || env->win.keys.tab[124])
	{
		q = create_quaternion(create_vector(0, 0, (env->win.keys.tab[123]) ?
		-ROTATION : ROTATION));
		env->cam.q = multiply_quaternion(&q, &env->cam.q);
		env->mem_cam = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
		sizeof(t_camera), &env->cam, NULL);
		clSetKernelArg(env->kernel, 1, sizeof(cl_mem), &env->mem_cam);
	}
	if (env->win.keys.tab[126] || env->win.keys.tab[125])
	{
		q = create_quaternion(create_vector(0, (env->win.keys.tab[126]) ?
		ROTATION : -ROTATION, 0));
		env->cam.q = multiply_quaternion(&q, &env->cam.q);
		env->mem_cam = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
		sizeof(t_camera), &env->cam, NULL);
		clSetKernelArg(env->kernel, 1, sizeof(cl_mem), &env->mem_cam);
	}
}

void	ft_keys_2(t_env *env)
{
	t_vec	d;

	if (env->win.keys.tab[49] || env->win.keys.tab[257])
	{
		d = create_vector(0, 0, (env->win.keys.tab[49]) ? STEP : -STEP);
		d = rotate_vector(&d, &env->cam.q);
		env->cam.pos = create_vector(env->cam.pos.x + d.x,
		env->cam.pos.y + d.y, env->cam.pos.z + d.z);
		env->mem_cam = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
		sizeof(t_camera), &env->cam, NULL);
		clSetKernelArg(env->kernel, 1, sizeof(cl_mem), &env->mem_cam);
	}
	if (env->win.keys.tab[15])
	{
		ft_lstdel(&env->elem, (void(*)(void*, size_t))&free);
		free(env->objects);
		if (!load_scene(env, env->file))
			exit(1);
		alloc_objects(env);
		create_buffers(env);
		set_args(env);
	}
	ft_keys_3(env);
}

void	ft_keys(t_env *env)
{
	t_vec	d;

	if (env->win.keys.tab[53])
		ft_exit(env, 0);
	if (env->win.keys.tab[13] || env->win.keys.tab[1])
	{
		d = create_vector((env->win.keys.tab[13]) ? STEP : -STEP, 0, 0);
		d = rotate_vector(&d, &env->cam.q);
		env->cam.pos = create_vector(env->cam.pos.x + d.x,
		env->cam.pos.y + d.y, env->cam.pos.z + d.z);
		env->mem_cam = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
		sizeof(t_camera), &env->cam, NULL);
		clSetKernelArg(env->kernel, 1, sizeof(cl_mem), &env->mem_cam);
	}
	if (env->win.keys.tab[0] || env->win.keys.tab[2])
	{
		d = create_vector(0, (env->win.keys.tab[0]) ? STEP : -STEP, 0);
		d = rotate_vector(&d, &env->cam.q);
		env->cam.pos = create_vector(env->cam.pos.x + d.x,
		env->cam.pos.y + d.y, env->cam.pos.z + d.z);
		env->mem_cam = clCreateBuffer(env->context, CL_MEM_COPY_HOST_PTR,
		sizeof(t_camera), &env->cam, NULL);
		clSetKernelArg(env->kernel, 1, sizeof(cl_mem), &env->mem_cam);
	}
	ft_keys_2(env);
}
