/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:23:20 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/04 12:43:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_printhexa(unsigned int nb, unsigned int size_base, char *base)
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
		ft_printhexa(n / size_base, size_base, base);
	}
	written_size++;
	write(1, &rec, 1);
	return (written_size);
}

int	ft_puthexa(unsigned int nb, char *base)
{
	int				i;
	int				j;
	int				written_size;

	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (-1);
		while (j < i)
		{
			if (base[j] == base[i])
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	written_size = 0;
	if (i >= 2)
		written_size = ft_printhexa(nb, i, base);
	return (written_size);
}
