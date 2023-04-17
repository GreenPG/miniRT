/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:47:32 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 17:03:04 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_path(char *path)
{
	int		start;
	char	*extension;

	start = ft_strlen(path) - 3;
	extension = ft_substr(path, start, 3);
	if (ft_strncmp(extension, ".rt", 3) != 0)
	{
		free(extension);
		return (1);
	}
	free(extension);
	return (0);
}

t_ambiant_l	*init_ambiant_l(char *input)
{
	t_ambiant_l	*ambiant_l;
	int			i;

	ambiant_l = malloc(sizeof(t_ambiant_l));
	if (!ambiant_l)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 1;
	while (input[i])
		i++;
	return (NULL);
}
