/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:17 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/13 16:45:39 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include <minirt.h>

typedef struct s_light	t_light;

struct	s_light {
	t_vector	*origin;
	float		brightness;
	int			colors;
};

#endif
