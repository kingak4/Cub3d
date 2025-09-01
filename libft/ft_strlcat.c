/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:27:55 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/14 11:57:46 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!dest) || (!src))
		return (0);
	while ((dest[i] != '\0') && (i < size))
		i++;
	if (size == 0)
		return (ft_strlen(src));
	if (i == size)
		return (size + ft_strlen(src));
	while ((src[j] != '\0') && (i + j < size - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return ((i + j) + (ft_strlen(src + j)));
}
// int main()
// {
// 	char	dest[30] = "hejka";
// 	char	src[] = " jak tam ?";
// 	size_t	result;
// 	result = ft_strlcat(dest, src, sizeof(dest));
// 	printf("%zu\n", result);
// 	printf("%s\n", dest);
// 	return(0);
// }
