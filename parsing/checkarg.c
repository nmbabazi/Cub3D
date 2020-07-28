/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:59:44 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 15:51:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int		ft_checkcub(char *str)
{
	int len;

	len = ft_strlen(str) - 1;
	if (str[len] != 'b')
		return (0);
	len--;
	if (str[len] != 'u')
		return (0);
	len--;
	if (str[len] != 'c')
		return (0);
	len--;
	if (str[len] != '.')
		return (0);
	return (1);
}

int		ft_checksave(char *str)
{
	int i;
	int len;

	len = ft_strlen(str);
	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i] != 's')
		return (0);
	i++;
	if (str[i] != 'a')
		return (0);
	i++;
	if (str[i] != 'v')
		return (0);
	i++;
	if (str[i] != 'e')
		return (0);
	return (1);
}

int		ft_checkarg(int ac, char **av)
{
	if (ac > 3 || ac < 2)
		return (0);
	if (ac == 3)
	{
		if (ft_checksave(av[2]) == 0 || ft_checkcub(av[1]) == 0)
		{
			ft_putstr_fd("ERROR\n WRONG ARG\n", 1);
			return (0);
		}
		return (1);
	}
	if (ac == 2)
	{
		if (ft_checkcub(av[1]) == 0)
		{
			ft_putstr_fd("ERROR\n WRONG ARG\n", 1);
			return (0);
		}
		return (1);
	}
	ft_putstr_fd("ERROR\n WRONG ARG\n", 1);
	return (0);
}
