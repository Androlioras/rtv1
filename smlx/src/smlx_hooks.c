/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:26:23 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 14:51:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

int		smlx_hook_key_press(int k, t_win *win)
{
	if (k >= TAB_SIZE)
		return (0);
	win->keys.tab[k] = 1;
	return (1);
}

int		smlx_hook_key_release(int k, t_win *win)
{
	if (k >= TAB_SIZE)
		return (0);
	win->keys.tab[k] = 0;
	return (1);
}

int		smlx_hook_mouse_notify(int x, int y, t_win *win)
{
	win->keys.mouse[0] = x;
	win->keys.mouse[1] = y;
	return (1);
}

int		smlx_hook_button_press(int k, int x, int y, t_win *win)
{
	t_list		*list;
	t_button	*button;

	win->keys.mouse[0] = x;
	win->keys.mouse[1] = y;
	if (k >= BUTTONS_SIZE)
		return (0);
	list = win->buttons;
	if (k == 1)
		while (list)
		{
			button = (t_button*)(list->content);
			if (button->event(button, x, y))
				*(button->k) = 1;
			list = list->next;
		}
	win->keys.buttons[k] = 1;
	return (1);
}

int		smlx_hook_button_release(int k, int x, int y, t_win *win)
{
	win->keys.mouse[0] = x;
	win->keys.mouse[1] = y;
	if (k >= BUTTONS_SIZE)
		return (0);
	ft_bzero(win->keys.personnal, 100);
	win->keys.buttons[k] = 0;
	return (1);
}
