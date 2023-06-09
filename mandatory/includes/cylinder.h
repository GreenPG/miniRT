/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:17:57 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/09 11:04:40 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include <minirt.h>

typedef struct s_cylinder	t_cylinder;
typedef struct s_cyl_calc	t_cyl_calc;

struct s_cylinder	{
	t_vector	*origin;
	t_vector	*direction;
	t_vector	*up;
	float		diameter;
	float		height;
	int			color;
	bool		hit_body;
	double		alpha;
	double		beta;
	double		theta;
};

struct s_cyl_calc	{
	t_normal	normal;
	t_vector	rayo;
	t_vector	cross;
	double		angle;
	t_vector	front;
	double		vector_len;
};

#endif
