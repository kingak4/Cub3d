/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:15:35 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 12:23:45 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		return ;
	}
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
// int main()
// {
// 	char	*s = "hi";

// 	ft_putstr_fd(s, 1);
// 	return(0);
// }