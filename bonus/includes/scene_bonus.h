/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:26:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/14 08:11:04 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include <minirt_bonus.h>

typedef struct s_scene	t_scene;

struct s_scene {
	t_ambiant_l		*ambiant_l;
	t_camera		*camera;
	t_light_list	*light_list;
	t_obj_list		*obj_list;
	t_obj_list		*obj_selected;
	mlx_image_t		*img;
	t_vector		*up;
	t_vector		*direction;
};

#endif
