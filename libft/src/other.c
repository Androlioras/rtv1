/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:39:16 by pribault          #+#    #+#             */
/*   Updated: 2017/01/13 16:13:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

int		is_number(const char *f, int *i)
{
	if (f[*i] >= 49 && f[*i] <= 57)
		return (1);
	if (f[*i] == '+' || f[*i] == '-')
		if (f[*i + 1] >= '0' && f[*i + 1] <= '9')
			return (1);
	return (0);
}

int		ft_atoi2(const char *str, int *i)
{
	int		negative;
	int		number;

	negative = 1;
	number = 0;
	if (str[*i] == '+' || str[*i] == '-')
		negative = 44 - str[(*i)++];
	if (str[*i] == '0')
		return (0);
	while (str[*i] < 58 && str[*i] > 47)
		number = number * 10 + str[(*i)++] - 48;
	return (number * negative);
}
