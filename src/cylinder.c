/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 09:46:19 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_cylinder(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 2;
	while (ft_isspace(str[i]) == 1)
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
	if (check_int(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (check_int(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_cylinder	*init_cylinder(char *str)
{
	t_cylinder	*cylinder;
	int			i;
	int			*rgb;

	if(!str || check_cylinder(str) == 1)
		return (NULL);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	cylinder->vector = init_vector(str + i);
	if (!cylinder->vector)
	{
		free(cylinder);
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
	cylinder->diameter = ft_atof(str + i);
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]))
		i++;
	cylinder->height = ft_atof(str + i);
	if (cylinder->height <= 0 || cylinder->diameter <= 0)
	{
		ft_error("Cylinder diameter and height must be within the range of 0 to 1\n");
		free(cylinder);
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
		free(cylinder);
		return (NULL);
	}
	cylinder->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (cylinder);
}
