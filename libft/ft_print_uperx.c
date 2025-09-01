/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uperx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:15 by kikwasni          #+#    #+#             */
/*   Updated: 2025/04/24 14:14:08 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_upperx(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb >= 16)
	{
		i += ft_print_upperx(nb / 16);
		i += ft_print_upperx(nb % 16);
	}
	else
	{
		if (nb >= 10)
			ft_putchar("ABCDEF"[(nb % 16) - 10]);
		else
		{
			nb += '0';
			ft_putchar(nb);
		}
		i ++;
	}
	return (i);
}

//int main()
//{
//	int	nb = 1;
//	ft_printX(nb);
//	return(0);
//}
//write(1, &tmp[7 % 16], 1);
//i wtedy mamy tmp[7]