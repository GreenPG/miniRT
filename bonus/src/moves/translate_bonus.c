/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   translate_bonus.c                                  :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/05 15:23:39 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/06/08 16:04:27 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	light_translate(t_light_list *light_list, double x, double y,
		double z)
{
	t_light_list	*tmp;

	tmp = light_list;
	while (tmp)
	{
		tmp->light->origin->x += x;
		tmp->light->origin->y += y;
		tmp->light->origin->z += z;
		tmp = tmp->next;
	}
}

void	world_translate(t_scene *scene, double x, double y, double z)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_translate(scene->light_list, x, y, z);
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
