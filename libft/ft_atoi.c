/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:27:17 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/02 14:08:00 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	a;

	sign = 1;
	result = 0;
	a = 0;
	while ((nptr[a] == 32) || (nptr[a] >= 9 && nptr[a] <= 13))
	{
		a++;
	}
	if (nptr[a] == '+')
		a++;
	else if (nptr[a] == '-')
	{
		sign = -1;
		a++;
	}
	while ((nptr[a] >= '0') && (nptr[a] <= '9'))
	{
		result = result * 10 + nptr[a] - '0';
		a++;
	}
	return (sign * result);
}
//int main()
//{
//	const char *n = "-4886";
//	printf("%d\n",ft_atoi(n));
//	return(0);
//}