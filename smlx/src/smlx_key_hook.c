/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_key_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:46:12 by pribault          #+#    #+#             */
/*   Updated: 2017/06/15 12:36:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void		smlx_key_hook(t_win *win)
{
	mlx_hook(win->win, 2, (1L << 0), &smlx_hook_key_press, win);
	mlx_hook(win->win, 3, (1L << 1), &smlx_hook_key_release, win);
	if (win->flags.mouse)
	{
		mlx_hook(win->win, 5, (1L << 3), &smlx_hook_button_release, win);
		mlx_hook(win->win, 4, (1L << 2), &smlx_hook_button_press, win);
	}
	if (win->flags.motion)
		mlx_hook(win->win, 6, (1L << 6), &smlx_hook_mouse_notify, win);
}
