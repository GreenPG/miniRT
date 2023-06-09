/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:48:47 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/15 10:00:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_BONUS_H
# define SPHERE_BONUS_H

# include <minirt_bonus.h>

typedef struct s_sphere	t_sphere;

struct	s_sphere {
	t_vector		*origin;
	t_vector		*up;
	t_vector		*direction;
	double			diameter;
	int				color;
};

#endif
