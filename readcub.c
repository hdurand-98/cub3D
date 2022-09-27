/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 20:18:49 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 16:30:44 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

int		ft_checkcub(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		if (str[i + 1] == 'c' && str[i + 2] == 'u'
		&& str[i + 3] == 'b' && !str[i + 4])
			return (1);
	return (0);
}

char	**ft_readmap(int *ret, int fd, int nbline)
{
	char **map;
	char *line;

	line = ft_gnl(0, ret, fd);
	if (line[0] == 0 && *ret == 1 && nbline == 0)
		return (ft_passnorm(line, ret, fd, nbline));
	if (*ret == -1)
		return (0);
	if (*ret == 0)
	{
		if (!(map = malloc(sizeof(char **) * (nbline + 2))))
			return (ft_freeline(line));
		map[nbline] = ft_strdup(line);
		map[nbline + 1] = 0;
		free(line);
		return (map);
	}
	else
	{
		if (!(map = ft_readmap(ret, fd, nbline + 1)))
			return (ft_freeline(line));
		map[nbline] = ft_strdup(line);
		free(line);
	}
	return (map);
}

int		ft_cubmode(int ac, char **av, t_mega *mega)
{
	mega->mlx = mlx_init();
	mega->map = NULL;
	mlx_get_screen_size(mega->mlx,
		&mega->conf.res.width, &mega->conf.res.height);
	if (ac == 2)
	{
		if (!ft_checkcub(av[1]))
			return (-1);
		else
			return (0);
	}
	else if (ac == 3)
	{
		if (av[2][0] == '-' && av[2][1] == '-' &&
			av[2][2] == 's' && av[2][3] == 'a' &&
			av[2][4] == 'v' && av[2][5] == 'e' && !av[2][6])
		{
			if (!ft_checkcub(av[1]))
				return (-1);
			return (1);
		}
	}
	return (-1);
}

int		ft_error(int fd, t_mega *mega, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	write(1, str, i);
	i = -1;
	if (fd == -2)
		exit(0);
	close(fd);
	if (mega->map != NULL)
	{
		while (mega->map[++i] != NULL)
			free(mega->map[i]);
		free(mega->map);
	}
	free(mega->sprites);
	free(mega->conf.no);
	free(mega->conf.so);
	free(mega->conf.ea);
	free(mega->conf.we);
	free(mega->conf.s);
	exit(0);
	return (-1);
}

int		main(int ac, char **av)
{
	int		ret;
	int		fd;
	t_mega	mega;

	if ((mega.save = ft_cubmode(ac, av, &mega)) == -1)
		return (ft_error(-2, &mega, "Error\nInvalid Argument\n"));
	ret = 1;
	fd = open(av[1], O_RDONLY);
	ft_readconf(&ret, fd, &mega);
	if (ret == -1)
		return (ft_error(fd, &mega, "Error\nInvalid configuration\n"));
	if (ret == 1)
		mega.map = ft_readmap(&ret, fd, 0);
	ret = ft_checkmap(&mega);
	if (ret == -1)
		return (ft_error(fd, &mega, "Error\nInvalid map\n"));
	if (mega.save == 0)
		ret = ft_window(&mega);
	else
		ret = ft_save(&mega);
	if (ret == 0)
		ft_error(fd, &mega, "Error\nCan't run Cub3D\n");
	return (ret);
}
