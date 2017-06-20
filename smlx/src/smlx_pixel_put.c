/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_pixel_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 13:41:13 by pribault          #+#    #+#             */
/*   Updated: 2017/06/15 13:23:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_pixel_put(t_image *img, t_pixel p)
{
	if (p.x < 0 || p.x >= img->w || p.y < 0 || p.y >= img->h)
		return ;
	img->l[p.y * img->w + p.x] = p.c;
}
