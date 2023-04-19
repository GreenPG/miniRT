/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 17:50:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_plane(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_plane	*init_plane(char *str)
{
	t_plane	*plane;
	int		i;
	int		*rgb;

	if (!str || check_plane(str) == 1)
		return (NULL);
	plane = malloc(sizeof(t_plane));
	if (!plane)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	plane->vector = init_vector(str + i);
	if (!plane->vector)
	{
		free(plane);
		return (NULL);
	}
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free(plane);
		return (NULL);
	}
	plane->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	return (plane);
}
