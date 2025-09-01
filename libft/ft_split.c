/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:31:43 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/12 10:23:56 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_token(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while ((s[i]) && (s[i] != c))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**free_token(char **result, size_t token_index)
{
	while (token_index > 0)
		free(result[--token_index]);
	free(result);
	return (NULL);
}

static char	**tk(const char *s, char c, char **result)
{
	size_t	token_index;
	size_t	start;
	size_t	end;

	start = 0;
	token_index = 0;
	while (s[start])
	{
		while ((s[start]) && (s[start] == c))
			start++;
		if (s[start] == '\0')
			break ;
		end = start;
		while ((s[end]) && (s[end] != c))
			end++;
		result[token_index] = ft_substr(s, start, end - start);
		if (!result[token_index])
			free_token(result, token_index);
		token_index++;
		start ++;
		start = end;
	}
	result[token_index] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t	token_count;
	char	**result;

	if (!s)
		return (NULL);
	token_count = count_token(s, c);
	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (tk(s, c, result));
}
// int main()
// {
// 	char const *s = "hello,world!";
// 	char c = ',';
// 	char **result;
// 	int i = 0;
// 	result = ft_split(s, c);
// 	if (result == NULL)
// 	{
// 		return 1;
// 	}
// 	while (result[i] != NULL)
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return 0;
// }
