/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:18:03 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 15:14:39 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

char				**ft_passnorm(char *line, int *ret, int fd, int nbline)
{
	free(line);
	return (ft_readmap(ret, fd, nbline));
}

void				ft_isspace(char *str, int *i)
{
	while (str[*i] == 32)
		*i = *i + 1;
}

int					r_atoi(char *strf, int *i, int max)
{
	int result;

	result = 0;
	while (strf[*i] > 47 && strf[*i] < 58 && result < max)
	{
		result = result * 10 + (strf[*i] - 48);
		*i = *i + 1;
	}
	if (result >= max)
		return (max);
	else
		return (result);
}

int					ft_atoi(char *strf, int *index, int max)
{
	int result;

	result = 0;
	ft_isspace(strf, index);
	if (strf[*index] == '-')
		return (-1);
	while (strf[*index] > 47 && strf[*index] < 58 && result < max)
	{
		result = result * 10 + (strf[*index] - 48);
		*index = *index + 1;
	}
	if (result >= max)
	{
		while (strf[*index] > 47 && strf[*index] < 58)
			*index = *index + 1;
		return (max);
	}
	else
		return (result);
	return (0);
}
