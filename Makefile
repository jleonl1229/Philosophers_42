# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 15:08:43 by jleon-la          #+#    #+#              #
#    Updated: 2024/07/31 15:08:43 by jleon-la         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM =	philo
NAME	=	$(PROGRAM)

HEADER	=	./philo.h

CC		=	gcc

CFLAGS	=	-Werror -Wall -Wextra -pthread

SRCS	=		main.c	       		\
				chores.c      		\
				tasks.c  	   		\
				initializer.c 		\
				tools.c       		\
				routine_process.c	\

OBJS	=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all