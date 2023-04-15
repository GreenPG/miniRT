/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 15:04:11 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "minirt.h"

typedef struct s_color	t_color;
typedef struct s_vector	t_vector;
 

struct s_color {
	int	r;
	int	g;
	int	b;
};

struct	s_vector {
	float	x_o;
	float	y_o;
	float	z_o;
	float	x_d;
	float	y_d;
	float	z_d;
};

#endif
