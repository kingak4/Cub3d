/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:27:31 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/03 14:47:04 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	s = (const char *) src;
	d = (char *) dest;
	i = 0;
	if ((!d) || (!s))
		return (NULL);
	if (d > s)
	{
		while (n-- > 0)
		{
			d[n] = s[n];
		}
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
//int main()
//{
//	char	d[4] = "";
//	char	s[] = "elo";
//	ft_memmove(d, s, 3);
//	 d[3] = '\0';
//	printf("%s\n", d );
//	return(0);
//}