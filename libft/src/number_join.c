/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2017/03/25 17:02:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"
#include <stdio.h>

static size_t	numberlen(long long int nbr)
{
	size_t	len;

	len = 1;
	while (nbr / 10)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

void			print_number(va_list va, char *new, size_t *j)
{
	long long int	nbr;
	long long int	pow;
	char			c;

	nbr = va_arg(va, long long int);
	pow = 1;
	while (pow * 10 <= nbr)
		pow *= 10;
	while (pow > 0)
	{
		c = nbr / pow;
		new[(*j)++] = c + '0';
		nbr -= c * pow;
		pow /= 10;
	}
}

size_t			get_number_len(va_list va)
{
	long long int	nbr;

	nbr = va_arg(va, long long int);
	return (numberlen(nbr));
}
