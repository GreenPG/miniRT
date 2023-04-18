/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:11:47 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/18 13:12:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_sphere(char *input)
{
	int	i;

	if (!input)
		return (-1);
	i = 2;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_int(input, &i) == 1)
		return (1);
	return (0);
}

t_sphere	*init_sphere(char *input)
{
	int			i;
	t_sphere	*sphere;
	int			*rgb;

	if (!input || check_sphere(input) == 1)
		return (NULL);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	i = 2;
	while (ft_isspace(input[i]) == 1)
		i++;
	sphere->pos = get_coords(input + i);
	if (!sphere->pos)
	{
		free(sphere);
		return (NULL);
	}
	while (ft_isspace(input[i]) == 0)
		i++;
	while (ft_isspace(input[i]) == 1)
		i++;
	sphere->diameter = ft_atof(input + i);
	if (sphere->diameter <= 0)
	{
		free(sphere);
		return (NULL);
	}
	while (ft_isspace(input[i]) == 0)
		i++;
	while (ft_isspace(input[i]) == 1)
		i++;
	rgb = get_color_values(input + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free(sphere);
		return (NULL);
	}
	sphere->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (sphere);
}
