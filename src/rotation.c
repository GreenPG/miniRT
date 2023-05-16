/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:59:40 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/16 08:47:24 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void    vector_rot_x(t_vector *vec, double angle)
{
    double  tmp;

    tmp = vec->x;
    vec->x = vec->x * cos(angle) - vec->y * sin(angle);
    vec->y = vec->y * cos(angle) + tmp * sin(angle);
}

void    sphere_rot_x(t_sphere *sphere, double angle)
{
    vector_rot_x(sphere->origin, angle);
}

void    light_rot_x(t_light *light, double angle)
{
    vector_rot_x(light->origin, angle);
}

void    plane_rot_x(t_plane *plane, double angle)
{
    vector_rot_x(plane->origin, angle);
    vector_rot_x(plane->direction, angle);
}

void	cylinder_rot_x(t_cylinder *cylinder, double angle)
{
    vector_rot_x(cylinder->origin, angle);
    vector_rot_x(cylinder->direction, angle);
    cylinder->alpha = fmod(cylinder->alpha - angle, 360);
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

void    vector_rot_y(t_vector *vec, double angle)
{
    double  tmp;

    tmp = vec->y;
    vec->y = vec->y * cos(angle) - vec->z * sin(angle);
    vec->z = vec->z * cos(angle) + tmp * sin(angle);
}

void    sphere_rot_y(t_sphere *sphere, double angle)
{
    vector_rot_y(sphere->origin, angle);
}

void    light_rot_y(t_light *light, double angle)
{
    vector_rot_y(light->origin, angle);
}

void    plane_rot_y(t_plane *plane, double angle)
{
    vector_rot_y(plane->origin, angle);
    vector_rot_y(plane->direction, angle);
}

static void	cylinder_rot_y(t_cylinder *cylinder, double angle)
{
    vector_rot_y(cylinder->origin, angle);
    vector_rot_y(cylinder->direction, angle);
    cylinder->beta -= angle;
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