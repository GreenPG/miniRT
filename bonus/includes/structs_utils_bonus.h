/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/08 09:12:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "minirt_bonus.h"

typedef enum e_type {sphere, plane, cylinder, ellipsoid}	t_type;
typedef enum e_pattern {plain, checkerboard}	t_pattern;

typedef struct s_vector		t_vector;
typedef struct s_obj_list	t_obj_list;
typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_ellipsoid	t_ellipsoid;
typedef struct s_normal		t_normal;

struct	s_vector {
	double	x;
	double	y;
	double	z;
};

struct	s_obj_list {
	t_type		type;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_ellipsoid *ellipsoid;
	t_obj_list	*next;
	int			pattern;
	int			hitted;
	float		sp_e;
	float		ks;
	bool		front_face;
};

struct	s_normal {
	t_vector	origin;
	t_vector	dir;
};

#endif
