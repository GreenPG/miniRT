/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:11:12 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:31 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	i;
	int					a;
	int					b;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{	
			a = s1[i];
			if (a < 0)
				a += 256;
			a = a % 256;
			b = s2[i];
			if (b < 0)
				b += 256;
			b = b % 256;
			return (a - b);
		}
		i++;
	}
	return (0);
}
