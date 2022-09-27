/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcub.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:16:05 by hdurand           #+#    #+#             */
/*   Updated: 2021/03/25 18:07:05 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READCUB_H
# define READCUB_H
# define ROTA 0.1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx_linux/mlx.h"
# include <math.h>
# include <string.h>
# pragma pack(push, 1)

typedef struct	s_fileheader
{
	unsigned char	signature[2];
	unsigned int	filesize;
	short			reserved1;
	short			reserved2;
	unsigned int	fileoffset_to_pixelarray;
}				t_fileheader;

typedef struct	s_bitmapinfo
{
	unsigned int	dibheadersize;
	unsigned int	width;
	unsigned int	height;
	short			planes;
	short			bitsperpixel;
	unsigned int	compression;
	unsigned int	imagesize;
	unsigned int	ypixelpermeter;
	unsigned int	xpixelpermeter;
	unsigned int	numcolorspallette;
	unsigned int	mostimpcolor;
}				t_bitmapinfoheader;

typedef struct	s_bitmap
{
	t_fileheader		fileheader;
	t_bitmapinfoheader	bitmapinfoheader;
}				t_bitmap;
# pragma pack(pop)

typedef struct	s_pos
{
	float	x;
	float	y;
	double	dist;
}				t_pos;

typedef struct	s_res
{
	int width;
	int height;
}				t_res;

typedef struct	s_color
{
	int red;
	int green;
	int blue;
}				t_color;

typedef struct	s_play
{
	double dirx;
	double diry;
	double posx;
	double posy;
	double planey;
	double planex;
}				t_play;

typedef struct	s_conf
{
	t_res	res;
	t_play	player;
	int	*max_x;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	t_color	f;
	t_color	c;
}				t_conf;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		linelen;
	int		endian;
	int		height;
	int		width;
}				t_data;

typedef struct	s_tex
{
	t_data no;
	t_data so;
	t_data we;
	t_data ea;
	t_data sp;
}				t_tex;

typedef struct	s_spr
{
	int		drawstartx;
	int		drawendx;
	int		drawstarty;
	int		drawendy;
}				t_spr;

typedef struct	s_mega
{
	t_data	dat;
	t_conf	conf;
	t_tex	tex;
	void	*mlx;
	void	*mlx_win;
	char	**map;
	t_pos	*sprites;
	int		save;
	int		nbsprites;
	t_spr	spconf;
	double	transformx;
	double	transformy;
}				t_mega;

typedef struct	s_ray
{
	double	cameray;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	perpwalldist;
	int		side;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;

}				t_ray;

typedef struct	s_draw
{
	int		drawstart;
	int		drawend;
	int		texx;
	int		drawdist;
	t_data	tex;
}				t_draw;

typedef struct	s_spawn
{
	double dirx;
	double diry;
	double px;
	double py;
}				t_spawn;

char			**ft_freeline(char *line);
char			**ft_readmap(int *ret, int fd, int nbline);
char			**ft_passnorm(char *line, int *ret, int fd, int nbline);
char			*ft_strdup(char *str);
char			*ft_gnl(int i, int *y, int fd);
void			ft_readconf(int *ret, int fd, t_mega *mega);
int				ft_atoi(char *st, int *i, int max);
void			ft_res(char *str, t_conf *conf, int *ret);
void			ft_no(char *str, t_conf *conf, int *ret);
void			ft_so(char *str, t_conf *conf, int *ret);
void			ft_we(char *str, t_conf *conf, int *ret);
void			ft_ea(char *str, t_conf *conf, int *ret);
void			ft_s(char *str, t_conf *conf, int *ret);
void			ft_floor(char *str, t_conf *conf, int *ret);
void			ft_ceiling(char *str, t_conf *conf, int *ret);
void			ft_drawline2(t_mega *mega, int x, t_draw draw);
void			ft_drawsprite(t_mega *mega, int x, int texx, int lineheight);
int				ft_checkmap(t_mega *mega);
int				ft_loadsprites(t_mega *mega);
int				ft_loadsprites2(t_mega *mega);
int				ft_window(t_mega *mega);
void			ft_raycast(t_mega *mega);
int				ft_save(t_mega *mega);
void			ft_savesprite(t_mega *mega);
void			ft_rotate(t_mega *mega, double coef);
void			ft_left(t_mega *mega);
void			ft_right(t_mega *mega);
void			ft_forward(t_mega *mega);
void			ft_backward(t_mega *mega);
void			ft_chooseside(t_mega *mega, t_ray *ray);
void			ft_dda(t_mega *mega, t_ray *ray);
double			ft_wallx(t_mega *mega, t_ray *ray, t_draw *draw);
void			ft_rayinit(t_mega *mega, t_ray *ray, int x);
void			ft_sortsprites(t_mega *mega);
int				ft_spheight(t_mega *mega, int spriteheight);
int				ft_spwidth(t_mega *mega, int spritewidth, int spritescreenx);
void			ft_transforms(t_mega *mega, int y);
int				ft_mktexx(t_mega *mega, int *stripe, double tsfx, double tsfy);
int				ft_player_spawn(int y, int x, t_conf *conf, char c);
int				ft_quit(t_mega *mega);

#endif
