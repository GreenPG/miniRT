/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:32:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/17 17:15:59 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_coords	*get_coords(char *str)
{
	t_coords	*coords;
	int			i;
	float		x;
	float		y;
	float		z;

	if (!str)
		return (NULL);
	x = ft_atof(str);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1 || str[i] == '.')
		i++;
	i++;
	y = ft_atof(str + i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1 || str[i] == '.')
		i++;
	i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	z = ft_atof(str + i);
	coords = init_coords(x, y, z);
	if (!coords)
		return (NULL);
	return (coords);
}

t_coords	*init_coords(float x, float y, float z)
{
	t_coords	*coords;

	coords = malloc(sizeof(t_coords));
	if (!coords)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	coords->x = x;
	coords->y = y;
	coords->z = z;
	return (coords);
}

t_vector	*get_vector(char *str)
{	
	t_vector	*vector;
	int			i;
	float		x;
	float		y;
	float		z;

	if (!str)
		return (NULL);
	x = ft_atof(str);
	i = 0;
	while (ft_isdigit(str[i]) == 1 || str[i] == '.')
		i++;
	i++;
	y = ft_atof(str + i);
	while (ft_isdigit(str[i]) == 1 || str[i] == '.')
		i++;
	i++;
	z = ft_atof(str + i);
	vector = init_vector(x, y, z);
	if (!vector)
		return (NULL);
	return (vector);
}

t_vector	*init_vector(float x, float y, float z)
{
	t_vector	*vector;

	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0)
	{
		ft_error("Vector components should be within the range of \
				-1.0 to 1.0\n");
		return (NULL);
	}
	vector = malloc(sizeof(t_vector));
	if (!vector)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

int	get_color(char	*str)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	r = ft_atoi(str);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (-1);
	g = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (-1);
	b = ft_atoi(str + i);
	return (get_rgba(r, g, b, 255));
}
