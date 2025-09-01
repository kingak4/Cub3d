/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:26:56 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 12:22:32 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}
// int main()
// {
//     char str[] = "hej 1!";
//     int i = 0;
//     while (str[i] != '\0')
//     {
//         if (!ft_isascii(str[i]))
//         {
//             printf("Nie jest ASCII: %c\n", str[i]);
//         }
//         i++;
//     }
//     return 0;
// }