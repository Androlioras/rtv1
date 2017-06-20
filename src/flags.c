/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 22:34:37 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 17:34:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		red_cross(t_env *env)
{
	ft_lstdel(&env->elem, (void(*)(void*, size_t))&free);
	smlx_destroy_image(&env->win, &env->img);
	smlx_destroy_window(&env->win);
	free(env->objects);
	free(env->file);
	free(env);
	exit(0);
	return (0);
}

void	ft_exit(t_env *env, int k)
{
	ft_lstdel(&env->elem, (void(*)(void*, size_t))&free);
	smlx_destroy_image(&env->win, &env->img);
	smlx_destroy_window(&env->win);
	free(env->objects);
	free(env->file);
	free(env);
	exit(k);
}
