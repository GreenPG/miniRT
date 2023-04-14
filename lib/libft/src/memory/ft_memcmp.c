/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:12:22 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:19:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*news1;
	const char	*news2;
	int			a;
	int			b;

	news1 = s1;
	news2 = s2;
	i = 0;
	while (i < n)
	{
		if (news1[i] != news2[i])
		{
			a = news1[i] % 256;
			if (a < 0)
				a += 256;
			b = news2[i] % 256;
			if (b < 0)
				b += 256;
			return (a - b);
		}
		i++;
	}
	return (0);
}
