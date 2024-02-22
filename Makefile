# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/12/15 13:18:56 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE=	philosopher.c	\
		ft_putnbr.c		\
		ft_exit.c		\
		ft_malloc.c		\
		ft_lstnew.c		\
		ft_atoi.c		\
		ft_strlen.c		\
		prog.c		\
		prog2.c		\
		philoinit.c		\
		threadinit.c	\
		fork.c		\
		ft_posclear.c	\
		ft_lstdelone.c	\
		ft_setpos.c

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ			=	$(SRC:.c=.o)

DOBJ		=	${SRC:.c=.d}

NAME = philo

INC = include/philosopher.h

CC			=	gcc

FLAGS = -fsanitize=thread -fsanitize=thread -Wall -Werror -Wextra -MMD

RM			=	rm -f

all:		$(NAME)

-include ${DOBJ}
.c.o:
			$(CC) $(FLAGS) -pthread -I include -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ) $(INC)
	$(CC) $(FLAGS) $(OBJ) -pthread -I include -o $(NAME)

clean:
			${RM} $(OBJ) ${DOBJ}

fclean:		clean
			${RM} $(NAME)

re:			fclean all 

.PHONY:		all clean fclean re .c.o
