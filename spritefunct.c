/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritefunct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:08:19 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 17:31:30 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"
#include <stdio.h>

void	ft_sortsprites(t_mega *mega)
{
	int		y;
	int		z;
	t_pos	temp;

	y = -1;
	while (++y < mega->nbsprites)
		mega->sprites[y].dist = ((mega->conf.player.posx - mega->sprites[y].x)
			* (mega->conf.player.posx - mega->sprites[y].x)
			+ (mega->conf.player.posy - mega->sprites[y].y)
			* (mega->conf.player.posy - mega->sprites[y].y));
	y = -1;
	while (++y < mega->nbsprites - 1)
	{
		z = -1;
		while (++z + 1 < mega->nbsprites - y)
		{
			if (mega->sprites[z].dist
				< mega->sprites[z + 1].dist && mega->sprites[z + 1].x != -1)
			{
				temp = mega->sprites[z];
				mega->sprites[z] = mega->sprites[z + 1];
				mega->sprites[z + 1] = temp;
			}
		}
	}
}

int		ft_spheight(t_mega *mega, int spriteheight)
{
	mega->spconf.drawstarty = -spriteheight / 2 + mega->conf.res.height / 2;
	if (mega->spconf.drawstarty < 0)
		mega->spconf.drawstarty = 0;
	mega->spconf.drawendy = spriteheight / 2 + mega->conf.res.height / 2;
	if (mega->spconf.drawendy >= mega->conf.res.height)
		mega->spconf.drawendy = mega->conf.res.height - 1;
	return (spriteheight);
}

int		ft_spwidth(t_mega *mega, int spritewidth, int spritescreenx)
{
	mega->spconf.drawstartx = -spritewidth / 2 + spritescreenx;
	if (mega->spconf.drawstartx < 0)
		mega->spconf.drawstartx = 0;
	mega->spconf.drawendx = spritewidth / 2 + spritescreenx;
	if (mega->spconf.drawendx >= mega->conf.res.width)
		mega->spconf.drawendx = mega->conf.res.width - 1;
	return (spritewidth);
}

void	ft_transforms(t_mega *mega, int y)
{
	double spritex;
	double spritey;
	double invdet;

	spritey = mega->sprites[y].y - mega->conf.player.posy;
	spritex = mega->sprites[y].x - mega->conf.player.posx;
	invdet = 1.0 / (mega->conf.player.planex * mega->conf.player.diry -
		mega->conf.player.planey * mega->conf.player.dirx);
	mega->transformx = invdet * (mega->conf.player.diry *
		spritex - mega->conf.player.dirx * spritey);
	mega->transformy = invdet * (-mega->conf.player.planey *
		spritex + mega->conf.player.planex * spritey);
}

int		ft_mktexx(t_mega *mega, int *stripe, double transfx, double transfy)
{
	int texx;
	int spritescreenx;
	int spritewidth;

	spritescreenx = (int)((mega->conf.res.width / 2)
		* (1 + transfx / transfy));
	spritewidth = ft_spwidth(mega,
		abs((int)(mega->conf.res.height * 0.6 / (transfy))), spritescreenx);
	if (spritewidth < 1)
		spritewidth = 1;
	if (*stripe == 0)
		*stripe = mega->spconf.drawstartx;
	texx = (int)(256 * (*stripe - (-spritewidth / 2 + spritescreenx)) *
		mega->tex.sp.width / spritewidth) / 256;
	return (texx);
}
