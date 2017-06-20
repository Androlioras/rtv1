/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:27:30 by pribault          #+#    #+#             */
/*   Updated: 2017/02/14 13:42:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_translate_point(t_point *p, t_point *v)
{
	p->x += v->x;
	p->y += v->y;
}

void	smlx_translate_pixel(t_pixel *p, t_point *v)
{
	p->x += v->x;
	p->y += v->y;
}

void	smlx_translate_obj(t_obj *obj, int x, int y)
{
	obj->args.vec.x += x;
	obj->args.vec.y += y;
}
