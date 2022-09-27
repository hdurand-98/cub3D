/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:42:54 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 15:50:29 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void	ft_rotate(t_mega *mega, double coef)
{
	double olddirx;
	double oldpx;

	olddirx = mega->conf.player.dirx;
	mega->conf.player.dirx = mega->conf.player.dirx *
	cos(coef) - mega->conf.player.diry * sin(coef);
	mega->conf.player.diry = olddirx * sin(coef) +
		mega->conf.player.diry * cos(coef);
	oldpx = mega->conf.player.planex;
	mega->conf.player.planex = mega->conf.player.planex *
	cos(coef) - mega->conf.player.planey * sin(coef);
	mega->conf.player.planey = oldpx * sin(coef) +
		mega->conf.player.planey * cos(coef);
}

void	ft_left(t_mega *mega)
{
	if (mega->map[(int)(mega->conf.player.posy)]
		[(int)(mega->conf.player.posx
	+ mega->conf.player.diry * 0.11)] != '1')
		mega->conf.player.posx += mega->conf.player.diry * 0.11;
	if (mega->map[(int)(mega->conf.player.posy
	- mega->conf.player.dirx * 0.11)]
		[(int)mega->conf.player.posx] != '1')
		mega->conf.player.posy -= mega->conf.player.dirx * 0.11;
}

void	ft_right(t_mega *mega)
{
	if (mega->map[(int)(mega->conf.player.posy)]
		[(int)(mega->conf.player.posx
		- mega->conf.player.diry * 0.11)] != '1')
		mega->conf.player.posx -= mega->conf.player.diry * 0.11;
	if (mega->map[(int)(mega->conf.player.posy
	+ mega->conf.player.dirx * 0.11)]
		[(int)mega->conf.player.posx] != '1')
		mega->conf.player.posy += mega->conf.player.dirx * 0.11;
}

void	ft_forward(t_mega *mega)
{
	if (mega->map[(int)(mega->conf.player.posy)]
		[(int)(mega->conf.player.posx
		+ mega->conf.player.dirx * 0.11)] != '1')
		mega->conf.player.posx += mega->conf.player.dirx * 0.11;
	if (mega->map[(int)(mega->conf.player.posy
	+ mega->conf.player.diry * 0.11)]
		[(int)mega->conf.player.posx] != '1')
		mega->conf.player.posy += mega->conf.player.diry * 0.11;
}

void	ft_backward(t_mega *mega)
{
	if (mega->map[(int)(mega->conf.player.posy)]
		[(int)(mega->conf.player.posx
		- mega->conf.player.dirx * 0.11)] != '1')
		mega->conf.player.posx -= mega->conf.player.dirx * 0.11;
	if (mega->map[(int)(mega->conf.player.posy
	- mega->conf.player.diry * 0.11)]
		[(int)mega->conf.player.posx] != '1')
		mega->conf.player.posy -= mega->conf.player.diry * 0.11;
}
