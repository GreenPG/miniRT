/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:48:47 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/13 16:44:14 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELLIPSOID_H
# define ELLIPSOID_H

# include <minirt_bonus.h>

typedef struct s_ellipsoid	t_ellipsoid;

//format : el <coord> <direction> <a,b,c> <color>

struct	s_ellipsoid {
	t_vector	*origin;
	t_vector	*direction;
	double		a;
	double		b;
	double		c;
	double		alpha;
	double		beta;
	int			color;
	int			pattern;
};

#endif