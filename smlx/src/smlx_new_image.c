/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_new_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:33:29 by pribault          #+#    #+#             */
/*   Updated: 2017/06/15 12:29:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

t_image	*smlx_new_image_xpm(t_win *win, char *file)
{
	t_image	*i;
	int		fd;

	if (!win || !file || (fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	close(fd);
	if (!(i = (t_image*)malloc(sizeof(t_image))))
		return (NULL);
	if (!(i->img = mlx_xpm_file_to_image(win->mlx, file, &(i->w), &(i->h))))
		smlx_destroy_image(win, &i);
	if (!i)
		return (NULL);
	i->l = (t_color*)mlx_get_data_addr(i->img, &i->bits, &i->size_l,
	&i->endian);
	if (!i->l)
		return (NULL);
	i->win = win;
	return (i);
}

t_image	*smlx_new_image(t_win *win, int w, int h)
{
	t_image	*i;

	if (!win)
		return (NULL);
	if (!(i = (t_image*)malloc(sizeof(t_image))))
		return (NULL);
	i->w = w;
	i->h = h;
	if (!(i->img = mlx_new_image(win->mlx, w, h)))
		smlx_destroy_image(win, &i);
	if (!i)
		return (NULL);
	i->l = (t_color*)mlx_get_data_addr(i->img, &i->bits, &i->size_l,
	&i->endian);
	if (!i->l)
		return (NULL);
	i->win = win;
	return (i);
}
