/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:52:24 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:18:35 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	void	*ptr;
	int		len;

	if (nmenb > 2147483648 || size > 2147483648)
		return (0);
	ptr = malloc(nmenb * size);
	if (!ptr)
		return (0);
	len = nmenb * size;
	ft_bzero(ptr, len);
	return (ptr);
}
