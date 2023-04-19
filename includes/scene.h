/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:26:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 14:17:46 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <minirt.h>

typedef struct s_scene	t_scene;

struct s_scene {
	t_ambiant_l	*ambiant_l;
	t_camera	*camera;
	//t_light	*light;
	
	t_obj_list	*obj_list;
};

#endif