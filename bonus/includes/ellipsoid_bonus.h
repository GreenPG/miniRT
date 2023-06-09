/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:07 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/09 18:10:54 by gtouzali         ###   ########.fr       */
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
	double		a;
	double		b;
	double		c;
	int			color;
	int			pattern;
};

#endif
