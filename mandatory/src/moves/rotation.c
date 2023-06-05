/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/01 09:59:40 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/05/17 15:32:45 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt.h>

void	vector_rot_x(t_vector *vec, double angle)
{
	double	tmp;

	tmp = vec->x;
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = vec->y * cos(angle) + tmp * sin(angle);
}

// void	vector_rot_x(t_vector *vec, double angle)
// {
// 	double	tmp;

// 	tmp = vec->x;
// 	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
// 	vec->y = vec->y * cos(angle) + tmp * sin(angle);
// }

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

void	vector_rot_y(t_vector *vec, double angle)
{
	double	tmp;

	tmp = vec->y;
	vec->y = vec->y * cos(angle) - vec->z * sin(angle);
	vec->z = vec->z * cos(angle) + tmp * sin(angle);
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

void	world_rotate(t_scene *scene, double alpha, double beta)
{
	if (scene->camera->beta + beta > 90 || scene->camera->beta + beta < -90)
		return ;
	rotation_y(scene, scene->camera->beta * (M_PI / 180));
	rotation_x(scene, -scene->camera->alpha * (M_PI / 180));
	scene->camera->alpha = fmod(scene->camera->alpha + alpha, 360);
	scene->camera->beta += beta;
	rotation_x(scene, scene->camera->alpha * (M_PI / 180));
	rotation_y(scene, -scene->camera->beta * (M_PI / 180));
	printf("alpha: %f\nbeta: %f\n\n", scene->camera->alpha, scene->camera->beta);
}
