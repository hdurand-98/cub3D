/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:20:18 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 16:02:10 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

int	ft_quit(t_mega *mega)
{
	int i;

	i = -1;
	if (mega->save == 0)
		mlx_destroy_window(mega->mlx, mega->mlx_win);
	if (mega->map != NULL)
	{
		while (mega->map[++i] != NULL)
			free(mega->map[i]);
		free(mega->map);
	}
	free(mega->sprites);
	mlx_destroy_image(mega->mlx, mega->tex.no.img);
	free(mega->conf.no);
	mlx_destroy_image(mega->mlx, mega->tex.so.img);
	free(mega->conf.so);
	mlx_destroy_image(mega->mlx, mega->tex.ea.img);
	free(mega->conf.ea);
	mlx_destroy_image(mega->mlx, mega->tex.we.img);
	free(mega->conf.we);
	mlx_destroy_image(mega->mlx, mega->tex.sp.img);
	free(mega->conf.s);
	exit(0);
	return (0);
}

int	ft_move(int keycode, t_mega *mega)
{
	if (keycode == 97)
		ft_left(mega);
	else if (keycode == 100)
		ft_right(mega);
	else if (keycode == 119)
		ft_forward(mega);
	else if (keycode == 115)
		ft_backward(mega);
	else if (keycode == 65363)
		ft_rotate(mega, 0.1);
	else if (keycode == 65361)
		ft_rotate(mega, -0.1);
	else if (keycode == 65307)
		ft_quit(mega);
	return (0);
}

int	ft_nextframe(t_mega *mega)
{
	mega->dat.img = mlx_new_image(mega->mlx,
		mega->conf.res.width, mega->conf.res.height);
	mega->dat.addr = mlx_get_data_addr(mega->dat.img, &mega->dat.bpp,
		&mega->dat.linelen, &mega->dat.endian);
	ft_raycast(mega);
	mlx_put_image_to_window(mega->mlx, mega->mlx_win, mega->dat.img, 0, 0);
	mlx_destroy_image(mega->mlx, mega->dat.img);
	return (1);
}

int	ft_window(t_mega *mega)
{
	if (ft_loadsprites(mega) == -1)
		return (0);
	mega->mlx_win = mlx_new_window(mega->mlx,
		mega->conf.res.width, mega->conf.res.height, "cub3D");
	mlx_hook(mega->mlx_win, 2, 1L << 0, ft_move, mega);
	mlx_hook(mega->mlx_win, 33, 0L, ft_quit, mega);
	mlx_loop_hook(mega->mlx, ft_nextframe, mega);
	mlx_loop(mega->mlx);
	return (1);
}

int	ft_save(t_mega *mega)
{
	if (ft_loadsprites(mega) == -1)
		return (0);
	mega->dat.img = mlx_new_image(mega->mlx,
		mega->conf.res.width, mega->conf.res.height);
	mega->dat.addr = mlx_get_data_addr(mega->dat.img, &mega->dat.bpp,
		&mega->dat.linelen, &mega->dat.endian);
	ft_raycast(mega);
	ft_savesprite(mega);
	mlx_destroy_image(mega->mlx, mega->dat.img);
	return (1);
}
