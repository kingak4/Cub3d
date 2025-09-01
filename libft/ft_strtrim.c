/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:13:13 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/08 16:46:28 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

//char	*ft_strchr(const char *s, int c)
//{
//	int	i;

//	i = 0;
//	if (!s)
//		return (NULL);
//	while (s[i] != '\0')
//	{
//		if (s[i] == c)
//			return ((char *) s + i);
//		else
//			i++;
//	}
//	if (c == '\0')
//		return ((char *) s + i);
//	return (NULL);
//}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			start;
	int			end;
	char		*trimmed;
	size_t		len;

	if (!s1)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	start = 0;
	while ((s1[start]) && (ft_strchr(set, s1[start])))
		start++;
	len = ft_strlen(s1);
	end = len - 1;
	while ((end >= 0) && (ft_strchr(set, s1[end])))
		end--;
	if (start > end)
		return (ft_strdup(""));
	trimmed = malloc(end - start + 2);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + start, end - start + 1);
	trimmed[end - start + 1] = '\0';
	return (trimmed);
}
//int main()
//{
//	const char	*s1 = "          ";
//	const char	*set = " ";
//	char		*trimmed;

//	trimmed = strtrim(s1, set);
//	printf("%s\n", trimmed);
//	return (0);
//}