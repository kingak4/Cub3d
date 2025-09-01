/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:28:39 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/07 09:23:23 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	j = 0;
	while ((i < len) && (big[i] != '\0'))
	{
		j = 0;
		while ((i + j < len) && (big[i + j] == little[j])
			&& (little[j] != '\0'))
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
//int main ()
//{
//	char	*big = "Witam serdecznie ";
//	char	*little = "serdecznie";
//	printf("%s\n", ft_strnstr(big, little, 20));
//	return(0);
//}
