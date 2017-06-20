/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_get_fps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 00:21:47 by pribault          #+#    #+#             */
/*   Updated: 2017/06/18 00:36:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"
#include <sys/time.h>

t_uint	smlx_get_fps(void)
{
	static struct timeval	prev;
	static struct timeval	t;
	t_uint					fps;

	gettimeofday(&t, NULL);
	fps = 1000000 * (t.tv_sec - prev.tv_sec) + t.tv_usec - prev.tv_usec;
	prev = t;
	return ((fps) ? 1000000 / fps : 0);
}
