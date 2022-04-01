/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:31:41 by lbattest          #+#    #+#             */
/*   Updated: 2022/02/17 10:54:02 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calling(char *fmt, int i, va_list args)
{
	int	len;

	len = 0;
	if (fmt[i] == 'c')
		len += ft_putchar_mod(va_arg(args, int));
	else if (fmt[i] == 'd' || fmt[i] == 'i')
		len += ft_putnbr_mod(va_arg(args, int));
	else if (fmt[i] == 's')
		len += ft_putstr_mod(va_arg(args, char *));
	else if (fmt[i] == 'u')
		len += ft_uns_putnbr_mod(va_arg(args, unsigned int));
	else if (fmt[i] == 'x')
		len += to_hexa(va_arg(args, unsigned int), "0123456789abcdef");
	else if (fmt[i] == 'X')
		len += to_hexa(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (fmt[i] == '%')
		len += ft_putchar_mod('%');
	else if (fmt[i] == 'p')
	{
		len += ft_putstr_mod("0x");
		len += adress(va_arg(args, uint64_t));
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	int		i;
	va_list	args;
	int		len;

	len = 0;
	va_start(args, fmt);
	i = 0;
	while (fmt[i])
	{
		while (fmt[i] != '%' && fmt[i])
			len = ft_putchar_mod(fmt[i++]);
		if (fmt[i] == '%')
		{
			len += calling((char *)fmt, i + 1, args);
			i += 2;
		}
	}
	va_end(args);
	return (len);
}
