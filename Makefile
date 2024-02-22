# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 11:12:26 by mchenava          #+#    #+#              #
#    Updated: 2024/02/22 16:03:14 by  mchenava        ###   ########.fr        #
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
CAM_DIR= $(SRC_DIR)/camera
RENDER_DIR= $(SRC_DIR)/rendering
CONTROLS_DIR= $(SRC_DIR)/controls
SCENE_DIR= $(SRC_DIR)/scene
SHADER_DIR= $(SRC_DIR)/shaders
SHAPES_DIR= $(SRC_DIR)/shapes

MLX= $(MLX_DIR)/libmlx.a
GL= $(GL_DIR)/lite_gl.a

S_DIRS = $(WIN_DIR) $(UTILS_DIR) $(CAM_DIR) $(RENDER_DIR) $(CONTROLS_DIR) $(SCENE_DIR) $(SHADER_DIR) $(SHAPES_DIR)
B_DIRS = $(S_DIRS:$(SRC_DIR)/%=$(BUILD_DIR)/%)

WIN_SRC=	$(WIN_DIR)/init_window.c \
			$(WIN_DIR)/hooks.c \
			$(WIN_DIR)/init_glx.c

UTILS_SRC=	$(UTILS_DIR)/clean.c \
			$(UTILS_DIR)/init_rt.c \
			$(UTILS_DIR)/vec_to_array.c

CAM_SRC=	$(CAM_DIR)/init_cam.c \
			$(CAM_DIR)/move_cam.c

RENDER_SRC= $(RENDER_DIR)/render.c \
			$(RENDER_DIR)/projection.c

CONTROLS_SRC= 	$(CONTROLS_DIR)/keyboard_ctrl.c \
				$(CONTROLS_DIR)/mouse_ctrl.c

SCENE_SRC=	$(SCENE_DIR)/scene.c

SHADER_SRC= $(SHADER_DIR)/gridshader.c \
			$(SHADER_DIR)/loadshader.c

SHAPES_SRC = 	$(SHAPES_DIR)/plane.c \
			$(SHAPES_DIR)/mesh.c \
			$(SHAPES_DIR)/sphere.c \
			$(SHAPES_DIR)/sphere_tri_tex.c \
			$(SHAPES_DIR)/shapes_tools.c \

SRC= $(SRC_DIR)/minirt.c
SRC+= $(WIN_SRC) $(UTILS_SRC) $(CAM_SRC) $(RENDER_SRC) $(CONTROLS_SRC) $(SCENE_SRC) $(SHADER_SRC) $(SHAPES_SRC)

OBJECTS= $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS= $(INC_DIR)/%.h $(SRC_DIR)/%.h

FLAGS= -Wall -Wextra -Werror -lX11 -lXext -lm -g3 -fsanitize=address
OBJ_FLAGS=  -I$(SRC_DIR) -I$(GL_DIR) -I$(MLX_DIR) -Wall -Wextra -Werror -fsanitize=address -g3

all: $(NAME)

$(NAME): dirs compile

help :
	@echo $(SRC)
	@echo $(OBJECTS)
	@echo $(HEADERS)

compile: $(OBJECTS) $(MLX) $(GL)
	@echo "Compiling $(NAME)"
	@ $(CC) $^ $(FLAGS) -o $(NAME)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "Compiling $@"
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
