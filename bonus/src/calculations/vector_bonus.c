/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:03:03 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/21 11:15:56 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	is_aligned(t_vector u, t_vector v)
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
	if (fabs(u.x) <= 1e-6 && fabs(u.y) <= 1e-6 && fabs(u.z) <= 1e-6)
		return (1);
	return (0);
}

static void	get_vector(t_vector **vector_ptr, double x, double y, double z)
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

void	get_xyz(char *str, double *x, double *y, double *z)
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
	double		x;
	double		y;
	double		z;

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
