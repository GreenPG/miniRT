/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculations2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:16:07 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 10:51:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	min_cyl(double t_1, double t_2, double t_3, double t_4)
{
	double	min;

	min = INFINITY;
	if (t_1 > 0 && t_1 < min)
		min = t_1;
	if (t_2 > 0 && t_2 < min)
		min = t_2;
	if (t_3 > 0 && t_3 < min)
		min = t_3;
	if (t_4 > 0 && t_4 < min)
		min = t_4;
	return (min);
}

void	free_cyl_roots(double *root, double *caps)
{
	if (root)
		free(root);
	if (caps)
		free(caps);
}
