/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_converts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 21:42:50 by pribault          #+#    #+#             */
/*   Updated: 2017/06/15 12:25:07 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

t_pixel	smlx_mix_color(t_pixel a, t_color b)
{
	double	r;
	t_pixel	i;

	i = a;
	r = 1 - a.c.a / 255;
	i.c.a = r * a.c.a + (1.0 - r) * b.a;
	i.c.r = r * a.c.r + (1.0 - r) * b.r;
	i.c.g = r * a.c.g + (1.0 - r) * b.g;
	i.c.b = r * a.c.b + (1.0 - r) * b.b;
	return (i);
}

double	smlx_deg_to_rad(int deg)
{
	return (deg * 2 * PI / 360);
}

int		smlx_rad_to_deg(double rad)
{
	return (rad * 360 / (2 * PI));
}

t_pixel	smlx_translate(t_pixel p, t_point v)
{
	p.x -= v.x;
	p.y -= v.y;
	return (p);
}
