/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:23:39 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/11 10:00:27 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void    sphere_translate(t_sphere *sphere, double x, double y, double z)
{
    sphere->pos->x += x;
    sphere->pos->y += y;
    sphere->pos->z += z;
}

void    plane_translate(t_plane *plane, double x, double y, double z)
{
    plane->vector->x_o += x;
    plane->vector->y_o += y;
    plane->vector->z_o += z;
}

void    cylinder_translate(t_cylinder *cylinder, double x, double y, double z)
{
    cylinder->vector->x_o += x;
    cylinder->vector->y_o += y;
    cylinder->vector->z_o += z;
}

void    light_translate(t_light *light, double x, double y, double z)
{
    light->pos->x += x;
    light->pos->y += y;
    light->pos->z += z;
}

void    world_translate(t_scene *scene, double x, double y, double z)
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