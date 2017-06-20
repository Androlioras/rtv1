/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:53:39 by pribault          #+#    #+#             */
/*   Updated: 2017/05/22 15:01:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

t_args	smlx_create_arg(int angle, int x, int y, double zoom)
{
	t_args	arg;

	arg.mat = smlx_create_matrix(angle);
	arg.vec = smlx_create_point(x, y);
	arg.z = zoom;
	arg.z_w = 1;
	arg.z_h = 1;
	return (arg);
}

t_pixel	smlx_create_pixel(int x, int y, t_color c)
{
	t_pixel	p;

	p.x = x;
	p.y = y;
	p.c = c;
	return (p);
}

t_point	smlx_create_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_color	smlx_create_color(t_uchar r, t_uchar g, t_uchar b, t_uchar a)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}
