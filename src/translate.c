/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/05 15:23:39 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/05/17 15:35:46 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt.h>

void	sphere_translate(t_sphere *sphere, double x, double y, double z)
{
	sphere->origin->x += x;
	sphere->origin->y += y;
	sphere->origin->z += z;
}

void	plane_translate(t_plane *plane, double x, double y, double z)
{
	plane->origin->x += x;
	plane->origin->y += y;
	plane->origin->z += z;
}

void	cylinder_translate(t_cylinder *cylinder, double x, double y, double z)
{
	cylinder->origin->x += x;
	cylinder->origin->y += y;
	cylinder->origin->z += z;
}

void	light_translate(t_light *light, double x, double y, double z)
{
	light->origin->x += x;
	light->origin->y += y;
	light->origin->z += z;
}

void	world_translate(t_scene *scene, double x, double y, double z)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_translate(scene->light, x, y, z);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_translate(cursor->sphere, x, y, z);
		if (cursor->type == plane)
			plane_translate(cursor->plane, x, y, z);
		if (cursor->type == cylinder)
			cylinder_translate(cursor->cylinder, x, y, z);
		cursor = cursor->next;
	}
}
