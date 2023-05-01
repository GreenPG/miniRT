/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:59:40 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/01 11:53:59 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void    sphere_rot_x(void *obj, int direction)
{
    t_sphere *sphere;

    sphere = obj;
    sphere->pos->x = sphere->pos->x * cos (10. * (M_PI / 180.) * direction) - sphere->pos->y * sin (10. * (M_PI / 180.) * direction);
    sphere->pos->y = sphere->pos->y * cos (10. * (M_PI / 180.) * direction) + sphere->pos->x * sin (10. * (M_PI / 180.) * direction);

}

void rotation_x(t_scene *scene, int direction)
{
    t_obj_list	*cursor;

    cursor = scene->obj_list;
    while (cursor)
    {
        if (cursor->type == sphere)
			sphere_rot_x(cursor->obj, direction);
        cursor = cursor->next;
    }
}

void    sphere_rot_y(void *obj, int direction)
{
    t_sphere *sphere;

    sphere = obj;
    sphere->pos->y = sphere->pos->y * cos (10 * (M_PI / 180) * direction) - sphere->pos->z * sin (10 * (M_PI / 180) * direction);
    sphere->pos->z = sphere->pos->z * cos (10 * (M_PI / 180) * direction) + sphere->pos->y * sin (10 * (M_PI / 180) * direction);
}

void rotation_y(t_scene *scene, int direction)
{
    t_obj_list	*cursor;

    cursor = scene->obj_list;
    while (cursor)
    {
        if (cursor->type == sphere)
			sphere_rot_y(cursor->obj, direction);
        cursor = cursor->next;
    }
}