/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:09:09 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/17 17:17:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include <minirt.h>

typedef struct s_plane	t_plane;

struct s_planne {
	t_coords	*origin;
	t_vector	*normal_vector;
	int			colors;
};

#endif
