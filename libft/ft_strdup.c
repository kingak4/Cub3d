/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:15:40 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 12:24:03 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	str = (char *) malloc(sizeof(*str) * (i + 1));
	if (!str)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main()
{
	char	s[] ="srebrny";

	char	*duplicated = ft_strdup(s);
	printf("%s\n", duplicated);
	free(duplicated);
	return(0);

}
*/