/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:51:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 16:33:20 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_light(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_light	*init_light(char *str)
{
	t_light	*light;
	int		i;
	int		*rgb;

	if (!str || check_light(str) == 1)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (!light)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 1;
	while (ft_isspace(str[i]))
		i++;
	light->pos = get_coords(str + i);
	if (!light->pos)
	{
		free(light);
		return (NULL);
	}
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	light->brightness = ft_atof(str + i);
	if (light->brightness < 0 || light->brightness > 1)
	{
		ft_error("Light brightness must be within the range of 0 to 1\n");
		free(light);
		return (NULL);
	}
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free(light);
		return (NULL);
	}
	light->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (light);
}
