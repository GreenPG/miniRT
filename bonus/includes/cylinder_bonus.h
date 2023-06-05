/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:17:57 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/05 09:22:26 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_BONUS_H
# define CYLINDER_BONUS_H

# include <minirt_bonus.h>

typedef struct s_cylinder	t_cylinder;

struct s_cylinder	{
	t_vector	*origin;
	t_vector	*direction;
	float		diameter;
	float		height;
	int			color;
	bool		hit_body;
	double		alpha;
	double		beta;
	int			pattern;
};

#endif
