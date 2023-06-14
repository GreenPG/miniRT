/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/01 09:59:40 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/06/14 16:57:59 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

void	vector_rot_x(t_vector *vec, double angle)
{
	t_vector	axis;

	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	rotate_around_axis(vec, axis, angle);
}

void	rotation_x(t_scene *scene, double angle)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_rot_x(scene->light_list, angle);
	world_rot_x(scene, angle);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_rot_x(cursor->sphere, angle);
		if (cursor->type == plane)
			plane_rot_x(cursor->plane, angle);
		if (cursor->type == cylinder)
			cylinder_rot_x(cursor->cylinder, angle);
		if (cursor->type == ellipsoid)
			ellipsoid_rot_x(cursor->ellipsoid, angle);
		if (cursor->type == triangle)
			triangle_rot_x(cursor->triangle, angle);
		cursor = cursor->next;
	}
}

void	vector_rot_y(t_vector *vec, double angle)
{
	t_vector	axis;

	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	rotate_around_axis(vec, axis, angle);
	
}

void	rotation_y(t_scene *scene, double angle)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_rot_y(scene->light_list, angle);
	world_rot_y(scene, angle);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_rot_y(cursor->sphere, angle);
		if (cursor->type == plane)
			plane_rot_y(cursor->plane, angle);
		if (cursor->type == cylinder)
			cylinder_rot_y(cursor->cylinder, angle);
		if (cursor->type == ellipsoid)
			ellipsoid_rot_y(cursor->ellipsoid, angle);
		if (cursor->type == triangle)
			triangle_rot_y(cursor->triangle, angle);
		cursor = cursor->next;
	}
}

void	vector_rot_z(t_vector *vec, double angle)
{
	t_vector	axis;

	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	rotate_around_axis(vec, axis, angle);
}

void	rotation_z(t_scene *scene, double angle)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	light_rot_z(scene->light_list, angle);
	world_rot_z(scene, angle);
	while (cursor)
	{
		if (cursor->type == sphere)
			sphere_rot_z(cursor->sphere, angle);
		if (cursor->type == plane)
			plane_rot_z(cursor->plane, angle);
		if (cursor->type == cylinder)
			cylinder_rot_z(cursor->cylinder, angle);
		if (cursor->type == ellipsoid)
			ellipsoid_rot_z(cursor->ellipsoid, angle);
		if (cursor->type == triangle)
			triangle_rot_z(cursor->triangle, angle);
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
	scene->camera->beta += beta;
	printf("alpha: %f\nbeta: %f\n\n", scene->camera->alpha, scene->camera->beta);
}
