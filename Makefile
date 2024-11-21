# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 15:49:16 by ychirouz          #+#    #+#              #
#    Updated: 2024/02/14 15:49:19 by ychirouz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Reset
Color_Off=\033[0m       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green=\033[0;32m
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White=\033[0;37m        # White

# Bold
BBlack=\033[1;30m
BRed=\033[1;31m
BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;35m
BCyan=\033[1;36m
BWhite=\033[1;37m

NAME = minishell

GNL = gnl.a

SRC_MINI =	main.c								\
			src/Parser/fill_node.c				\
			src/Parser/heredoc.c				\
			src/Parser/parse_args.c				\
			src/LibUtils/utils1.c				\
			src/LibUtils/utils2.c				\
			src/LibUtils/utils_matrix.c			\
			src/LibUtils/utils_split.c			\
			src/LibUtils/utils_fd.c				\
			src/LibUtils/utils_lst.c			\
			src/LibUtils/utils_atoi_itoa.c		\
			src/LibUtils/utils_str_1.c			\
			src/LibUtils/utils_str_2.c			\
			src/LibUtils/utils_str_3.c			\
			src/Lexer/expand.c					\
			src/Lexer/ft_cmdsubsplit.c			\
			src/Lexer/ft_cmdtrim.c				\
			src/Lexer/ft_strtrim_all.c			\
			src/Lexer/prompt.c					\
			src/Handling/error.c				\
			src/Handling/signal.c				\
			src/Handling/starting.c				\
			src/Exec/custom_cmd.c				\
			src/Exec/exec.c						\
			src/Exec/check_cmd.c					\
			src/Exec/get_params.c				\
			src/Env/env.c						\
			src/Builtins/builtins.c
OBJ_MINI	= $(SRC_MINI:.c=.o)

CC = @gcc

CFLAGS = -Werror -Wextra -Wall

INCLUDE = -I include

RM = rm -rf

all:	$(NAME)

$(NAME):	$(OBJ_MINI)
		@make -s -C get_next_line
		@echo -e "\e[1A\e\r[0K${BWhite}Get_next_line : $(BGreen)[OK✓]${Color_Off}"
		@echo "${BWhite}Minishell : [...]${Color_Off}"
		$(CC) $(CFLAGS) $(OBJ_MINI) -lreadline $(INCLUDE) get_next_line/$(GNL) -o $(NAME) 
		@echo -e "\e[1A\e\r[0K${BWhite}Minishell : $(BGreen)[OK✓]${Color_Off}"

clean:
		@make clean -s -C get_next_line
		@$(RM) $(OBJ_MINI)
		@echo "${BWhite}Deleted Files : $(BGreen)[OK✓]${Color_Off}"

fclean:		clean
		@make fclean -s -C get_next_line
		@$(RM) $(NAME) $(GNL)
		@echo "${BWhite}Deleted Executable : $(BGreen)[OK✓]${Color_Off}"

re:		fclean all

.PHONY:	all clean fclean re
