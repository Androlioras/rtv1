/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 21:19:24 by pribault          #+#    #+#             */
/*   Updated: 2017/02/08 16:39:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

t_point	smlx_rotate_point(double **rot, t_point c, t_point p)
{
	t_point	r;

	r.x = (p.x - c.x) * rot[0][0] + (p.y - c.y) * rot[0][1] + c.x;
	r.y = (p.x - c.x) * rot[1][0] + (p.y - c.y) * rot[1][1] + c.y;
	return (r);
}

t_pixel	smlx_rotate_pixel(double **rot, t_point c, t_pixel p)
{
	t_pixel	r;

	r.c = p.c;
	r.x = (p.x - c.x) * rot[0][0] + (p.y - c.y) * rot[0][1] + c.x;
	r.y = (p.x - c.x) * rot[1][0] + (p.y - c.y) * rot[1][1] + c.y;
	return (r);
}
