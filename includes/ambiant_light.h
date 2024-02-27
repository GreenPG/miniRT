/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_light.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:33:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/12 09:01:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIANT_LIGHT_H
# define AMBIANT_LIGHT_H

# include <minirt.h>

typedef struct s_ambiant_l	t_ambiant_l;

struct s_ambiant_l {
	float	light_ratio;
	int		colors;
};

#endif
