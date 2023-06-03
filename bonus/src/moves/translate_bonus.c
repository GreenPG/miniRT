/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/05 15:23:39 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/05/18 09:14:56 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

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
		if (cursor->type == ellipsoid)
			ellipsoid_translate(cursor->ellipsoid, x, y, z);
		cursor = cursor->next;
	}
}
