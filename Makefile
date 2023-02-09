# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 20:26:19 by ojing-ha          #+#    #+#              #
#    Updated: 2023/02/09 13:22:23 by ojing-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR     = \033[0;39m
GRAY         = \033[0;90m
RED         = \033[0;91m
GREEN         = \033[0;92m
YELLOW         = \033[0;93m
BLUE         = \033[0;94m
MAGENTA     = \033[0;95m
CYAN         = \033[0;96m
WHITE         = \033[0;97m
NAME		= philo

CC			= gcc

SRCS_DIR	= srcs/
OBJS_DIR	= objs/
INCLUDES	= includes/

CFLAGS	= -Wall -Werror -Wextra -pthread -fsanitize=thread -g3

SRC_FILES	= philo_main\
				philo_libft\
				philo_getters\
				philo_inits\
				philo_routine


SRCS	= $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

all		:
		@mkdir -p $(OBJS_DIR)
		@echo "$(MAGENTA) --------------------------INSIDE PHILO-------------------------- $(CYAN)"
		@echo "\n"
		@make $(NAME)
		@echo "$(YELLOW)Done Creating ./philo$(DEF_COLOR)"
		@echo "\n"
		@echo "$(GREEN) -------------$(RED)I $(CYAN)AM $(GREEN)DONE $(YELLOW)MADAFAKA$(GREEN)-------------------------- $(DEF_COLOR)"

$(NAME)	: ${OBJS}
		@${CC} ${CFLAGS} -I ${INCLUDES} ${OBJS} -o ${NAME}
		@echo "$(GREEN)Creating ./philo ...$(DEF_COLOR)"

${OBJS_DIR}%.o:	$(SRCS_DIR)%.c
		@$(CC) $(CFLAGS) -c $^ -o $@
		@echo "$(GREEN)Compiling $<...$(DEF_COLOR)"


clean	:
		@echo "$(MAGENTA) --------------------------REMOVING objs/-------------------------- $(CYAN)"
		@echo "\n"
		@rm -rf $(OBJS_DIR)
		@echo "$(RED)Object Files Deleted$(DEF_COLOR)"
		@echo "\n"
		@echo "$(GREEN) --------------------------DONE--------------------------$(DEF_COLOR)"

fclean	:	clean
		@echo "$(MAGENTA) --------------------------REMOVING ./philo-------------------------- $(CYAN)"
		@echo "\n"
		@rm -f $(NAME)
		@echo "$(RED)./philo Deleted$(DEF_COLOR)"
		@echo "\n"
		@echo "$(GREEN) --------------------------DONE--------------------------$(DEF_COLOR)"

re		:fclean all

.PHONY	:all clean fclean re