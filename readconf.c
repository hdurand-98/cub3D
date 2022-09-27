/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readconf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:57:26 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 16:32:21 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void	(*g_tabfunc[8]) (char*, t_conf*, int*) = {
	ft_res,
	ft_no,
	ft_so,
	ft_we,
	ft_ea,
	ft_s,
	ft_floor,
	ft_ceiling
};

int		ft_elements(char *str, int *ret)
{
	if (str[0] == 'R')
		return (0);
	else if (str[0] == 'N' && str[1] == 'O')
		return (1);
	else if (str[0] == 'S' && str[1] == 'O')
		return (2);
	else if (str[0] == 'W' && str[1] == 'E')
		return (3);
	else if (str[0] == 'E' && str[1] == 'A')
		return (4);
	else if (str[0] == 'S')
		return (5);
	else if (str[0] == 'F')
		return (6);
	else if (str[0] == 'C')
		return (7);
	else if (str[0] == 0)
		return (8);
	else
	{
		*ret = -1;
		return (-1);
	}
}

void	ft_res(char *str, t_conf *conf, int *ret)
{
	int i;

	i = 1;
	conf->res.width = ft_atoi(str, &i, conf->res.width);
	if (conf->res.width <= 0)
		*ret = -1;
	conf->res.height = ft_atoi(str, &i, conf->res.height);
	if (conf->res.height <= 0)
		*ret = -1;
	if (str[i])
		*ret = -1;
}

int		ft_putconf(int *checknbr, int *check, int fd, t_conf *conf)
{
	char	*str;
	int		i;
	int		ret;

	if ((str = ft_gnl(0, &ret, fd)) == NULL)
		return (-1);
	i = ft_elements(str, &ret);
	if (ret != 1)
	{
		free(str);
		return (ret);
	}
	if (i >= 0 && i < 8)
	{
		g_tabfunc[i](str, conf, &ret);
		check[i] = 1;
		*checknbr = *checknbr + 1;
	}
	else if (str[0] != 0)
	{
		free(str);
		return (-1);
	}
	free(str);
	return (ret);
}

void	ft_initptr(t_mega *mega)
{
	mega->sprites = NULL;
	mega->conf.no = NULL;
	mega->conf.so = NULL;
	mega->conf.ea = NULL;
	mega->conf.we = NULL;
	mega->conf.s = NULL;
}

void	ft_readconf(int *ret, int fd, t_mega *mega)
{
	int		check[8];
	int		checknbr;
	int		i;

	i = 0;
	checknbr = 0;
	ft_initptr(mega);
	while (i < 8)
		check[i++] = 0;
	*ret = 1;
	while (checknbr < 8 && *ret == 1)
		*ret = ft_putconf(&checknbr, check, fd, &mega->conf);
	if (checknbr != 8)
		*ret = -1;
	i = 0;
	while (i < 8 && check[i] == 1)
		i++;
	if (i != 8)
		*ret = -1;
}
