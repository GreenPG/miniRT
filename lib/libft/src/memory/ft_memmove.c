/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:19:36 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:19:54 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_src_sup_dest(char *sdest, const char *ssrc, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		sdest[i] = ssrc[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*sdest;
	const char	*ssrc;

	if (dest == 0 && src == 0)
		return (0);
	sdest = dest;
	ssrc = src;
	if (ssrc > sdest)
		ft_src_sup_dest(sdest, ssrc, n);
	else
	{
		while (n > 0)
		{	
			sdest[n - 1] = ssrc[n - 1];
			n--;
		}
	}
	return (dest);
}
