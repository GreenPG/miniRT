/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:32:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/13 17:54:18 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	get_to_next_int(char *str, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	while (ft_isdigit(str[*i]) == 1 || str[*i] == '.')
		(*i)++;
	(*i)++;
}

t_vector	*get_coords(char *str)
{
	t_vector	*coords;
	int			i;
	float		x;
	float		y;
	float		z;

	if (!str)
		return (NULL);
	i = 0;
	x = ft_atof(str);
	get_to_next_int(str, &i);
	y = ft_atof(str + i);
	get_to_next_int(str, &i);
	z = ft_atof(str + i);
	coords = init_coords(x, y, z);
	if (!coords)
		return (NULL);
	return (coords);
}

t_vector	*init_coords(float x, float y, float z)
{
	t_vector	*coords;

	coords = malloc(sizeof(t_vector));
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
