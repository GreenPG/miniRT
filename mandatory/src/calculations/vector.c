/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/19 08:57:28 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/06/15 16:48:24 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt.h>

void	vector_norm(t_vector *vec)
{
	double	len;

	len = sqrt(dot_product(*vec, *vec));
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
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
