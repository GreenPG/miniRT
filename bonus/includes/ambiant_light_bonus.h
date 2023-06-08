/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_light_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:33:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/08 13:31:07 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIANT_LIGHT_BONUS_H
# define AMBIANT_LIGHT_BONUS_H

# include <minirt_bonus.h>

typedef struct s_ambiant_l	t_ambiant_l;

struct s_ambiant_l {
	float	light_ratio;
	int		colors;
};

#endif
