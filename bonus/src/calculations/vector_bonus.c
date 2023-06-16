/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/19 08:57:28 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/06/16 13:23:08 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

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
