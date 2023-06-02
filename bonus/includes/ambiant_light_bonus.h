/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_light.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:33:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/17 17:16:24 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIANT_LIGHT_H
# define AMBIANT_LIGHT_H

# include <minirt_bonus.h>

typedef struct s_ambiant_l	t_ambiant_l;

struct s_ambiant_l {
	float	light_ratio;
	int		colors;
};

#endif
