/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:51:34 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:17:19 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lst_len;

	if (!lst)
		return (0);
	lst_len = 1;
	while (lst->next != NULL)
	{
		lst_len++;
		lst = lst->next;
	}
	return (lst_len);
}
