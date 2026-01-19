#Sources
SRCS_DIR 	= srcs/

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

SRC			+= $(addprefix ${SRC_UTI_DIR}, ${SRC_UTI})
SRC			+= $(addprefix ${SRC_PAR_DIR}, ${SRC_PAR})
SRC			+= $(addprefix ${SRC_GAM_DIR}, ${SRC_GAM})
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

all:			${NAME}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
				@mkdir -p $(dir $@)	
				@${CC} ${CFLAGS} -c $< -o $@

${NAME}:		${OBJS}
				@${CC} ${CFLAGS} ${OBJS} -o $@
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
				@echo
				@echo "    /|    //| |                                //   ) )  /__  ___/"
				@echo "   //|   // | |    ( )       __       ( )     //___/ /     / /"
				@echo "  // |  //  | |   / /     //   ) )   / /     / ___ (      / /"
				@echo " //  | //   | |  / /     //   / /   / /     //   | |     / /"
				@echo "//   |//    | | / /     //   / /   / /     //    | |    / /"
				@echo
				@echo

.PHONY:			all clean fclean re head

