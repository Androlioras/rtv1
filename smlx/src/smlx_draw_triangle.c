/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_draw_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 19:44:27 by pribault          #+#    #+#             */
/*   Updated: 2017/06/15 12:37:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

static void		replace_pixels(t_pixel *a, t_pixel *b, t_pixel *c)
{
	t_pixel	tmp;

	if (b->x < a->x)
	{
		tmp = *b;
		*b = *a;
		*a = tmp;
	}
	if (c->x < a->x)
	{
		tmp = *c;
		*c = *a;
		*a = tmp;
	}
	if (b->x > c->x)
	{
		tmp = *b;
		*b = *c;
		*c = tmp;
	}
}

static t_pixel	define_color(t_win *win, t_pixel a, t_pixel b, t_pixel i)
{
	double	r;
	double	ab;
	double	ib;

	if (!win->flags.c_slope)
		return (i);
	ab = ft_sqrt(ft_power(b.x - a.x, 2) + ft_power(b.y - a.y, 2));
	ib = ft_sqrt(ft_power(b.x - i.x, 2) + ft_power(b.y - i.y, 2));
	r = (ab != 0) ? ib / ab : 0;
	i.c.r = r * a.c.r + (1.0 - r) * b.c.r;
	i.c.g = r * a.c.g + (1.0 - r) * b.c.g;
	i.c.b = r * a.c.b + (1.0 - r) * b.c.b;
	i.c.a = r * a.c.a + (1.0 - r) * b.c.a;
	return (i);
}

static void		draw_triangle_part1(t_image *img, t_pixel a, t_pixel b,
				t_pixel c)
{
	t_pixel	m[2];
	t_pixel	i;
	double	d[2];
	int		e[2];

	i = a;
	d[0] = (a.x != b.x) ? ((double)(a.y - b.y) / (a.x - b.x)) : 0;
	d[1] = (a.x != c.x) ? ((double)(a.y - c.y) / (a.x - c.x)) : 0;
	e[0] = a.y - a.x * d[0];
	e[1] = a.y - a.x * d[1];
	while (i.x <= b.x)
	{
		m[0] = smlx_create_pixel(i.x, i.x * d[0] + e[0], g_black);
		m[0] = define_color(img->win, a, b, m[0]);
		m[1] = smlx_create_pixel(i.x, i.x * d[1] + e[1], g_black);
		m[1] = define_color(img->win, a, c, m[1]);
		i.y = m[0].y;
		while ((m[0].y < m[1].y) ? i.y <= m[1].y : i.y >= m[1].y)
		{
			smlx_pixel_put(img, define_color(img->win, m[0], m[1], i));
			i.y += (m[0].y < m[1].y) ? 1 : -1;
		}
		i.x++;
	}
}

static void		draw_triangle_part2(t_image *img, t_pixel a, t_pixel b,
				t_pixel c)
{
	t_pixel	m[2];
	t_pixel	i;
	double	d[2];
	int		e[2];

	i = b;
	d[0] = (b.x != c.x) ? ((double)(b.y - c.y) / (b.x - c.x)) : 0;
	d[1] = (a.x != c.x) ? ((double)(a.y - c.y) / (a.x - c.x)) : 0;
	e[0] = c.y - c.x * d[0];
	e[1] = c.y - c.x * d[1];
	while (i.x <= c.x)
	{
		m[0] = smlx_create_pixel(i.x, i.x * d[0] + e[0], g_black);
		m[0] = define_color(img->win, b, c, m[0]);
		m[1] = smlx_create_pixel(i.x, i.x * d[1] + e[1], g_black);
		m[1] = define_color(img->win, a, c, m[1]);
		i.y = m[0].y;
		while ((m[0].y < m[1].y) ? i.y <= m[1].y : i.y >= m[1].y)
		{
			smlx_pixel_put(img, define_color(img->win, m[0], m[1], i));
			i.y += (m[0].y < m[1].y) ? 1 : -1;
		}
		i.x++;
	}
}

void			smlx_draw_triangle(t_image *img, t_pixel a, t_pixel b,
				t_pixel c)
{
	replace_pixels(&a, &b, &c);
	draw_triangle_part1(img, a, b, c);
	draw_triangle_part2(img, a, b, c);
}
