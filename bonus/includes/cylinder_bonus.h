/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:17:57 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/11 12:44:47 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_BONUS_H
# define CYLINDER_BONUS_H

# include <minirt_bonus.h>

typedef struct s_cylinder	t_cylinder;
typedef struct s_cyl_calc	t_cyl_calc;

struct s_cylinder	{
	t_vector	*origin;
	t_vector	*direction;
	float		diameter;
	float		height;
	int			color;
	bool		hit_body;
	int			pattern;
	mlx_texture_t	*tex;
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
