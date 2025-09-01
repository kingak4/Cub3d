/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:00 by kikwasni          #+#    #+#             */
/*   Updated: 2025/04/24 14:14:21 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printx(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 16)
	{
		i += ft_printx(n / 16);
		i += ft_printx(n % 16);
	}
	else
	{
		if (n >= 10)
			ft_putchar("abcdef"[(n % 16) - 10]);
		else
		{
			n += '0';
			ft_putchar(n);
		}
		i ++;
	}
	return (i);
}
