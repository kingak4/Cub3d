/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:12:37 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/09 14:07:24 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*s3;

	if ((s1 == NULL) || (s2 == NULL))
	{
		return (NULL);
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (!s3)
	{
		return (NULL);
	}
	ft_strlcpy(s3, s1, len_s1 + 1);
	ft_strlcat(s3, s2, (len_s1) + len_s2 + 1);
	return (s3);
}
//int main()
//{
//	char	*s1 = "jasno";
//	char	*s2 = "widz";
//	char	*result;
//	result = ft_strjoin(s1, s2);
//	printf("%s\n", result);
//	free(result);
//	return(0);
//}