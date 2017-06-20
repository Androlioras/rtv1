/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_clear_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:37:33 by pribault          #+#    #+#             */
/*   Updated: 2017/05/22 15:09:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_clear_image(t_image *img)
{
	t_color	c;
	int		i;

	c = smlx_create_color(0, 0, 0, 255);
	i = 0;
	while (i < img->w * img->h)
	{
		img->l[i] = c;
		i++;
	}
}
