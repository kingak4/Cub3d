/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:25:23 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 15:34:47 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr++ = '\0';
	}
}

// int main()
// {
// 	char	buffer[10] = "abcedfghij";
// 	int	i ;

// 	i = 0;
// 	ft_bzero(buffer, sizeof(buffer));
// 	while(i < 10)
// 	{
// 		printf("%d\n", buffer[i]);
// 		i++;
// 	}
// 	return(0);
// }
