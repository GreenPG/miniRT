/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:14:30 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/08 17:11:18 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	flag_checker(char *s, va_list var)
{
	int		ptd_cha;

	ptd_cha = 0;
	if (*s == 'c')
		ptd_cha += ft_putchar_fd(va_arg(var, int), 1);
	else if (*s == 's')
		ptd_cha += ft_putstr_fd((char *)va_arg(var, char *), 1);
	else if (*s == 'd' || *s == 'i')
		ptd_cha += ft_putnbr_fd(va_arg(var, int), 1);
	else if (*s == 'u')
		ptd_cha += ft_putnbr_fd((unsigned int)va_arg(var, unsigned int), 1);
	else if (*s == 'x')
		ptd_cha += ft_puthexa(va_arg(var, unsigned int), "0123456789abcdef");
	else if (*s == 'X')
		ptd_cha += ft_puthexa(va_arg(var, unsigned int), "0123456789ABCDEF");
	else if (*s == 'p')
		ptd_cha += ft_putptr((unsigned long int)va_arg(var, unsigned long int));
	else if (*s == '%')
		ptd_cha += ft_putchar_fd('%', 1);
	else
		s--;
	return (ptd_cha);
}

int	ft_printf(const char *s, ...)
{
	va_list	var;
	int		written_char;
	char	*str;

	str = (char *)s;
	va_start(var, s);
	written_char = 0;
	while (*str != '\0')
	{
		if (*str != '%')
			written_char += ft_putchar_fd(*str, 1);
		if (*str == '%')
		{
			str++;
			written_char += flag_checker(str, var);
		}
		str++;
	}
	return (written_char);
}
