/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:55:50 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:27:34 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_substr_cpy(char *new_s, char const *s, int s_ind, size_t len)
{
	size_t			j;

	j = 0;
	while (s[s_ind] && j < len)
	{
		new_s[j] = s[s_ind];
		s_ind++;
		j++;
	}
	new_s[j] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	unsigned int	s_size;
	unsigned int	i;

	if (s == 0)
		return (0);
	s_size = ft_strlen(s);
	if (start >= s_size)
	{
		new_s = malloc(1);
		if (!new_s)
			return (0);
		new_s[0] = '\0';
		return (new_s);
	}
	if (len > s_size - start)
		len = s_size - start;
	new_s = malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (0);
	i = start;
	ft_substr_cpy(new_s, s, i, len);
	return (new_s);
}
