/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:26:20 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 16:26:34 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void	ft_no(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 2;
	while (str[i] == 32)
		i++;
	if (!(conf->no = ft_strdup(&str[i])))
		*ret = -1;
}

void	ft_so(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 2;
	while (str[i] == 32)
		i++;
	if (!(conf->so = ft_strdup(&str[i])))
		*ret = -1;
}

void	ft_we(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 2;
	while (str[i] == 32)
		i++;
	if (!(conf->we = ft_strdup(&str[i])))
		*ret = -1;
}

void	ft_ea(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 2;
	while (str[i] == 32)
		i++;
	if (!(conf->ea = ft_strdup(&str[i])))
		*ret = -1;
}

void	ft_s(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 1;
	while (str[i] == 32)
		i++;
	if (!(conf->s = ft_strdup(&str[i])))
		*ret = -1;
}
