# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/10/11 14:27:44 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

FLAG = -fsanitize=thread -fsanitize=thread -Wall -Werror -Wextra

SRC=	src/philosopher.c	\
	src/ft_putnbr.c		\
	src/ft_exit.c		\
	src/ft_malloc.c		\
	src/ft_lstnew.c		\
	src/ft_atoi.c		\
	src/ft_strlen.c		\
	src/prog.c		\
	src/prog2.c		\
	src/philoinit.c		\
	src/threadinit.c	\
	src/fork.c		\
	src/ft_posclear.c	\
	src/ft_lstdelone.c	\
	src/ft_setpos.c

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -pthread -I include -c $< -o $(<:.c=.o)

INC = include/philosopher.h

all:	$(NAME)

$(NAME):	$(OBJ) $(INC)
	$(CC) $(FLAG) $(OBJ) -pthread -I include -o $(NAME)

clean:
	rm -f $(OBJ) libft.a

fclean:	clean
	rm -f $(NAME)

re			: fclean all 

git:
	make fclean
	git add src
	git add Makefile
	git add include/
	read S; git commit -m $${S}
	git push

fini:
	make git

.PHONY: all clean fclean re
