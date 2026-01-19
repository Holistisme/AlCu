# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 00:04:27 by aheitz            #+#    #+#              #
#    Updated: 2026/01/20 00:04:46 by aheitz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Sources
SRCS_DIR 	= srcs/

LDLIBS		= -Lraylib/src -lraylib -lGL -lm -ldl -lpthread -lrt -lX11

SRC			= main.c
			  
SRC_UTI_DIR	= utils/
SRC_UTI	 	= utils.c \
			  get_next_line.c \
			  get_next_line_utils.c \
			  print.c

SRC_PAR_DIR	= parsing/
SRC_PAR	 	= parsing.c

SRC_GAM_DIR	= game/
SRC_GAM	 	= Ai.c

SRC_GRAPH_DIR	= graphics/
SRC_GRAPH	 	= open.c

SRC			+= $(addprefix ${SRC_UTI_DIR}, ${SRC_UTI})
SRC			+= $(addprefix ${SRC_PAR_DIR}, ${SRC_PAR})
SRC			+= $(addprefix ${SRC_GAM_DIR}, ${SRC_GAM})
SRC			+= $(addprefix ${SRC_GRAPH_DIR}, ${SRC_GRAPH})
SRCS		= $(addprefix ${SRCS_DIR}, ${SRC})

#Object
OBJS_DIR	= objects/
OBJS		= $(addprefix ${OBJS_DIR}, ${SRC:.c=.o})

INCLUDES	= includes
NAME		= alum1
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I ${INCLUDES} -g3 -O3
CC			= cc

#Colors
LIGHT_GRAY	= \033[2m
ORANGE		= \033[1;33m
DARK_GRAY	= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
RESET		= \033[0m

#Forme
BOLD		= \033[1m
ITALIC		= \033[3m
UNDERLINE	= \033[4m
CROSS		= \033[9m
FLASH		= \033[5m
NEGATIF		= \033[7m

all:			head ${NAME}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
				@mkdir -p $(dir $@)	
				@${CC} ${CFLAGS} -c $< -o $@

${NAME}:		${OBJS}
				@${CC} ${CFLAGS} ${OBJS} ${LDLIBS} -o $@
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

${OBJS_DIR}:
				@mkdir -p ${OBJS_DIR}

clean:
				@${RM} ${OBJS}
				@${RM} -r ${OBJS_DIR}
				@echo "${RED}'${NAME}' objects are deleted ! 👍${RESET}"

fclean:			clean
				@${RM} ${NAME}
				@echo "${RED}'${NAME}' is deleted ! 👍${RESET}"

re:				fclean all

head:			
				@echo
				@echo "${CYAN}    ___     _    ______        ${RESET}"
				@echo "${CYAN}   /   |   (_)  / ____/__  __  ${RESET}"
				@echo "${CYAN}  / /| |  / /  / /   / / / /  ${RESET}"
				@echo "${CYAN} / ___ | / /  / /___/ /_/ /   ${RESET}"
				@echo "${CYAN}/_/  |_|/_/   \____/\__,_/    ${RESET}"
				@echo
				@echo "${YELLOW}     Nim Game - AI Strategy${RESET}"
				@echo

bonus:
	$(MAKE) -C raylib/src PLATFORM=PLATFORM_DESKTOP

bonus_clean:
	$(MAKE) -C raylib/src clean

.PHONY:			all clean fclean re head bonus

