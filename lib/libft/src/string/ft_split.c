/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:09:41 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:14:23 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_free(char **s_tab)
{
	int	i;

	i = 0;
	while (s_tab[i])
	{
		free(s_tab[i]);
		i++;
	}
	free(s_tab);
}

static int	ft_word_count(const char *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (word_count);
}

static char	*ft_fill_str(char *new_s, const char *s, int s_ind, char c)
{
	int	start;		
	int	word_size;	

	start = s_ind;
	while (s[s_ind] && s[s_ind] != c)
		s_ind++;
	word_size = s_ind - start;
	new_s = ft_substr(s, start, word_size);
	if (!new_s)
		return (0);
	return (new_s);
}

static void	ft_tab_browsing(char **s_tab, const char *s, char c)
{
	int	tab_ind;
	int	i;

	i = 0;
	tab_ind = 0;
	while (s[i])
	{
		if (s[i] != c)
		{	
			s_tab[tab_ind] = ft_fill_str(s_tab[tab_ind], s, i, c);
			if (!s_tab[tab_ind])
			{
				ft_free(s_tab);
				return ;
			}
			i += ft_strlen(s_tab[tab_ind]);
			tab_ind++;
		}			
		while (s[i] != '\0' && s[i] == c)
					i++;
	}
	s_tab[tab_ind] = 0;
}

char	**ft_split(const char *s, char c)
{
	char	**s_tab;
	int		word_count;

	if (s == 0)
	{	
		s_tab = malloc(sizeof(char *));
		s_tab[0] = 0;
		return (s_tab);
	}
	word_count = ft_word_count(s, c);
	s_tab = malloc(sizeof(char *) * (word_count + 1));
	if (!s_tab)
		return (0);
	ft_tab_browsing(s_tab, s, c);
	return (s_tab);
}
