/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:09:09 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include <minirt_bonus.h>

typedef struct s_plane	t_plane;

struct s_plane {
	t_vector	*origin;
	t_vector	*direction;
	int			colors;
};

#endif
