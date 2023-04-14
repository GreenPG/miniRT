/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 13:14:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "minirt.h"

typedef enum e_type {sphere, plane, cylinder}	t_type;

typedef struct s_coords		t_coords;
typedef struct s_color		t_color;
typedef struct s_vector		t_vector;
typedef struct s_obj_list	t_obj_list;

struct s_coords {
	float	x;
	float	y;
	float	z;
	//should we hade rotations too or seperate everything?
};

struct s_color {
	int	r;
	int	g;
	int	b;
};

struct	s_vector {
	float	x;
	float	y;
	float	z;
};

struct	s_obj_list {
	t_type		type;
	void		*obj;
	t_obj_list	*next;
};

#endif
