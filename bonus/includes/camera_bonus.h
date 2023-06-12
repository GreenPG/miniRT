/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:25:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/12 09:00:55 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_BONUS_H
# define CAMERA_BONUS_H

# include <minirt_bonus.h>

typedef struct s_camera	t_camera;
typedef struct s_rays	t_rays;

struct s_rays {
	t_vector	**rays;
};

struct s_camera	{
	t_vector	*origin;
	t_vector	*direction;
	double		fov;
	t_rays		*rays;
	double		alpha;
	double		beta;
};

#endif
