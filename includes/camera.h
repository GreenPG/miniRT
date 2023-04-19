/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:25:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 14:01:47 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define CAMERA_H

# include <minirt.h>

typedef struct s_camera	t_camera;

struct s_camera	{
	t_vector	pos;
	double		fov;
};

#endif
