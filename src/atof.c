/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:41:38 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/15 11:10:32 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

//avec des chiffres tres grand : >MAX_INT ca fait nimp;
//faudra normer
//et calcule meme si ca overflow underflow essaye de atof un truc trop precis si
//y'as des lettres rien caca ca defaut sur 0.
//sinon avec des test classiques (ce qu on aura en realite)
//ca fonctionne niquel.

double	gg_atof(char *str)
{
	double	result;
	double 	sign;
	int		i;
	double	scale;

	result = 0;
	sign = 1;
	i = 0;
	scale = 10;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '-')
		sign *= -1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break;
		result = (result * 10) + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break;
		result = result + (str[i] - '0') / scale;
		scale *= 10;
		i++;
	}
	return (result * sign);
}
int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("%f\n%f\n", gg_atof(argv[1]), atof(argv[1]));
	return (0);
}