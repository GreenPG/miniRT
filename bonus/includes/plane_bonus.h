/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:09:09 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/15 09:58:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_BONUS_H
# define PLANE_BONUS_H

# include <minirt_bonus.h>

typedef struct s_plane	t_plane;

struct s_plane {
	t_vector	*origin;
	t_vector	*direction;
	t_vector	*up;
	int			colors;
};

#endif
