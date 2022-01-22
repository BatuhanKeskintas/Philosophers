# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkeskint <bkeskint@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 23:09:48 by bkeskint          #+#    #+#              #
#    Updated: 2021/12/15 23:11:02 by bkeskint         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		philo.c extra.c functions.c initialize.c threads.c \

OBJ		=		${SRC:.c=.o}

CC		= 		gcc
CFLAGS	=		-Wall -Wextra -Werror
RM		= 		rm -f

NAME	= 		philo

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -g $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

clean:		
			$(RM) *.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re