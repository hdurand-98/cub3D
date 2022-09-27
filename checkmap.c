/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:19:52 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 16:07:46 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

int				ft_ischarvalid(char **map)
{
	int		i;
	int		y;
	char	*okchar;
	int		x;

	i = 0;
	okchar = " 012NSEW";
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			x = 0;
			while (map[i][y] != okchar[x] && okchar[x])
				x++;
			if (!okchar[x])
				return (0);
			else
				y++;
		}
		i++;
	}
	return (i);
}

int				ft_ismapvalid(char **map, int maplen, t_conf *conf, int *nbs)
{
	int	i;
	int	y;
	int	spawn;

	i = 0;
	spawn = 0;
	while (map[++i])
	{
		y = -1;
		while (map[i][++y])
		{
			if (map[i][y] != '1' && map[i][y] != ' ')
			{
				if (y > conf->max_x[i - 1] || y > conf->max_x[i + 1] ||
		map[i + 1][y] == ' ' || map[i - 1][y] == ' ' || map[i][y + 1] == ' '
		|| map[i][y - 1] == ' ' || !map[i][y + 1] || y == 0 || i == maplen - 1)
					return (0);
				else if (map[i][y] != '0' && map[i][y] != '2')
					spawn += ft_player_spawn(i, y, conf, map[i][y]);
				else if (map[i][y] == '2')
					*nbs = *nbs + 1;
			}
		}
	}
	return (spawn == 1 ? 1 : 0);
}

struct s_pos	*ft_findsprites(t_mega *mega, int nbs)
{
	int		x;
	int		y;
	int		i;
	t_pos	*sp_list;

	sp_list = malloc(sizeof(t_pos) * (nbs + 1));
	x = 0;
	i = 0;
	while (mega->map[x])
	{
		y = -1;
		while (mega->map[x][++y])
		{
			if (mega->map[x][y] == '2')
			{
				sp_list[i].x = y + 0.5f;
				sp_list[i].y = x + 0.5f;
				i++;
			}
		}
		x++;
	}
	sp_list[i].x = -1;
	return (sp_list);
}

int				*ft_max_x(char **map, int maplen)
{
	int	*tab;
	int y;
	int x;

	if (!(tab = malloc(sizeof(int) * maplen)))
		return (NULL);
	y = -1;
	while (++y < maplen)
	{
		x = 0;
		while (map[y][x])
			x++;
		tab[y] = x - 1;
	}
	return (tab);
}

int				ft_checkmap(t_mega *mega)
{
	int	i;
	int	y;
	int	maplen;

	i = 0;
	y = 0;
	mega->nbsprites = 0;
	maplen = ft_ischarvalid(mega->map);
	if (maplen == 0)
		return (-1);
	while (mega->map[0][y] == '1' || mega->map[0][y] == ' ')
		y++;
	if (mega->map[0][y] != 0)
		return (-1);
	if (!(mega->conf.max_x = ft_max_x(mega->map, maplen)))
		return (-1);
	if (ft_ismapvalid(mega->map, maplen, &mega->conf, &mega->nbsprites) == 0)
		return (-1);
	mega->sprites = ft_findsprites(mega, mega->nbsprites);
	return (1);
}
