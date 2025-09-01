/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:14:58 by kikwasni          #+#    #+#             */
/*   Updated: 2025/01/16 09:05:38 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	b;
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	b = count * size;
	p = malloc(b);
	if (p == NULL)
	{
		return (NULL);
	}
	else
		ft_memset (p, 0, b);
	return (p);
}
// int  main()
// {
// 	 int *array = (int *)ft_calloc(5, sizeof(int)); 
//  if (!array) {
//  printf("Błąd alokacji pamięci!\n");
// eturn 1;
//}
//     for (int i = 0; i < 5; i++) {
// printf("%d ", array[i]); 
//}
// free(array); 
// return 0;
// }