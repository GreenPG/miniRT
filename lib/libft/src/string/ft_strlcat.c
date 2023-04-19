/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:56:48 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:25:35 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;
	size_t	ret;

	i = 0;
	if (dst == 0 && size == 0)
		return (0);
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size < dest_len + 1)
		return (src_len + size);
	while (src[i] && (i + dest_len) < size - 1)
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = 0;
	if (size < dest_len)
		ret = size + src_len;
	else
		ret = dest_len + src_len;
	return (ret);
}
