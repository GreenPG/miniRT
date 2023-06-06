/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 08:18:41 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/06 16:21:41 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_quaternion quaternion(double a, double i, double j, double k)
{
	t_quaternion quat;

	quat.a = a;
	quat.i = i;
	quat.j = j;
	quat.k = k;
	return (quat);
}

t_quaternion quaternion_conjugate(t_quaternion quat)
{
	quat.a = -quat.a;
	quat.i = -quat.i;
	quat.j = -quat.j;
	quat.k = -quat.k;
	return (quat);
}

t_quaternion quaternion_multiplicate(t_quaternion q, t_quaternion l)
{
	t_quaternion quat;

	quat.a = q.a * l.a - q.i * l.i - q.j * l.j - q.k * l.k;
	quat.i = q.a * l.i + q.i * l.a - q.j * l.k + q.k * l.j;
	quat.j = q.a * l.j + q.i * l.k + q.j * l.a - q.k * l.i;
	quat.k = q.a * l.k - q.i * l.j + q.j * l.i + q.k * l.a;

	return (quat);
}

/*	ANGLE IN RADIAN	*/

void	rotate_around_axis(t_vector *vec, t_vector axis, double angle)
{
	t_quaternion	q;
	t_quaternion	q_c;
	t_quaternion	p;
	double			rot;

	rot = sin(angle / 2.);
	q = quaternion(cos(angle / 2.), axis.x * rot, axis.y * rot, axis.z * rot);
	rot = sin(-angle / 2.);
	q_c = quaternion(cos(-angle / 2.), axis.x * rot, axis.y * rot, axis.z * rot);
	p = quaternion(0, vec->x, vec->y, vec->z);
	p = quaternion_multiplicate(q, p);
	p = quaternion_multiplicate(p, q_c);
	vec->x = p.i;
	vec->y = p.j;
	vec->z = p.k;
}