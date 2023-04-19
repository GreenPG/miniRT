/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:15:27 by gpasquet          #+#    #+#             */
/*   Updated: 2022/11/03 17:14:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power > 0)
		nb = nb * ft_power(nb, power - 1);
	return (nb);
}

static void	ft_itoa_convert(int n, char *ret, int ret_len)
{
	int	i;

	if (n < 0)
	{
		ret[0] = '-';
		i = 1;
		n = -n;
		ret_len--;
	}
	else
		i = 0;
	while (ret_len > 0)
	{
		ret[i] = (n / ft_power(10, (ret_len - 1))) + 48;
		n = n % ft_power(10, ret_len - 1);
		ret_len--;
		i++;
	}	
	ret[i] = '\0';
}

static int	ft_ret_len_measuring(int n)
{
	int		ret_len;
	int		i;

	ret_len = 1;
	if (n < 0)
	{	
		i = -n;
		ret_len++;
	}
	else
		i = n;
	while (i > 9)
	{
		i = i / 10;
		ret_len++;
	}
	return (ret_len);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		ret_len;

	if (n == -2147483648)
	{	
		ret = ft_strdup("-2147483648");
		return (ret);
	}
	ret_len = ft_ret_len_measuring(n);
	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
	if (!ret)
		return (0);
	ft_itoa_convert(n, ret, ret_len);
	return (ret);
}
