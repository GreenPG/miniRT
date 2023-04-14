/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:25:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 14:58:57 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <minirt.h>

typedef struct s_camera	t_camera;

struct s_camera	{
	t_coords	*pos;
	t_vector	*orientation_vector;
	int			fov;
};

#endif
