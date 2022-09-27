NAME		=	Cub3D
DIRSRC		=	./
DIROBJ		=	./
INCLUDE		=	readcub.h
SRC			=	ft_atoi.c ft_gnl.c ft_strdup.c readcub.c readconf.c checkmap.c window.c raycaster.c bmp.c subwindow.c moving.c rayfunct.c spritefunct.c tex.c floceil.c spawn.c

OBJB		=	$(SRCB:.c=.o)
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)/%)

LIB			=	mlx_linux/libmlx_Linux.a

CFLAGS		=	-Wall -Wextra -Werror

CC			=	clang
RM			=	rm -f


$(NAME)	:		$(LIB) $(OBJ)
	$(CC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME) $(OBJS) mlx_linux/libmlx_Linux.a

$(LIB)	:			
				#sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev
				make -C mlx_linux/

clean	:
				make -C mlx_linux/ clean
				cd $(DIROBJ) && $(RM) $(OBJ) $(OBJB)

all		:		$(NAME)

fclean	:		clean
				$(RM) $(NAME)

re		:		fclean all

.PHONY	:		all clean fclean re bonus

%.o		:		$(DIRSRC)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -I/usr/include -Imlx_linux -O3 -o $(DIROBJ)/$@ -c $<
