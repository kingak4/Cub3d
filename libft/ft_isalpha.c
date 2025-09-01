/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:19:24 by kikwasni          #+#    #+#             */
/*   Updated: 2024/12/17 12:22:26 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}
// int main()
// {
//     char str[] = "AaBBcc44";
//     int i = 0;
//     while (str[i] != '\0')
//     {
//         if (!ft_isalpha(str[i]))
//         {
//             printf("Nie jest literą: %c\n", str[i]);
//         }
//         i++;
//     }
//     return 0;
// }