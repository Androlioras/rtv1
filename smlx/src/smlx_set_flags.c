/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_set_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 10:41:05 by pribault          #+#    #+#             */
/*   Updated: 2017/05/22 13:14:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_set_flags(t_win *win, int flags)
{
	win->flags.rotation = ((flags & SMLX_ROTATION) == SMLX_ROTATION) ? 1 : 0;
	win->flags.c_slope = ((flags & SMLX_C_SLOPE) == SMLX_C_SLOPE) ? 1 : 0;
	win->flags.motion = ((flags & SMLX_MOTION) == SMLX_MOTION) ? 1 : 0;
	win->flags.mouse = ((flags & SMLX_MOUSE) == SMLX_MOUSE) ? 1 : 0;
}
