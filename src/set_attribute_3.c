/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attribute_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 14:02:10 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 18:54:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_normal(t_object *obj, char **params)
{
	obj->norm.x = ft_atof(params[0]);
	obj->norm.y = ft_atof(params[1]);
	obj->norm.z = ft_atof(params[2]);
	normalize_vector(&obj->norm);
	ft_free_array((void**)params, ft_arraylen(params) + 1);
}
