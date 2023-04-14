/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 07:13:36 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_UTILS_H
# define STRUCT_UTILS_H

#include "minirt.h"

typedef struct	s_coords t_coords;
typedef struct	s_color t_color;

struct s_coords {
	int	x;
	int	y;
	int	z;
	//should we hade rotations too or seperate everything?
};

struct s_color {
	int	r;
	int	g;
	int	b;
};

#endif