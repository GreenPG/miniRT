/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:07 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/21 15:04:38 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELLIPSOID_H
# define ELLIPSOID_H

# include <minirt.h>

typedef struct s_ellipsoid	t_ellipsoid;

//format : el <coord> <direction> <a,b,c> <color>

struct	s_ellipsoid {
	t_vector	*origin;
	t_vector	*direction;
	t_vector	*up;
	double		a;
	double		b;
	double		c;
	double		c_std;
	int			color;
};

#endif
