/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:42:02 by pribault          #+#    #+#             */
/*   Updated: 2016/11/09 21:07:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str)
{
	int		negative;
	int		number;
	int		i;

	negative = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14) || str[i] == 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
		negative = 44 - str[i++];
	while (str[i] < 58 && str[i] > 47)
		number = number * 10 + str[i++] - 48;
	return (number * negative);
}
