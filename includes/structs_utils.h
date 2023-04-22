/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/22 13:09:59 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "minirt.h"

typedef enum e_type {sphere, plane, cylinder}	t_type;

typedef struct s_coords		t_coords;
typedef struct s_vector		t_vector;
typedef struct s_obj_list	t_obj_list;

struct s_coords {//DEPRECATED
	double	x;
	double	y;
	double	z;
};

struct	s_vector {
	double	x_o;
	double	y_o;
	double	z_o;
	double	x_d;
	double	y_d;
	double	z_d;
};

struct	s_obj_list {
	t_type		type;
	void		*obj;
	t_obj_list	*next;
};

#endif
