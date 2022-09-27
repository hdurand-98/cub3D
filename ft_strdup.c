/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:30:06 by hdurand           #+#    #+#             */
/*   Updated: 2020/10/01 19:56:03 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

char	*ft_strdup(char *src)
{
	char*dest;
	int i;

	i = 0;
	while (src[i])
	{
		if (src[i] < 32 || src[i] == 127)
			return (NULL);
		i++;
	}
	if (!(dest = malloc(i + 1)))
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**ft_freeline(char *line)
{
	free(line);
	return (0);
}
