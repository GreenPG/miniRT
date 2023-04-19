/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:10:22 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	*ft_search(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	int		a;

	i = 0;
	little_len = ft_strlen(little);
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			a = 0;
			while (little[j] && (i + j) < len)
			{
				if (big[i + j] != little[j])
					a++;
				j++;
			}
			if (a == 0 && j == little_len)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;
	size_t	little_len;

	if (len == 0 && big == 0)
		return (0);
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	ptr = ft_search(big, little, len);
	if (ptr != 0)
		return (ptr);
	else
		return (0);
}
