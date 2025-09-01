/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:27:37 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 12:23:23 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n--)
	{
		*ptr++ = (unsigned char)c;
	}
	return (str);
}
/*
int main()
{
char	buffer[10];
int i = 0;
ft_memset(buffer, 'A', sizeof(buffer));
while ( i < 10)
{
printf("%c ", buffer[i]);
i++;
}
return(0);
}
*/