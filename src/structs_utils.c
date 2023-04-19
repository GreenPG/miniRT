/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:32:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 15:37:16 by gpasquet         ###   ########.fr       */
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

static void	get_o_vector(t_vector *vector, float x, float y, float z)
{
	vector->x_o = x;
	vector->y_o = y;
	vector->z_o = z;
	return ;
}

static void	get_d_vector(t_vector *vector, float x, float y, float z)
{
	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0)
	{
		ft_error("Vector components should be within the range of \
				-1.0 to 1.0\n");
		free(vector);
		vector = NULL;
		return ;
	}
	vector->x_d = x;
	vector->y_d = y;
	vector->z_d = z;
	return ;
}

t_vector	*init_vector(char *str)
{	
	t_vector	*vector;
	int			i;
	float		x;
	float		y;
	float		z;

	if (!str)
		return (NULL);
	vector = malloc(sizeof(t_vector));
	if (!vector)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	x = ft_atof(str);
	i = 0;
	while (str[i] != ',')
		i++;
	i++;
	y = ft_atof(str + i);
	while (str[i] != ',')
		i++;
	i++;
	z = ft_atof(str + i);
	get_o_vector(vector, x, y, z);
	if (!vector)
		return (NULL);
	while (ft_isdigit(str[i]) == 1 || str[i] == '.')
		i++;
	while (ft_isspace(str[i]) == 1)
		i++;
	x = ft_atof(str + i);
	while (str[i] != ',')
		i++;
	i++;
	y = ft_atof(str + i);
	while (str[i] != ',')
		i++;
	i++;
	z = ft_atof(str + i);
	get_d_vector(vector, x, y, z);
	return (vector);
}

int	*get_color_values(char	*str)
{
	int		*rgb;
	int		i;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	i = 0;
	rgb[0] = ft_atoi(str);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (NULL);
	rgb[1] = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (NULL);
	rgb[2] = ft_atoi(str + i);
	return (rgb);
}
