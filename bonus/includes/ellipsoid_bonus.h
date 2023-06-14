/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:07 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/14 17:01:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELLIPSOID_BONUS_H
# define ELLIPSOID_BONUS_H

# include <minirt_bonus.h>

typedef struct s_ellipsoid	t_ellipsoid;

//format : el <coord> <direction> <a,b,c> <color>

struct	s_ellipsoid {
	t_vector	*origin;
	t_vector	*direction;
	t_vector	*up;
	double		a;
	double		b;
	double		c;
	int			color;
	int			pattern;
	int			sp_e;
	int			ks;
	mlx_texture_t	*tex;
};

#endif
