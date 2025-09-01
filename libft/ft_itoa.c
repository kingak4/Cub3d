/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:38:54 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/14 13:04:41 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*safe_malloc(int sign, int len)
{
	char	*result;

	result = malloc(sign + len + 1);
	if (!result)
		return (NULL);
	result[sign + len] = '\0';
	if (sign == 1)
		result[0] = '-';
	return (result);
}

static void	check_sign(int *sign, unsigned int *tmp, int n)
{
	if (n < 0)
	{
		*sign = 1;
		*tmp = -n;
	}
	else
	{
		*tmp = n;
		*sign = 0;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	tmp;
	unsigned int	temp;
	int				len;
	int				sign;
	char			*result;

	check_sign(&sign, &tmp, n);
	len = 1;
	temp = tmp;
	while (temp >= 10)
	{
		temp = temp / 10;
		len++;
	}
	result = safe_malloc(sign, len);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[len + sign - 1] = (tmp % 10) + '0';
		tmp = tmp / 10;
		len--;
	}
	return (result);
}

//int main(void)
//{
//	int	n = -123;
//	char	*s;

//	s = ft_itoa(n);
//	printf("%s\n", s);
//	free(s);
//	return(0);
//}