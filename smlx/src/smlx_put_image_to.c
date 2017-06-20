/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_put_image_to.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 18:12:06 by pribault          #+#    #+#             */
/*   Updated: 2017/05/22 17:47:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

static t_color	smlx_def_color(t_image *i, t_pixel p, t_args *arg)
{
	t_point	center;

	p.x = p.x / arg->z;
	p.y = p.y / arg->z;
	center = smlx_create_point(i->w / (2 / arg->z_w), i->h / (2 / arg->z_h));
	p = smlx_rotate_pixel(arg->mat, center, p);
	p.x /= arg->z_w;
	p.y /= arg->z_h;
	if (p.x < 0 || p.y < 0 || p.x >= i->w || p.y >= i->h)
		return (g_alpha);
	return (i->l[p.y * i->w + p.x]);
}

static t_point	set_min(t_image *i, t_args *arg)
{
	t_point	center;
	t_point	m;

	center = smlx_create_point(i->w / 2, i->h / 2);
	m.x = center.x - (ft_sqrt(ft_power(center.x, 2) + ft_power(center.y, 2)));
	m.y = center.y - (ft_sqrt(ft_power(center.x, 2) + ft_power(center.y, 2)));
	m.x = m.x * (arg->z / (arg->z_w * arg->z_h)) + arg->vec.x;
	m.y = m.y * (arg->z / (arg->z_w * arg->z_h)) + arg->vec.y;
	m.x = (m.x < 0) ? 0 : m.x;
	m.y = (m.y < 0) ? 0 : m.y;
	return (m);
}

static t_point	set_max(t_image *i, t_args *arg)
{
	t_point	center;
	t_point	m;

	center = smlx_create_point(i->w / 2, i->h / 2);
	m.x = center.x + (ft_sqrt(ft_power(center.x, 2) + ft_power(center.y, 2)));
	m.y = center.y + (ft_sqrt(ft_power(center.x, 2) + ft_power(center.y, 2)));
	m.x = m.x * (arg->z / (arg->z_w * arg->z_h)) + arg->vec.x;
	m.y = m.y * (arg->z / (arg->z_w * arg->z_h)) + arg->vec.y;
	return (m);
}

void			smlx_put_img_to_img(t_image *i, t_image *t, t_args *a)
{
	t_pixel	px;
	t_point	max[2];
	t_color	c;
	double	**m;

	if (a->mat[0][1] < 0)
		m = smlx_create_matrix(acos(a->mat[0][0]));
	else
		m = smlx_create_matrix(-acos(a->mat[0][0]));
	max[0] = set_min(i, a);
	max[1] = set_max(i, a);
	px = smlx_create_pixel(max[0].x, max[0].y, g_black);
	while (px.y < max[1].y && px.y < t->h)
	{
		px.x = 0;
		while (px.x < max[1].x && px.x < t->w)
		{
			c = t->l[px.y * t->w + px.x];
			px.c = smlx_def_color(i, smlx_translate(px, a->vec), a);
			smlx_pixel_put(t, smlx_mix_color(px, c));
			px.x++;
		}
		px.y++;
	}
	ft_free_array((void**)m, 2);
}

void			smlx_put_img_to_win(t_win *w, t_image *i, t_args *a)
{
	t_image	*tmp;

	if (!a->z)
		return ;
	tmp = smlx_new_image(w, w->w, w->h);
	smlx_put_img_to_img(i, tmp, a);
	mlx_put_image_to_window(w->mlx, w->win, tmp->img, 0, 0);
	smlx_destroy_image(w, &tmp);
}
