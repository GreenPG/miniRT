/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:57:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/15 10:29:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	scalar_multiplication(t_vector *vector, double scalar)
{
	//ca jse po comment faire pour l instant je sais pas comment tu l utilise
	t_vector	result;

	// result.x_o = vector->x_o;
	// result.y_o = vector->y_o;
	// result.z_o = vector->z_o;
	// result.x_d = (vector->x_o + vector->x_d) * scalar;
	// result.x_d = (vector->y_o + vector->y_d) * scalar;
	// result.x_d = (vector->z_o + vector->z_d) * scalar;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x = (vector->x + vector->x) * scalar;
	result.x = (vector->y + vector->y) * scalar;
	result.x = (vector->z + vector->z) * scalar;
	return (result);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.x * b.z) + (a.z * b.x);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

double	dot_product(t_vector v, t_vector u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

static void	get_vector(t_vector **vector_ptr, float x, float y, float z)
{
	t_vector	*vector;

	if (!vector_ptr || !*vector_ptr)
		return ;
	vector = *vector_ptr;
	vector->x = x;
	vector->y = y;
	vector->z = z;
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
	get_vector(&vector, x, y, z);
	if (!vector)
		return (NULL);
	return (vector);
}
