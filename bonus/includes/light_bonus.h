/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:17 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:15:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_BONUS_H
# define LIGHT_BONUS_H

# include <minirt_bonus.h>

typedef struct s_light_list	t_light_list;
typedef struct s_light		t_light;

struct	s_light_list {
	t_light			*light;
	t_light_list	*next;
};

struct	s_light	{
	t_vector	*origin;
	float		brightness;
	int			colors;
};

#endif
