/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayfunct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:34:31 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 17:36:51 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void	ft_chooseside(t_mega *mega, t_ray *ray)
{
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (mega->conf.player.posy
		- (int)mega->conf.player.posy) * fabs(1 / ray->raydiry);
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = ((int)mega->conf.player.posy
		+ 1.0 - mega->conf.player.posy) * fabs(1 / ray->raydiry);
	}
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (mega->conf.player.posx
		- (int)mega->conf.player.posx) * fabs(1 / ray->raydirx);
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = ((int)mega->conf.player.posx
		+ 1.0 - mega->conf.player.posx) * fabs(1 / ray->raydirx);
	}
}

void	ft_dda(t_mega *mega, t_ray *ray)
{
	while (1)
	{
		if (ray->sidedisty < ray->sidedistx)
		{
			ray->sidedisty += fabs(1 / ray->raydiry);
			ray->mapy += ray->stepy;
			ray->side = 0;
		}
		else
		{
			ray->sidedistx += fabs(1 / ray->raydirx);
			ray->mapx += ray->stepx;
			ray->side = 1;
		}
		if (mega->map[ray->mapy][ray->mapx] == '1')
			break ;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapy - mega->conf.player.posy
		+ (1 - ray->stepy) / 2) / ray->raydiry;
	else
		ray->perpwalldist = (ray->mapx - mega->conf.player.posx
		+ (1 - ray->stepx) / 2) / ray->raydirx;
}

double	ft_wallx(t_mega *mega, t_ray *ray, t_draw *draw)
{
	double wallx;

	if (ray->side == 0)
		wallx = mega->conf.player.posx + ray->perpwalldist * ray->raydirx;
	else
		wallx = mega->conf.player.posy + ray->perpwalldist * ray->raydiry;
	if (ray->raydiry > 0 && ray->side == 0)
		draw->tex = mega->tex.so;
	else if (ray->raydiry < 0 && ray->side == 0)
		draw->tex = mega->tex.no;
	else if (ray->raydirx < 0 && ray->side == 1)
		draw->tex = mega->tex.we;
	else if (ray->raydirx > 0 && ray->side == 1)
		draw->tex = mega->tex.ea;
	return (fmod(wallx, 1));
}

void	ft_rayinit(t_mega *mega, t_ray *ray, int x)
{
	ray->cameray = (2 * x / (double)mega->conf.res.width) - 1;
	ray->raydiry = mega->conf.player.diry
		+ mega->conf.player.planey * ray->cameray;
	ray->raydirx = mega->conf.player.dirx
		+ mega->conf.player.planex * ray->cameray;
	ray->mapy = (int)mega->conf.player.posy;
	ray->mapx = (int)mega->conf.player.posx;
}

int		ft_loadsprites2(t_mega *mega)
{
	t_data *ptr;

	ptr = &(mega->tex.we);
	if ((ptr->img = mlx_xpm_file_to_image(mega->mlx,
	mega->conf.we, &ptr->width, &ptr->height)) == NULL)
		return (-1);
	ptr->addr = mlx_get_data_addr(ptr->img,
	&ptr->bpp, &ptr->linelen, &ptr->endian);
	ptr = &(mega->tex.sp);
	if ((ptr->img = mlx_xpm_file_to_image(mega->mlx,
	mega->conf.s, &ptr->width, &ptr->height)) == NULL)
		return (-1);
	ptr->addr = mlx_get_data_addr(ptr->img,
	&ptr->bpp, &ptr->linelen, &ptr->endian);
	return (0);
}
