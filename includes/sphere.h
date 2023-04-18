/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:48:47 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/18 16:03:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <minirt.h>

typedef struct s_sphere	t_sphere;

struct	s_sphere {
	t_coords	*pos;
	double		diameter;
	int			color;
};

#endif
