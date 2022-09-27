/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subwindow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:44:18 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 17:51:07 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

int		ft_loadsprites(t_mega *mega)
{
	t_data *ptr;

	ptr = &(mega->tex.no);
	if ((ptr->img = mlx_xpm_file_to_image(mega->mlx,
		mega->conf.no, &ptr->width, &ptr->height)) == NULL)
		return (-1);
	ptr->addr = mlx_get_data_addr(ptr->img,
	&ptr->bpp, &ptr->linelen, &ptr->endian);
	ptr = &(mega->tex.so);
	if ((ptr->img = mlx_xpm_file_to_image(mega->mlx,
		mega->conf.so, &ptr->width, &ptr->height)) == NULL)
		return (-1);
	ptr->addr = mlx_get_data_addr(ptr->img,
	&ptr->bpp, &ptr->linelen, &ptr->endian);
	ptr = &(mega->tex.ea);
	if ((ptr->img = mlx_xpm_file_to_image(mega->mlx,
		mega->conf.ea, &ptr->width, &ptr->height)) == NULL)
		return (-1);
	ptr->addr = mlx_get_data_addr(ptr->img,
	&ptr->bpp, &ptr->linelen, &ptr->endian);
	return (ft_loadsprites2(mega));
}

void	ft_floor_and_ceiling(t_mega *mega, int color, int x, t_res start_end)
{
	char *dst;

	while (start_end.height <= start_end.width)
	{
		dst = mega->dat.addr + (start_end.height
		* mega->dat.linelen + x * (mega->dat.bpp / 8));
		*(unsigned int*)dst = color;
		start_end.height++;
	}
}

void	ft_pixelput(t_mega *mega, t_draw draw, int y, int x)
{
	double	texy;
	double	stepy;
	int		color;
	char	*src;
	char	*dst;

	stepy = (double)draw.tex.height / (double)draw.drawdist;
	texy = (draw.drawstart
	- mega->conf.res.height / 2 + draw.drawdist / 2) * stepy;
	while (++y < draw.drawend)
	{
		src = draw.tex.addr + ((int)texy * draw.tex.linelen
		+ draw.texx * (draw.tex.bpp / 8));
		dst = mega->dat.addr + (y * mega->dat.linelen
		+ x * (mega->dat.bpp / 8));
		color = *(unsigned int*)src;
		*(unsigned int*)dst = color;
		texy += stepy;
	}
}

void	ft_drawline2(t_mega *mega, int x, t_draw draw)
{
	int		y;
	int		color;
	t_res	start_end;

	y = draw.drawstart - 1;
	color = mega->conf.c.red << 16
	| mega->conf.c.green << 8 | mega->conf.c.blue;
	start_end.height = 0;
	start_end.width = y;
	ft_floor_and_ceiling(mega, color, x, start_end);
	ft_pixelput(mega, draw, y, x);
	color = mega->conf.f.red << 16
	| mega->conf.f.green << 8 | mega->conf.f.blue;
	start_end.height = draw.drawend;
	start_end.width = mega->conf.res.height - 1;
	ft_floor_and_ceiling(mega, color, x, start_end);
}

void	ft_drawsprite(t_mega *mega, int x, int texx, int spriteheight)
{
	int		y;
	int		color;
	int		d;
	int		texy;
	char	*str;

	y = mega->spconf.drawstarty;
	d = (y) * 256 - (mega->conf.res.height - 1) * 128 + spriteheight * 128;
	texy = ((d * mega->tex.sp.height) / spriteheight) / 256;
	while (y < mega->spconf.drawendy)
	{
		str = mega->tex.sp.addr +
		(texy * mega->tex.sp.linelen + texx * (mega->tex.sp.bpp / 8));
		color = *(unsigned int*)str;
		str = mega->dat.addr + (y * mega->dat.linelen +
		x * (mega->dat.bpp / 8));
		if ((color & 0x00FFFFFF) != 0)
			*(unsigned int*)str = color;
		d = (y) * 256 - mega->conf.res.height * 128 + spriteheight * 128;
		texy = ((d * mega->tex.sp.height) / spriteheight) / 256;
		if (texy < 0)
			texy = 0;
		y++;
	}
}
