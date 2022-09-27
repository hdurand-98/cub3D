/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:09:04 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 15:16:25 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

char	*ft_niquelanorme(int *ret)
{
	*ret = -1;
	return (0);
}

char	*ft_gnl(int depth, int *ret, int fd)
{
	char	buff[1];
	char	*out;

	if (!(read(fd, buff, 1)))
		buff[0] = 0;
	if (buff[0] == '\n' || buff[0] == 0)
	{
		if (!(out = malloc(sizeof(char) * depth + 1)))
			return (ft_niquelanorme(ret));
		out[depth] = 0;
		*ret = 1;
		if (buff[0] == 0)
			*ret = 0;
		return (out);
	}
	else
	{
		if (!(out = ft_gnl(depth + 1, ret, fd)))
			return (ft_niquelanorme(ret));
		out[depth] = buff[0];
	}
	return (out);
}
