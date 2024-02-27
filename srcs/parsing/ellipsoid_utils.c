/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellispoid_utlis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 09:20:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/27 09:20:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	null_all_el(t_ellipsoid *ellipsoid)
{
	ellipsoid->origin = NULL;
	ellipsoid->direction = NULL;
	ellipsoid->up = NULL;
}

int	calcul_el_ratio(t_ellipsoid *ellipsoid, float a, float b, float c)
{
	if (a == 0 || b == 0 || c == 0)
	{
		ft_error("Error\nEllipsoid ratio must be different to 0\n");
		return (1);
	}
	ellipsoid->a = 1. / (a * a);
	ellipsoid->b = 1. / (b * b);
	ellipsoid->c_std = c;
	ellipsoid->c = 1. / (c * c);
	return (0);
}
