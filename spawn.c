/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:16:39 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 15:20:23 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void			ft_dironspawn(t_conf *conf, t_spawn spawn)
{
	conf->player.dirx = spawn.dirx;
	conf->player.diry = spawn.diry;
	conf->player.planex = spawn.px;
	conf->player.planey = spawn.py;
}

struct s_spawn	ft_initspawn(double dirx, double diry, double px, double py)
{
	t_spawn spawn;

	spawn.dirx = dirx;
	spawn.diry = diry;
	spawn.px = px;
	spawn.py = py;
	return (spawn);
}

int				ft_player_spawn(int y, int x, t_conf *conf, char c)
{
	conf->player.posx = x + 0.5;
	conf->player.posy = y + 0.5;
	if (c == 'N')
		ft_dironspawn(conf, ft_initspawn(0, -1, 0.66, 0));
	else if (c == 'S')
		ft_dironspawn(conf, ft_initspawn(0, 1, -0.66, 0));
	else if (c == 'E')
		ft_dironspawn(conf, ft_initspawn(1, 0, 0, 0.66));
	else if (c == 'W')
		ft_dironspawn(conf, ft_initspawn(-1, 0, 0, -0.66));
	return (1);
}
