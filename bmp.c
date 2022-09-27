/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:51:51 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 15:57:03 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

struct s_bitmap	*ft_createbmp(t_mega *mega)
{
	t_bitmap *pbitmap;

	if ((pbitmap = (t_bitmap*)malloc(sizeof(t_bitmap))) == NULL)
		return (NULL);
	pbitmap->fileheader.signature[0] = 'B';
	pbitmap->fileheader.signature[1] = 'M';
	pbitmap->fileheader.reserved1 = 0;
	pbitmap->fileheader.reserved2 = 0;
	pbitmap->fileheader.filesize = mega->conf.res.height *
		mega->conf.res.width * sizeof(int) + sizeof(t_bitmap);
	pbitmap->fileheader.fileoffset_to_pixelarray = sizeof(t_bitmap);
	pbitmap->bitmapinfoheader.dibheadersize = sizeof(t_bitmapinfoheader);
	pbitmap->bitmapinfoheader.width = mega->conf.res.width;
	pbitmap->bitmapinfoheader.height = mega->conf.res.height;
	pbitmap->bitmapinfoheader.planes = 1;
	pbitmap->bitmapinfoheader.bitsperpixel = mega->dat.bpp;
	pbitmap->bitmapinfoheader.compression = 0;
	pbitmap->bitmapinfoheader.imagesize = mega->conf.res.height *
		mega->conf.res.width;
	pbitmap->bitmapinfoheader.ypixelpermeter = 0;
	pbitmap->bitmapinfoheader.xpixelpermeter = 0;
	pbitmap->bitmapinfoheader.numcolorspallette = 0;
	return (pbitmap);
}

unsigned int	*ft_createimage(t_mega *mega)
{
	unsigned int	*pixelbuffer;
	char			*dst;
	int				x;
	int				y;
	int				i;

	y = mega->conf.res.height - 1;
	i = 0;
	if ((pixelbuffer = (unsigned int*)malloc(mega->conf.res.height
	* mega->conf.res.width * sizeof(int))) == NULL)
		return (NULL);
	while (y >= 0)
	{
		x = 0;
		while (x < mega->conf.res.width)
		{
			dst = mega->dat.addr + (y * mega->dat.linelen + x *
				(mega->dat.bpp / 8));
			pixelbuffer[i] = *(unsigned int*)dst;
			++i;
			++x;
		}
		--y;
	}
	return (pixelbuffer);
}

void			ft_stop(int fd, t_bitmap *pb, t_mega *mega)
{
	close(fd);
	if (pb != NULL)
		free(pb);
	ft_quit(mega);
}

void			ft_savesprite(t_mega *mega)
{
	int				fd;
	t_bitmap		*pbitmap;
	unsigned int	*pixelbuffer;

	fd = open("screenshot.bmp", O_CREAT | O_TRUNC | O_WRONLY | O_APPEND);
	if (fd == -1)
		ft_quit(mega);
	if ((pbitmap = ft_createbmp(mega)) == NULL)
		return (ft_stop(fd, pbitmap, mega));
	if ((write(fd, pbitmap, sizeof(t_bitmap))) == -1)
		return (ft_stop(fd, pbitmap, mega));
	if ((pixelbuffer = ft_createimage(mega)) == NULL)
		return (ft_stop(fd, pbitmap, mega));
	write(fd, pixelbuffer, mega->conf.res.height
		* mega->conf.res.width * sizeof(int));
	close(fd);
	free(pbitmap);
	free(pixelbuffer);
	ft_quit(mega);
}
