/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 15:15:31 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 15:37:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	convert_quaternion_to_angle(t_quat *q)
{
	t_vec	new;

	new.x = atan((2 * (q->w * q->x + q->y * q->z)) /
	(1 - 2 * (pow(q->x, 2) + pow(q->y, 2))));
	new.y = asin(2 * (q->w * q->y - q->z * q->x));
	new.z = atan((2 * (q->w * q->z + q->x * q->y)) /
	(1 - 2 * (pow(q->y, 2) + pow(q->z, 2))));
	return (new);
}

double	get_quaternion_norm(t_quat *q)
{
	return (q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

void	normalize_quaternion(t_quat *q)
{
	double	norm;

	norm = get_quaternion_norm(q);
	q->x /= norm;
	q->y /= norm;
	q->z /= norm;
	q->w /= norm;
}

t_quat	multiply_quaternion(t_quat *q1, t_quat *q2)
{
	t_quat	new;

	new.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	new.x = q1->w * q2->x + q1->x * q2->w - q1->y * q2->z + q1->z * q2->y;
	new.y = q1->w * q2->y + q1->x * q2->z + q1->y * q2->w - q1->z * q2->x;
	new.z = q1->w * q2->z - q1->x * q2->y + q1->y * q2->x + q1->z * q2->w;
	normalize_quaternion(&new);
	return (new);
}

t_quat	create_quaternion(t_vec rot)
{
	double	tmp[6];
	t_quat	new;

	tmp[0] = cos(-rot.z / 2);
	tmp[1] = sin(-rot.z / 2);
	tmp[2] = cos(-rot.x / 2);
	tmp[3] = sin(-rot.x / 2);
	tmp[4] = cos(-rot.y / 2);
	tmp[5] = sin(-rot.y / 2);
	new.w = tmp[0] * tmp[2] * tmp[4] + tmp[1] * tmp[3] * tmp[5];
	new.x = tmp[0] * tmp[3] * tmp[4] - tmp[1] * tmp[2] * tmp[5];
	new.y = tmp[0] * tmp[2] * tmp[5] + tmp[1] * tmp[3] * tmp[4];
	new.z = tmp[1] * tmp[2] * tmp[4] - tmp[0] * tmp[3] * tmp[5];
	return (new);
}
