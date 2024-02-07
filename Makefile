# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 11:12:26 by mchenava          #+#    #+#              #
#    Updated: 2024/02/07 15:11:03 by mchenava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minirt

BUILD_DIR= build
SRC_DIR= RayTracer
INC_DIR= $(SRC_DIR)/includes
MLX_DIR= ./minilibx-linux
GL_DIR= ./42LiteGL

WIN_DIR= $(SRC_DIR)/window
UTILS_DIR= $(SRC_DIR)/utils

MLX= $(MLX_DIR)/libmlx.a
GL= $(GL_DIR)/lite_gl.a

S_DIRS = $(WIN_DIR) $(UTILS_DIR)
B_DIRS = $(S_DIRS:$(SRC_DIR)/%=$(BUILD_DIR)/%)

WIN_SRC=	$(WIN_DIR)/init_window.c \
			$(WIN_DIR)/hooks.c \
			$(WIN_DIR)/init_glx.c

UTILS_SRC=	$(UTILS_DIR)/clean.c \
			$(UTILS_DIR)/init_rt.c

SRC= $(SRC_DIR)/minirt.c
SRC+= $(WIN_SRC) $(UTILS_SRC)

OBJECTS= $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS= $(INC_DIR)/%.h $(SRC_DIR)/%.h

FLAGS= -Wall -Wextra -Werror -lX11
OBJ_FLAGS= -Wall -Wextra -Werror -I$(GL_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): dirs compile

help :
	@echo $(SRC)
	@echo $(OBJECTS)

compile: $(OBJECTS) $(MLX) $(GL)
	@echo "Compiling $(NAME)"
	@ $(CC) $^ $(FLAGS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(OBJ_FLAGS) -c $< -o $@ 

dirs : 
	mkdir -p $(BUILD_DIR)
	mkdir -p $(B_DIRS)

mlx:
	@make -C $(MLX_DIR)

$(MLX) : mlx

gl:
	@make -C $(GL_DIR) -j4

$(GL) : gl

check :
	norminette $(GL_DIR) $(SRC_DIR) > norm.log


clean :
	$(RM) $(OBJECTS)
	$(RM) -r $(BUILD_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(GL_DIR) clean

fclean : clean
	$(RM) $(NAME)
	$(MAKE) -C $(GL_DIR) fclean

re : fclean all