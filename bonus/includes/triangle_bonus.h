/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:31 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/15 14:48:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include <minirt_bonus.h>

typedef struct s_triangle	t_triangle;

struct	s_triangle {
	t_vector	*a;
	t_vector	*b;
	t_vector	*c;
	t_vector	*normal;
	t_vector	*up;
	int			color;
};

#endif
