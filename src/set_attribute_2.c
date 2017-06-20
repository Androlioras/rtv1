/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attribute_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:33:30 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 14:13:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_angle(t_object *obj, char **params)
{
	obj->angle = create_quaternion(create_vector(
	ft_atof(params[0]) * PI / 180,
	ft_atof(params[1]) * PI / 180,
	-ft_atof(params[2]) * PI / 180));
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_intensity(t_object *obj, char **params)
{
	obj->i.x = ft_atof(params[0]);
	obj->i.y = ft_atof(params[1]);
	obj->i.z = ft_atof(params[2]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_fov(t_object *obj, char **params)
{
	obj->fov_w = ft_atof(params[0]);
	obj->fov_h = ft_atof(params[1]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_alpha(t_object *obj, char **params)
{
	obj->color.a = ft_atou(params[0]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}

void	set_reflection(t_object *obj, char **params)
{
	obj->ref = ft_atof(params[0]);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}
