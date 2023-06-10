/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:48:47 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/08 09:12:08 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_BONUS_H
# define SPHERE_BONUS_H

# include <minirt_bonus.h>

typedef struct s_sphere	t_sphere;

struct	s_sphere {
	t_vector	*origin;
	double		diameter;
	int			color;
	int			pattern;
};

#endif
