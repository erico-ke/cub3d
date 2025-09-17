NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

MLX42_PATH = libs/MLX42
MLX42 = $(MLX42_PATH)/build/libmlx42.a

LIBFT_PATH = libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

HEADERS = -I ./libs -I $(MLX42_PATH)/include/MLX42 -I $(LIBFT_PATH)

SRCDIR = ./src/
SRCS = $(wildcard $(SRCDIR)/*.c)

OBJDIR = ./obj/
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(MLX42) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX42) $(LIBFT) $(HEADERS) -lglfw -o $(NAME) -lm
	@echo "$(GREEN)$(EYE) $(NAME) compiled successfully! $(DEF_COLOR)"

$(LIBFT) :
	@make -C $(LIBFT_PATH)
	@echo "$(GREEN)$(EYE) libft compiled successfully! $(DEF_COLOR)"

$(MLX42) :
	@cmake $(MLX42_PATH) -B $(MLX42_PATH)/build && make -C $(MLX42_PATH)/build -j4
	@echo "$(GREEN)$(EYE) MLX42 compiled successfully! $(DEF_COLOR)"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

clean :
	@$(RM) $(OBJDIR)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX42_PATH)/build clean
	@echo "$(WHITE)$(EYE) Cleaned object files and MLX42 build files! $(DEF_COLOR)"

fclean : clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(MLX42_PATH)/build
	@echo "$(WHITE)$(EYE) Fully cleaned project! $(DEF_COLOR)"

re : fclean all

.PHONY : all clean fclean re

DEF_COLOR = \033[0;39m
GREEN = \033[1;92m
YELLOW = \033[1;93m
EYE = \033[1;95m
WHITE = \033[5;97m