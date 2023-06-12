/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:18:08 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/09 17:26:02 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	quadratic(double a, double b, double c)
{
	double	d;
	double	r0;
	double	r1;

	d = (b * b) - (a * c);
	if (d > 0)
	{
		r0 = 1 * (-b - sqrt(d)) / a;
		r1 = 1 * (-b + sqrt(d)) / a;
		if (r0 > r1 && r1 >= 0)
			return (r1);
		else if (r1 >= r0 && r0 >= 0)
			return (r0);
		else if (r0 > 0)
			return (r0);
		else if (r1 > 0)
			return (r1);
	}
	return (INFINITY);
}

double	*cyl_quadratic(double a, double b, double c)
{
	double	d;
	double	*r;

	r = malloc(sizeof(double) * 2);
	if (!r)
	{
		ft_error("Error\n");
		return (NULL);
	}
	d = (b * b) - (a * c);
	if (d <= 0)
	{
		free(r);
		return (NULL);
	}
	r[0] = (-b - sqrt(d)) / a;
	r[1] = (-b + sqrt(d)) / a;
	return (r);
}

double	get_alpha(t_vector vec)
{
	return (atan2(vec.x, vec.y));
}

double	get_beta(t_vector vec)
{
	return (-atan2(vec.z, fabs(vec.y)));
}
