/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/03 10:35:53 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "minirt.h"

typedef enum e_type {sphere, plane, cylinder}	t_type;

typedef struct s_coords		t_coords;
typedef struct s_vector		t_vector;
typedef struct s_obj_list	t_obj_list;
typedef struct s_plane	t_plane;
typedef struct s_sphere	t_sphere;
typedef struct s_cylinder	t_cylinder;

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
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_obj_list	*next;
};


#endif
