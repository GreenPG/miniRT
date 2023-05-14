/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:48:47 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/13 16:44:14 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <minirt.h>

typedef struct s_sphere	t_sphere;

struct	s_sphere {
	t_vector	*origin;
	double		diameter;
	int			color;
};

#endif
