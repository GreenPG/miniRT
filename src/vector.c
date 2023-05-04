/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:57:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/04 17:03:24 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x_o = 0;
	result.y_o = 0;
	result.z_o = 0;
	result.x_d = (a.y_d * b.z_d) - (a.z_d * b.y_d);
	result.y_d = (a.x_d * b.z_d) - (a.z_d * b.x_d);
	result.z_d = (a.x_d * b.y_d) - (a.y_d * b.x_d);
	return (result);
}

double	dot_product(t_vector v, t_vector u)
{
	return (v.x_d * u.x_d + v.y_d * u.y_d + v.z_d * u.z_d);
}

static void	get_o_vector(t_vector *vector, float x, float y, float z)
{
	vector->x_o = x;
	vector->y_o = y;
	vector->z_o = z;
	return ;
}

static void	get_d_vector(t_vector **vector_ptr, float x, float y, float z)
{
	t_vector	*vector;

	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0)
	{
		ft_error("Vector components should be within the range of \
				-1.0 to 1.0\n");
		free(*vector_ptr);
		*vector_ptr = NULL;
		return ;
	}
	if (!vector_ptr || !*vector_ptr)
		return ;
	vector = *vector_ptr;
	vector->x_d = x;
	vector->y_d = y;
	vector->z_d = z;
	return ;
}

void	get_xyz(char *str, float *x, float *y, float *z)
{
	int	i;

	i = 0;
	*x = ft_atof(str);
	while (str[i] != ',')
		i++;
	i++;
	*y = ft_atof(str + i);
	while (str[i] != ',')
		i++;
	i++;
	*z = ft_atof(str + i);
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
	get_xyz(str, &x, &y, &z);
	get_o_vector(vector, x, y, z);
	if (!vector)
		return (NULL);
	i = 0;
	pass_to_next_element(str, &i);
	get_xyz(str + i, &x, &y, &z);
	get_d_vector(&vector, x, y, z);
	return (vector);
}
