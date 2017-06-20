/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:26:17 by pribault          #+#    #+#             */
/*   Updated: 2017/06/15 13:26:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"

void	smlx_invert_matrix(double **mat)
{
	mat[0][1] = -mat[0][1];
	mat[1][0] = -mat[1][0];
}

void	smlx_rotate_matrix(double **mat, int angle)
{
	double	rad;

	rad = (mat[0][1] < 0) ? acos(mat[0][0]) : -acos(mat[0][0]);
	rad += smlx_deg_to_rad(angle);
	mat[0][0] = cos(rad);
	mat[0][1] = -sin(rad);
	mat[1][0] = -mat[0][1];
	mat[1][1] = mat[0][0];
}

double	**smlx_copy_matrix(double **mat)
{
	double	**new;

	new = (double**)ft_alloc_array(2, 2, sizeof(double));
	new[0][0] = mat[0][0];
	new[0][1] = mat[0][1];
	new[1][0] = mat[1][0];
	new[1][1] = mat[1][1];
	return (new);
}

double	**smlx_create_matrix(int angle)
{
	double	**r;
	double	rad;

	r = (double**)ft_alloc_array(2, 2, sizeof(double));
	rad = smlx_deg_to_rad(angle);
	r[0][0] = cos(rad);
	r[0][1] = -sin(rad);
	r[1][0] = -r[0][1];
	r[1][1] = r[0][0];
	return (r);
}

void	smlx_destroy_matrix(double **mat)
{
	ft_free_array((void**)mat, 2);
}
