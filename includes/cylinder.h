/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:17:57 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/18 15:30:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include <minirt.h>

typedef struct s_cylinder	t_cylinder;

struct s_cylinder	{
	t_vector	*origin;
	t_vector	*direction;
	float		diameter;
	float		height;
	int			color;
	double		alpha;
	double		beta;
	double		theta;
};

#endif
