/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floceil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:38:50 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 15:39:16 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

int		ft_isdigit(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' && str[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

void	ft_2thenext(char *str, int *i, int *ret)
{
	while (str[*i] == ' ')
		*i = *i + 1;
	if (str[*i] != ',')
		*ret = -1;
	else
		*i = *i + 1;
}

void	ft_floor(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 1;
	if (!ft_isdigit(str))
	{
		*ret = -1;
		return ;
	}
	conf->f.red = ft_atoi(str, &i, 256);
	ft_2thenext(str, &i, ret);
	if (*ret != -1)
		conf->f.green = ft_atoi(str, &i, 256);
	else
		return ;
	ft_2thenext(str, &i, ret);
	if (*ret != -1)
		conf->f.blue = ft_atoi(str, &i, 256);
	else
		return ;
	if (conf->f.red < 0 || conf->f.green < 0 || conf->f.blue < 0 || str[i]
		|| conf->f.red == 256 || conf->f.green == 256 ||
		conf->f.blue == 256)
		*ret = -1;
}

void	ft_ceiling(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 1;
	if (!ft_isdigit(str))
	{
		*ret = -1;
		return ;
	}
	conf->c.red = ft_atoi(str, &i, 256);
	ft_2thenext(str, &i, ret);
	if (*ret != -1)
		conf->c.green = ft_atoi(str, &i, 256);
	else
		return ;
	ft_2thenext(str, &i, ret);
	if (*ret != -1)
		conf->c.blue = ft_atoi(str, &i, 256);
	else
		return ;
	if (conf->c.red < 0 || conf->c.green < 0 || conf->c.blue < 0 || str[i]
		|| conf->c.red == 256 || conf->c.green == 256
		|| conf->c.blue == 256)
		*ret = -1;
}
