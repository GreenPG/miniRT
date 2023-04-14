/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:20:08 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:27:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_search_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	sep_mark;

	i = 0;
	while (s1[i])
	{
		j = 0;
		sep_mark = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				sep_mark++;
			j++;
		}
		if (sep_mark == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_search_end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	sep_mark;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		j = 0;
		sep_mark = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				sep_mark++;
			j++;
		}
		if (sep_mark == 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_s;
	int		start_ind;
	int		end_ind;
	int		trimmed_s_len;

	if (!s1 || !set)
		return (0);
	start_ind = ft_search_start(s1, set);
	end_ind = ft_search_end(s1, set) + 1;
	trimmed_s_len = end_ind - start_ind;
	if (end_ind < start_ind)
	{
		trimmed_s = ft_calloc(1, sizeof(char));
		trimmed_s[0] = '\0';
		return (trimmed_s);
	}
	trimmed_s = ft_substr(s1, start_ind, trimmed_s_len);
	return (trimmed_s);
}
