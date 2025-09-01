/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:29:53 by kikwasni          #+#    #+#             */
/*   Updated: 2025/04/24 14:13:57 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printer(void *ptr)
{
	int	len;

	len = 0;
	if ((unsigned long)ptr >= 16)
	{
		len += printer((void *)((unsigned long)ptr / 16));
		len += printer((void *)((unsigned long)ptr % 16));
	}
	else
	{
		ft_putchar("0123456789abcdef"[(unsigned long)ptr % 16]);
		len++;
	}
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	if (!ptr)
		return (ft_putstr("(nil)"));
	write(1, "0x", 2);
	return (printer(ptr) + 2);
}
