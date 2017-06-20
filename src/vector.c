/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 13:01:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 18:53:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	create_vector(float x, float y, float z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

void	normalize_vector(t_vec *a)
{
	double	norm;

	norm = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}

t_vec	rotate_vector(t_vec *a, t_quat *q)
{
	t_vec	new;

	new.x = a->x * (q->w * q->w + q->x * q->x - q->y * q->y - q->z * q->z) +
	a->y * 2 * (q->x * q->y - q->w * q->z) +
	a->z * 2 * (q->x * q->z + q->w * q->y);
	new.y = a->x * 2 * (q->x * q->y + q->w * q->z) +
	a->y * (q->w * q->w - q->x * q->x + q->y * q->y - q->z * q->z) +
	a->z * 2 * (q->y * q->z - q->w * q->x);
	new.z = a->x * 2 * (q->x * q->z - q->w * q->y) +
	a->y * 2 * (q->y * q->z + q->w * q->x) +
	a->z * (q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z);
	return (new);
}
