NONE = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

NAME_CLIENT = client
NAME_SERVER = server

OBJDIR = ./obj/
HEADERDIR = ./includes/

SRCDIR_CLIENT = ./srcs/client/
SRCS_CLIENT = client.c client_utils.c
OBJ_CLIENT = $(addprefix $(OBJDIR), $(SRCS_CLIENT:.c=.o))
HEADER_CLIENT = $(addprefix $(HEADERDIR), client.h)

SRCDIR_SERVER = ./srcs/server/
SRCS_SERVER = server.c
OBJ_SERVER = $(addprefix $(OBJDIR), $(SRCS_SERVER:.c=.o))
HEADER_SERVER = $(addprefix $(HEADERDIR), server.h)

SRC_UTILS_DIR = ./srcs/utils/
SRCS_UTILS = ft_putnbr_fd.c ft_isdigit.c ft_putstr_fd.c ft_atoi.c\
	 error_handler.c ft_putendl_fd.c ft_memset.c str_join_char.c ft_strlen.c
OBJ_UTILS = $(addprefix $(OBJDIR), $(SRCS_UTILS:.c=.o))
HEADER_UTILS = $(addprefix $(HEADERDIR), utils.h)

OBJ_ALL = $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_UTILS)

all: $(NAME_CLIENT) $(NAME_SERVER)


$(NAME_CLIENT): $(OBJDIR) $(OBJ_CLIENT) $(OBJ_UTILS) $(HEADER_CLIENT) $(HEADER_UTILS)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_UTILS) -o $@
	@echo "$(PURPLE) $(NAME_CLIENT) has been created $(NONE)"

$(NAME_SERVER): $(OBJDIR) $(OBJ_SERVER) $(OBJ_UTILS) $(HEADER_SERVER) $(HEADER_UTILS)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_UTILS) -o $@
	@echo "$(PURPLE) $(NAME_SERVER) has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

################################
##   client compilation    ##
################################

$(OBJ_CLIENT): $(OBJDIR)%.o: $(SRCDIR_CLIENT)%.c $(HEADER_CLIENT) $(HEADER_UTILS)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for client has been created $(NONE)"

###############################
##    server compilation    ##
###############################

$(OBJ_SERVER): $(OBJDIR)%.o: $(SRCDIR_SERVER)%.c $(HEADER_SERVER) $(HEADER_UTILS)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for server has been created $(NONE)"

#############################
##   utils compilation    ##
#############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.c $(HEADER_UTILS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for utils has been created $(NONE)"

clean:
	$(RM) $(OBJDIR)
	@echo "$(RED) $(OBJDIR) has been deleted $(NONE)"

fclean: clean
	$(RM) $(NAME_CLIENT)
	@echo "$(RED) $(NAME_CLIENT) has been deleted $(NONE)"
	$(RM) $(NAME_SERVER)
	@echo "$(RED) $(NAME_SERVER) has been deleted $(NONE)"

re:	fclean all

.PHONY: all clean fclean re
