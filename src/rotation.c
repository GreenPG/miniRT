/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:59:40 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/04 10:56:38 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void    sphere_rot_x(t_sphere *sphere, double angle)
{
    sphere->pos->x = sphere->pos->x * cos ((M_PI / 180.) * angle) - sphere->pos->y * sin ((M_PI / 180.) * angle);
    sphere->pos->y = sphere->pos->y * cos ((M_PI / 180.) * angle) + sphere->pos->x * sin ((M_PI / 180.) * angle);
}

void    plane_rot_x(void *obj, double angle)
{
    t_plane *plane;

    plane = obj;
    plane->vector->x_o = plane->vector->x_o * cos ((M_PI / 180.) * angle) - plane->vector->y_o * sin ((M_PI / 180.) * angle);
    plane->vector->y_o = plane->vector->y_o * cos ((M_PI / 180.) * angle) + plane->vector->x_o * sin ((M_PI / 180.) * angle);
    plane->vector->x_d = plane->vector->x_d * cos ((M_PI / 180.) * angle) - plane->vector->y_d * sin ((M_PI / 180.) * angle);
    plane->vector->y_d = plane->vector->y_d * cos ((M_PI / 180.) * angle) + plane->vector->x_d * sin ((M_PI / 180.) * angle);

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
        cursor = cursor->next;
    }
}

void    sphere_rot_y(void *obj, double angle)
{
    t_sphere *sphere;

    sphere = obj;
    sphere->pos->y = sphere->pos->y * cos ((M_PI / 180) * angle) - sphere->pos->z * sin ((M_PI / 180) * angle);
    sphere->pos->z = sphere->pos->z * cos ((M_PI / 180) * angle) + sphere->pos->y * sin ((M_PI / 180) * angle);
}

void    plane_rot_y(void *obj, double angle)
{
    t_plane *plane;

    plane = obj;
    plane->vector->y_o = plane->vector->y_o * cos ((M_PI / 180) * angle) - plane->vector->z_o * sin ((M_PI / 180) * angle);
    plane->vector->z_o = plane->vector->z_o * cos ((M_PI / 180) * angle) + plane->vector->y_o * sin ((M_PI / 180) * angle);
    plane->vector->y_d = plane->vector->y_d * cos ((M_PI / 180) * angle) - plane->vector->z_d * sin ((M_PI / 180) * angle);
    plane->vector->z_d = plane->vector->z_d * cos ((M_PI / 180) * angle) + plane->vector->y_d * sin ((M_PI / 180) * angle);
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
        cursor = cursor->next;
    }
}