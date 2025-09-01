/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:27:15 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 12:22:51 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*x;
	unsigned char		i;

	x = (unsigned char *)s;
	i = (unsigned char )c;
	while (n--)
	{
		if (*x == i)
		{
			return ((void *)x);
		}
		x++;
	}
	return (NULL);
}

// int main()
// {
// 	char	s[] = "bigos";
// 	int	 c = 'g';
// 	char	*result;
// 	result = ft_memchr(s, c, 5);
// 	printf("%s\n", result);
// 	return(0);
// }
