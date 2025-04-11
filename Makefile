# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 22:29:07 by ahomari           #+#    #+#              #
#    Updated: 2024/07/24 13:28:34 by ahomari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS					= -Wall -Wextra -Werror -I$(READLINE_I)
CC						= cc
RM						= rm -rf
NAME					= minishell
HEAD					= include/minishell.h

SRC						= src/ft_atoi.c src/ft_isalpha.c src/ft_memset.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c src/ft_strdup.c \
							src/ft_strjoin.c src/ft_strlen.c src/ft_strncmp.c src/ft_substr.c src/ft_calloc.c src/ft_memcpy.c src/ft_bzero.c src/ft_strcmp.c src/ft_isdigit.c \
							src/ft_isalnum.c src/ft_itoa.c src/linkedlist_cmd.c src/linkedlist_env.c src/linkedlist.c src/ft_free.c src/error_msg.c
S_OBJ					= ${SRC:.c=.o}

READLINE_L = /Users/ahomari/.brew/opt/readline/lib
READLINE_I = /Users/ahomari/.brew/opt/readline/include

SRC_MAN					= main.c execution/ft_execution.c  parsing/split_arg.c parsing/ft_addspace.c parsing/ft_realloc.c parsing/ft_remove_quotes.c parsing/ft_split_custom.c \
							parsing/syntax_error.c parsing/ft_expand.c parsing/ft_here_doc.c execution/ft_dup_redirection.c builtins/ft_export.c builtins/ft_manage_export.c builtins/utils_export.c \
							builtins/ft_cd.c builtins/ft_unset.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_pwd.c builtins/ft_exit.c signals/ft_signals.c parsing/ft_remove_here.c \
							execution/ft_exit_stat.c parsing/utilis.c execution/utilis.c builtins/utilis_cd.c parsing/ft_parce.c parsing/ft_remove_backslash.c builtins/utilis_export2.c parsing/utilis_parce.c
							
							
SM_OBJ					= ${SRC_MAN:.c=.o}

all:					${NAME}

%.o: %.c				${HEAD}
						${CC} ${FLAGS}  -c $< -o $@

${NAME}:				${SM_OBJ} ${S_OBJ} ${HEAD}
						@${CC} ${SM_OBJ} ${S_OBJ} -L$(READLINE_L) -lreadline -lhistory -o ${NAME}
						@echo "${GREEN}${NAME} Created!${DEFAULT}"

clean:
						@${RM} ${SM_OBJ} ${S_OBJ}
						@echo "${YELLOW}Object Files deleted!${DEFAULT}"

fclean:					clean
						@${RM} ${NAME}
						@echo "${RED}All Deleted!${DEFAULT}"

re: 					fclean all

.PHONY: 				fclean all re  clean

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m