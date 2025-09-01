/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:28:16 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/13 12:08:20 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	len;
	unsigned int	i;

	len = 0;
	i = 0;
	if ((!src) || (!dest))
		return (0);
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while ((src[i]) && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

//int main()
//{
//	unsigned int	len;
//	const char	src[] = "hej, jak się masz?";
//	char	dest[4];
//	len = ft_strlcpy(dest, src, sizeof(dest));
//	printf("%u\n", len);
//	printf("%s\n", dest);
//	return(0);
//}
