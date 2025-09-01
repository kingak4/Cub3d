/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:27:24 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/22 18:57:03 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if ((!dest) && (!src))
	{
		return (NULL);
	}
	d = (char *) dest;
	s = (char *) src;
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}
//#include <stdio.h>

//int main()
//{
//	char	src[] = "czesc";
//	char	dest[6];
//	ft_memcpy(dest, src, 6);
//	dest[5] = '\0';
//	printf("%s\n", dest);
//	return(0);
//}