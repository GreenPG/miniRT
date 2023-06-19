/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:41:14 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 09:50:34 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_cylinder(t_cylinder **cylinder)
{
	if (!cylinder || !*cylinder)
		return ;
	if ((*cylinder)->origin)
		free((*cylinder)->origin);
	if ((*cylinder)->direction)
		free((*cylinder)->direction);
	free(*cylinder);
	*cylinder = NULL;
	return ;
}

void	free_sphere(t_sphere **sphere)
{
	if (!sphere || !*sphere)
		return ;
	if ((*sphere)->origin)
		free((*sphere)->origin);
	free(*sphere);
	*sphere = NULL;
	return ;
}

void	free_plane(t_plane **plane)
{
	if (!plane || !*plane)
		return ;
	if ((*plane)->direction)
	{
		free((*plane)->direction);
		(*plane)->direction = NULL;
	}
	if ((*plane)->origin)
	{
		free((*plane)->origin);
		(*plane)->origin = NULL;
	}
	free(*plane);
	*plane = NULL;
	return ;
}

void	free_ellipsoid(t_ellipsoid **ellipsoid)
{
	if (!ellipsoid || !*ellipsoid)
		return ;
	if ((*ellipsoid)->origin)
		free((*ellipsoid)->origin);
	if ((*ellipsoid)->direction)
		free((*ellipsoid)->direction);
	free(*ellipsoid);
	*ellipsoid = NULL;
	return ;
}

void	free_triangle(t_triangle **triangle_ptr)
{
	t_triangle	*triangle;

	triangle = *triangle_ptr;
	if (!triangle_ptr || !*triangle_ptr)
		return ;
	if (triangle->a)
		free(triangle->a);
	if (triangle->b)
		free(triangle->b);
	if (triangle->c)
		free(triangle->c);
	if (triangle->normal)
		free(triangle->normal);
	free(triangle);
	triangle = NULL;
	return ;
}
