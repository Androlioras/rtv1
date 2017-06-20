/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_destroy_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:50:31 by pribault          #+#    #+#             */
/*   Updated: 2017/02/09 13:05:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libsmlx.h"

void	smlx_destroy_window(t_win *win)
{
	t_list	*list;
	t_list	*prev;

	if (!win)
		return ;
	free(win->title);
	list = win->buttons;
	while (list && list->next)
	{
		prev = list;
		list = list->next;
		smlx_destroy_button((t_button**)&(prev->content));
		free(prev);
	}
	if (list)
		free(list);
	mlx_destroy_window(win->mlx, win->win);
}
