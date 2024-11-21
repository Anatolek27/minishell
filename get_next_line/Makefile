# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akunegel <akunegel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 19:17:03 by akunegel          #+#    #+#              #
#    Updated: 2024/02/12 19:17:03 by akunegel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = @gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

.c.o:	$(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

all:	$(NAME)

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
