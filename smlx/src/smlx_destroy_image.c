/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_destroy_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:43:51 by pribault          #+#    #+#             */
/*   Updated: 2017/02/04 11:12:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_destroy_image(t_win *win, t_image **img)
{
	if (!img || !(*img))
		return ;
	if (win && (*img)->img)
		mlx_destroy_image(win->mlx, (*img)->img);
	(*img)->win = NULL;
	(*img)->img = NULL;
	(*img)->l = NULL;
	free(*img);
	*img = NULL;
}
