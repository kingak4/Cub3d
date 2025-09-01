/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:01 by kikwasni          #+#    #+#             */
/*   Updated: 2025/04/24 14:14:15 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_check(char c, va_list args)
{
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int )));
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)), 1);
	if (c == 'x')
		return (ft_printx(va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_print_upperx(va_arg(args, unsigned int)));
	if (c == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	if (c == '%')
		return (write(1, "%", 1), 1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1])
			count += format_check(format[++i], args);
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

//#include <stdio.h>
//#include <limits.h>
//int main()
//{
//	printf("%d", ft_printf("tak"));
//	printf("\n");
//	ft_printf("tak");
//	printf("\n\n");

//	printf("tak%s", "tak");
//	printf("\n");
//	ft_printf("tak%s", "tak");
//	printf("\n\n");

//	printf("tak%ldtak", -2147483648);
//	printf("\n");
//	printf( "%d", ft_printf("%d", -2147483644));
//	printf("\n\n");

//	printf("%c", 'b');
//	printf("\n");
//	printf( "%d", ft_printf("%c", 'b'));
//	printf("\n\n");

//	printf("%%");
//	printf("\n");
//	ft_printf("%%");
//	printf("\n\n");

//	printf("tak");
//	printf("\n");
//	ft_printf("tak");
//	printf("\n\n");

//	printf("%x", 20000);
//	printf("\n");
//	ft_printf("%x", 20000);
//	printf("\n\n");

	//printf("%d\n",printf("%X\n", -42));
	//printf("\n");
	//printf("%d\n",ft_printf("%X\n", -42));
	//printf("\n\n");

//	printf("%d\n",printf("%d\n", 0));
//	printf("%d\n",ft_printf("%d\n", 0));

//	printf("Test 6: printf(\" %%p %%p \", LONG_MIN, LONG_MAX)\n");
//	printf("   printf: %p %p\n", (void *)LONG_MIN, (void *)LONG_MAX);
//	ft_printf("ft_printf: %p %p\n", (void *)LONG_MIN, (void *)LONG_MAX);

//	printf("\nTest 7: printf(\" %%p %%p \", INT_MIN, INT_MAX)\n");
//	printf("   printf: %p %p\n", (void *)INT_MIN, (void *)INT_MAX);
//	ft_printf("ft_printf: %p %p\n", (void *)INT_MIN, (void *)INT_MAX);
//	return (0);
//}