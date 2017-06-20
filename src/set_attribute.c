/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:16:30 by pribault          #+#    #+#             */
/*   Updated: 2017/06/16 16:11:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_name(t_object *obj, char **params)
{
	ft_bzero(obj->name, STRING_LEN);
	if (params[0])
		ft_memcpy(obj->name, params[0], ft_strlen(params[0]));
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_color(t_object *obj, char **params)
{
	obj->color.r = ft_atou(params[0]);
	obj->color.g = ft_atou(params[1]);
	obj->color.b = ft_atou(params[2]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_position(t_object *obj, char **params)
{
	obj->pos.x = ft_atof(params[0]);
	obj->pos.y = ft_atof(params[1]);
	obj->pos.z = ft_atof(params[2]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_radius(t_object *obj, char **params)
{
	obj->r = ft_atof(params[0]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_distance(t_object *obj, char **params)
{
	obj->d = ft_atof(params[0]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}
