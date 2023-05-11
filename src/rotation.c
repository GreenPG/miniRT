/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:59:40 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/11 09:41:33 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void    sphere_rot_x(t_sphere *sphere, double angle)
{
    double  tmp;

    tmp = sphere->pos->x;
    sphere->pos->x = sphere->pos->x * cos(angle) - sphere->pos->y * sin(angle);
    sphere->pos->y = sphere->pos->y * cos(angle) + tmp * sin(angle);
}

void    plane_rot_x(t_plane *plane, double angle)
{
    double  tmp;

    tmp = plane->vector->x_o;
    plane->vector->x_o = plane->vector->x_o * cos (angle) - plane->vector->y_o * sin (angle);
    plane->vector->y_o = plane->vector->y_o * cos (angle) + tmp * sin (angle);
    tmp = plane->vector->x_d;
    plane->vector->x_d = plane->vector->x_d * cos (angle) - plane->vector->y_d * sin (angle);
    plane->vector->y_d = plane->vector->y_d * cos (angle) + tmp * sin (angle);

}

void	cylinder_rot_x(t_cylinder *cylinder, double angle)
{
    double  tmp;

    tmp = cylinder->vector->x_o;
    cylinder->vector->x_o = cylinder->vector->x_o * cos (angle) - cylinder->vector->y_o * sin (angle);
    cylinder->vector->y_o = cylinder->vector->y_o * cos (angle) + tmp * sin (angle);
    tmp = cylinder->vector->x_d;
    cylinder->vector->x_d = cylinder->vector->x_d * cos (angle) - cylinder->vector->y_d * sin(angle);
    cylinder->vector->y_d = cylinder->vector->y_d * cos (angle) + tmp * sin (angle);
}

void rotation_x(t_scene *scene, double angle)
{
    t_obj_list	*cursor;

    cursor = scene->obj_list;
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

void    sphere_rot_y(t_sphere *sphere, double angle)
{
    double  tmp;

    tmp = sphere->pos->y;
    sphere->pos->y = sphere->pos->y * cos (angle) - sphere->pos->z * sin (angle);
    sphere->pos->z = sphere->pos->z * cos (angle) + tmp * sin (angle);
}

void    plane_rot_y(t_plane *plane, double angle)
{
    double  tmp;

    tmp =  plane->vector->y_o;
    plane->vector->y_o = plane->vector->y_o * cos (angle) - plane->vector->z_o * sin (angle);
    plane->vector->z_o = plane->vector->z_o * cos (angle) + tmp * sin (angle);
    tmp =  plane->vector->y_d;
    plane->vector->y_d = plane->vector->y_d * cos (angle) - plane->vector->z_d * sin (angle);
    plane->vector->z_d = plane->vector->z_d * cos (angle) + tmp * sin (angle);
}

static void	cylinder_rot_y(t_cylinder *cylinder, double angle)
{
    double  tmp;

    tmp =  cylinder->vector->y_o;
    cylinder->vector->y_o = cylinder->vector->y_o * cos (angle) - cylinder->vector->z_o * sin (angle);
    cylinder->vector->z_o = cylinder->vector->z_o * cos (angle) + tmp * sin (angle);
    tmp =  cylinder->vector->y_d;
    cylinder->vector->y_d = cylinder->vector->y_d * cos (angle) - cylinder->vector->z_d * sin (angle);
    cylinder->vector->z_d = cylinder->vector->z_d * cos (angle) + tmp * sin (angle);
}

void rotation_y(t_scene *scene, double angle)
{
    t_obj_list	*cursor;

    cursor = scene->obj_list;
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

void    world_rotate(t_scene *scene, double alpha, double beta)
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