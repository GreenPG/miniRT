/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:19:34 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/08 15:46:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_putnbr_fd(long long int n, int fd)
{
	int				rec;
	long long int	nb_size;	

	nb_size = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		nb_size = 11;
	}
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
			nb_size++;
		}
		nb_size++;
		rec = (n % 10) + 48;
		if (n > 9)
			nb_size += ft_putnbr_fd((n / 10), fd);
		write(fd, &rec, 1);
	}
	return (nb_size);
}
