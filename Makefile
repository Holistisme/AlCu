# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 00:04:27 by aheitz            #+#    #+#              #
#    Updated: 2026/01/20 13:18:03 by benpicar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Sources
SRCS_DIR 	= srcs/

RAYLIB		= libraylib.a
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
SRC_GRAPH		= click.c \
				close.c   \
				draw.c    \
				render.c  \
				setup.c

SRC_BON_DIR	= bonus/
SRC_BONN 	= main_bonus.c \
			  Ai_bonus.c

SRC			+= $(addprefix ${SRC_UTI_DIR}, ${SRC_UTI})
SRC			+= $(addprefix ${SRC_PAR_DIR}, ${SRC_PAR})
SRC			+= $(addprefix ${SRC_GAM_DIR}, ${SRC_GAM})
SRCS		= $(addprefix ${SRCS_DIR}, ${SRC})

#Bonus
SRC_BON		= $(addprefix ${SRC_UTI_DIR}, ${SRC_UTI})
SRC_BON		+= $(addprefix ${SRC_PAR_DIR}, ${SRC_PAR})
SRC_BON		+= $(addprefix ${SRC_BON_DIR}, ${SRC_BONN})
SRC_BON		+= $(addprefix ${SRC_GRAPH_DIR}, ${SRC_GRAPH})
SRC_BON		+= $(addprefix ${SRC_GAM_DIR}, ${SRC_GAM})

SRCS_BON	= $(addprefix ${SRCS_DIR}, ${SRC_BON})

#Object
OBJS_DIR	= objects/
OBJS		= $(addprefix ${OBJS_DIR}, ${SRC:.c=.o})
OBJS_BON	= $(addprefix ${OBJS_DIR}, ${SRC_BON:.c=.o})

INCLUDES	= includes
NAME		= alum1
NAME_BON	= alum1_bonus
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I ${INCLUDES} -I raylib/src -g3 -O3
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
				@${CC} ${CFLAGS} ${OBJS} -o $@
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

${OBJS_DIR}:
				@mkdir -p ${OBJS_DIR}

clean:			raylib_clean
				@${RM} ${OBJS} ${OBJS_BON}
				@${RM} -r ${OBJS_DIR}
				@echo "${RED}'${NAME}' and '${NAME_BON}' objects are deleted ! 👍${RESET}"

fclean:			clean
				@${RM} ${NAME} ${NAME_BON}
				@echo "${RED}'${NAME}' and '${NAME_BON}' are deleted ! 👍${RESET}"

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

bonus:			head ${RAYLIB} ${NAME_BON}

${NAME_BON}:	${OBJS_BON}
				@${CC} ${CFLAGS} ${OBJS_BON} ${LDLIBS} -o $@
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

${RAYLIB}:
				@$(MAKE) -C raylib/src PLATFORM=PLATFORM_DESKTOP
				@echo "${GREEN}'${RAYLIB}' library compiled ! ✅${RESET}"

raylib_clean:
				@$(MAKE) -C raylib/src clean

re_bonus:		fclean bonus

.PHONY:			all clean fclean re head bonus raylib_clean

