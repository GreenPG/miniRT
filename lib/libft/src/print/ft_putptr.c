/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:23:19 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/08 17:14:00 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_putnbr(unsigned long int nb, unsigned int size_base, char *base)
{
	int					rec;
	int					j;
	static int			written_size;
	unsigned long int	n;

	j = 0;
	written_size = 0;
	n = nb;
	rec = (n % size_base);
	while (base[j])
	{
		if (rec == j)
			rec = base[j];
		j++;
	}
	if (n >= size_base)
	{	
		ft_putnbr(n / size_base, size_base, base);
	}
	written_size++;
	write(1, &rec, 1);
	return (written_size);
}

int	ft_putptr(unsigned long int nb)
{
	int				written_size;

	if (nb == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	written_size = 2;
	written_size += ft_putnbr(nb, 16, "0123456789abcdef");
	return (written_size);
}
