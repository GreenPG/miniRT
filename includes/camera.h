/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:25:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/03 10:42:53 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <minirt.h>

typedef struct s_camera	t_camera;
typedef struct s_rays	t_rays;

struct s_rays {
	t_vector **rays;
};

struct s_camera	{
	t_vector	*vector;
	double		fov;
	t_rays		*rays;
	double		alpha;
	double		beta;
};

#endif
