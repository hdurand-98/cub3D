/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:49:49 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 16:25:48 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void	ft_sprites(double *zbuf, t_mega *mega)
{
	int y;
	int spriteheight;
	int stripe;
	int texx;

	ft_sortsprites(mega);
	y = 0;
	while (y < mega->nbsprites)
	{
		ft_transforms(mega, y);
		spriteheight = abs((int)(mega->conf.res.height / (mega->transformy)));
		spriteheight = ft_spheight(mega, spriteheight);
		stripe = 0;
		texx = ft_mktexx(mega, &stripe, mega->transformx, mega->transformy);
		while (stripe < mega->spconf.drawendx)
		{
			if (mega->transformy > 0 && stripe > 0 && stripe <
					mega->conf.res.width && mega->transformy < zbuf[stripe])
				ft_drawsprite(mega, stripe, texx, spriteheight);
			stripe++;
			texx = ft_mktexx(mega, &stripe, mega->transformx, mega->transformy);
		}
		y++;
	}
}

void	ft_raycast(t_mega *mega)
{
	int		x;
	t_ray	ray;
	t_draw	draw;
	double	zbuf[mega->conf.res.width];

	x = -1;
	while (++x < mega->conf.res.width)
	{
		ft_rayinit(mega, &ray, x);
		ft_chooseside(mega, &ray);
		ft_dda(mega, &ray);
		zbuf[x] = ray.perpwalldist;
		draw.drawdist = (int)(mega->conf.res.height / ray.perpwalldist);
		draw.drawstart = -draw.drawdist / 2 + mega->conf.res.height / 2;
		if (draw.drawstart < 0)
			draw.drawstart = 0;
		draw.drawend = draw.drawdist / 2 + mega->conf.res.height / 2;
		if (draw.drawend >= mega->conf.res.height)
			draw.drawend = mega->conf.res.height - 1;
		draw.texx = (int)(ft_wallx(mega, &ray, &draw) *
			(double)(draw.tex.width));
		ft_drawline2(mega, x, draw);
	}
	ft_sprites(zbuf, mega);
}
