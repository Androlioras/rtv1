/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:22:38 by pribault          #+#    #+#             */
/*   Updated: 2017/05/19 18:41:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_init(t_win *win, int w, int h, char *title)
{
	w = (w > 2560) ? 2560 : w;
	w = (w < 0) ? 0 : w;
	h = (h > 1440) ? 1440 : h;
	h = (h < 0) ? 0 : h;
	title = (!title) ? "default" : title;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, w, h, title);
	win->title = ft_strdup(title);
	win->buttons = NULL;
	ft_bzero(win->keys.tab, TAB_SIZE);
	ft_bzero(win->keys.mouse, 2);
	win->w = w;
	win->h = h;
	smlx_set_flags(win, 0);
}
