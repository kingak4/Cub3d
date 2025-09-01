/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:28:21 by kikwasni          #+#    #+#             */
/*   Updated: 2025/05/13 09:49:45 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*one_line(char *buffer)
{
	int		id;
	char	*c;
	int		i;

	i = 0;
	id = -1;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			id = i;
			break ;
		}
		i++;
	}
	if (id >= 0)
		c = ft_substr1(buffer, 0, id + 1);
	else
		c = ft_substr1(buffer, 0, ft_strlen(buffer));
	return (c);
}

char	*next_res(char *rest)
{
	char	*new_res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	new_res = NULL;
	if (!rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	len = ft_strlen1(rest) - i;
	if (len > 0)
		new_res = ft_calloc1(len, 1);
	i++;
	while (i < ft_strlen1(rest) && rest[i])
	{
		new_res[j] = rest[i];
		j++;
		i++;
	}
	free(rest);
	return (new_res);
}

char	*add_to_rest(char *rest, char *buffer)
{
	char	*r;

	if (rest == NULL)
	{
		rest = (char *)ft_calloc1(BUFFER_SIZE + 1, 1);
		if (!rest)
			return (NULL);
	}
	r = ft_strjoin1(rest, buffer);
	free(rest);
	rest = r;
	if (!rest)
	{
		free(buffer);
		return (NULL);
	}
	return (rest);
}

char	*read_buffer(int fd, char *rest, int bytes_read)
{
	char	*buffer;

	if (!rest)
		rest = ft_calloc1(1, 1);
	buffer = ft_calloc1(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			free(rest);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		rest = add_to_rest(rest, buffer);
	}
	free (buffer);
	if (rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*r;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r = read_buffer(fd, rest, 1);
	if (!r)
		return (NULL);
	line = one_line(r);
	rest = next_res(r);
	return (line);
}

//int main()
//{
//	int fd = open("hey.txt", O_RDONLY);
//	char *x;
//	x = get_next_line(fd);
//		printf("%s", x);
//	free(x);
//	x = get_next_line(fd);
//		printf("%s", x);
//		free(x);
//		return (0);
//}