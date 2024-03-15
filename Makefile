# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 22:38:40 by kahmada           #+#    #+#              #
#    Updated: 2024/03/15 01:41:38 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
cc = cc
header = pipex.h
CFLAGS = -Wall -Wextra -Werror
srcs = pipex.c\
	   utils_pipex.c
objs = $(srcs:.c=.o)
all: $(NAME)

%.o: %.c $(header)
	$(cc) $(CFLAGS) -o $@ -c $<

$(NAME): $(objs)
	ar rc $(NAME) $(objs)

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all