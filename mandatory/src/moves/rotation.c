/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/01 09:59:40 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/06/15 16:52:47 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt.h>

void	rotation_x(t_scene *scene, double angle)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_rot_x(scene->light, angle);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_rot_x(cursor->sphere, angle);
		if (cursor->type == plane)
			plane_rot_x(cursor->plane, angle);
		if (cursor->type == cylinder)
			cylinder_rot_x(cursor->cylinder, angle);
		cursor = cursor->next;
	}
}

void	rotation_y(t_scene *scene, double angle)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_rot_y(scene->light, angle);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_rot_y(cursor->sphere, angle);
		if (cursor->type == plane)
			plane_rot_y(cursor->plane, angle);
		if (cursor->type == cylinder)
			cylinder_rot_y(cursor->cylinder, angle);
		cursor = cursor->next;
	}
}

void	rotation_z(t_scene *scene, double angle)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_rot_z(scene->light, angle);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_rot_z(cursor->sphere, angle);
		if (cursor->type == plane)
			plane_rot_z(cursor->plane, angle);
		if (cursor->type == cylinder)
			cylinder_rot_z(cursor->cylinder, angle);
		cursor = cursor->next;
	}
}

void	world_rotate(t_scene *scene, double alpha, double beta, double theta)
{
	if (alpha)
		rotation_x(scene, -alpha * (M_PI / 180));
	if (beta)
		rotation_y(scene, beta * (M_PI / 180));
	if (theta)
		rotation_z(scene, -theta * (M_PI / 180));
	printf("alpha: %f\nbeta: %f\n\n", scene->camera->alpha, scene->camera->beta);
}
