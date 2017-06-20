/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_draw_polygone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:13:52 by pribault          #+#    #+#             */
/*   Updated: 2017/05/19 00:17:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_draw_full_polygone(t_image *img, t_pixel *p, t_uint n)
{
	int		t[3];
	int		nbr;
	int		i;

	nbr = n - 2;
	i = 0;
	t[2] = 0;
	while (i < nbr)
	{
		t[0] = t[2];
		t[1] = t[0] + t[0] / n + 1;
		t[2] = t[1] + t[1] / n + 1;
		smlx_draw_triangle(img, p[t[0] % n], p[t[1] % n], p[t[2] % n]);
		i++;
	}
}

void	smlx_draw_polygone(t_image *img, t_pixel *pixels, t_uint n)
{
	t_uint	i;

	i = 0;
	while (i < n)
	{
		smlx_draw_line(img, pixels[i], pixels[(i + 1) % n]);
		i++;
	}
}
