/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:59:40 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/14 14:01:39 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void    sphere_rot_x(t_sphere *sphere, double angle)
{
    double  tmp;

    tmp = sphere->origin->x;
    sphere->origin->x = sphere->origin->x * cos(angle) - sphere->origin->y * sin(angle);
    sphere->origin->y = sphere->origin->y * cos(angle) + tmp * sin(angle);
}

void    light_rot_x(t_light *light, double angle)
{
    double  tmp;

    tmp = light->origin->x;
    light->origin->x = light->origin->x * cos(angle) - light->origin->y * sin(angle);
    light->origin->y = light->origin->y * cos(angle) + tmp * sin(angle);
}

void    plane_rot_x(t_plane *plane, double angle)
{
    double  tmp;

    tmp = plane->origin->x;
    plane->origin->x = plane->origin->x * cos (angle) - plane->origin->y * sin (angle);
    plane->origin->y = plane->origin->y * cos (angle) + tmp * sin (angle);
    tmp = plane->direction->x;
    plane->direction->x = plane->direction->x * cos (angle) - plane->direction->y * sin (angle);
    plane->direction->y = plane->direction->y * cos (angle) + tmp * sin (angle);

}

void	cylinder_rot_x(t_cylinder *cylinder, double angle)
{
    double  tmp;

    tmp = cylinder->origin->x;
    cylinder->origin->x = cylinder->origin->x * cos (angle) - cylinder->origin->x * sin (angle);
    cylinder->origin->x = cylinder->origin->x * cos (angle) + tmp * sin (angle);
    tmp = cylinder->direction->x;
    cylinder->direction->x = cylinder->direction->x * cos (angle) - cylinder->direction->x * sin(angle);
    cylinder->direction->x = cylinder->direction->x * cos (angle) + tmp * sin (angle);
}

void rotation_x(t_scene *scene, double angle)
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

void    sphere_rot_y(t_sphere *sphere, double angle)
{
    double  tmp;

    tmp = sphere->origin->y;
    sphere->origin->y = sphere->origin->y * cos (angle) - sphere->origin->z * sin (angle);
    sphere->origin->z = sphere->origin->z * cos (angle) + tmp * sin (angle);
}

void    light_rot_y(t_light *light, double angle)
{
    double  tmp;

    tmp = light->origin->y;
    light->origin->y = light->origin->y * cos (angle) - light->origin->z * sin (angle);
    light->origin->z = light->origin->z * cos (angle) + tmp * sin (angle);
}

void    plane_rot_y(t_plane *plane, double angle)
{
    double  tmp;

    tmp =  plane->origin->y;
    plane->origin->y = plane->origin->y * cos (angle) - plane->origin->z * sin (angle);
    plane->origin->z = plane->origin->z * cos (angle) + tmp * sin (angle);
    tmp =  plane->direction->y;
    plane->direction->y = plane->direction->y * cos (angle) - plane->direction->y * sin (angle);
    plane->direction->z = plane->direction->z * cos (angle) + tmp * sin (angle);
}

static void	cylinder_rot_y(t_cylinder *cylinder, double angle)
{
    double  tmp;

    tmp =  cylinder->origin->y;
    cylinder->origin->y = cylinder->origin->y * cos (angle) - cylinder->origin->z * sin (angle);
    cylinder->origin->z = cylinder->origin->z * cos (angle) + tmp * sin (angle);
    tmp =  cylinder->direction->y;
    cylinder->direction->y = cylinder->direction->y * cos (angle) - cylinder->direction->z * sin (angle);
    cylinder->direction->z = cylinder->direction->z * cos (angle) + tmp * sin (angle);
}

void rotation_y(t_scene *scene, double angle)
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