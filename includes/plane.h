/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:09:09 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 14:04:36 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define PLANE_H

# include <minirt.h>

typedef struct s_plane	t_plane;

struct s_plane {
	t_coords	*origin;
	t_vector	*normal_vector;
	int			colors;
};

#endif
