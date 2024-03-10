# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 11:12:26 by mchenava          #+#    #+#              #
#    Updated: 2024/03/10 21:50:10 by agaley           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME= miniRT

BUILD_DIR= build
SRC_DIR= RayTracer
INC_DIR= $(SRC_DIR)/includes
MLX_DIR= ./minilibx-linux
GL_DIR= ./42LiteGL

FT_DIR= $(SRC_DIR)/ft
WIN_DIR= $(SRC_DIR)/window
UTILS_DIR= $(SRC_DIR)/utils
CAM_DIR= $(SRC_DIR)/camera
RENDER_DIR= $(SRC_DIR)/rendering
CONTROLS_DIR= $(SRC_DIR)/controls
SCENE_DIR= $(SRC_DIR)/scene
SHADER_DIR= $(SRC_DIR)/shader
SHAPES_DIR= $(SRC_DIR)/shapes
READLINE_DIR = $(SRC_DIR)/readline
PARSING_DIR= $(SRC_DIR)/parsing

MLX= $(MLX_DIR)/libmlx.a
GL= $(GL_DIR)/lite_gl.a

S_DIRS = $(FT_DIR) $(WIN_DIR) $(UTILS_DIR) $(CAM_DIR) $(RENDER_DIR) $(CONTROLS_DIR) $(SCENE_DIR) $(SHADER_DIR) $(SHAPES_DIR) $(READLINE_DIR) $(PARSING_DIR)
LIBS = -lX11 -lXext -lm

B_DIRS = $(S_DIRS:$(SRC_DIR)/%=$(BUILD_DIR)/%)

FT_SRC=		$(FT_DIR)/ft_atof.c \
			$(FT_DIR)/ft_atoi.c \
			$(FT_DIR)/ft_split.c \
			$(FT_DIR)/ft_strlen.c \
			$(FT_DIR)/ft_strmanip.c

WIN_SRC=	$(WIN_DIR)/init_window.c \
			$(WIN_DIR)/hooks.c \
			$(WIN_DIR)/init_glx.c

UTILS_SRC=	$(UTILS_DIR)/clean.c \
			$(UTILS_DIR)/init_rt.c \
			$(UTILS_DIR)/vec_to_array.c \
			$(UTILS_DIR)/error.c

CAM_SRC=	$(CAM_DIR)/init_cam.c \
			$(CAM_DIR)/move_cam.c

RENDER_SRC= $(RENDER_DIR)/render.c \
			$(RENDER_DIR)/projection.c

CONTROLS_SRC= 	$(CONTROLS_DIR)/keyboard_ctrl.c \
				$(CONTROLS_DIR)/mouse_ctrl.c \
				$(CONTROLS_DIR)/modes.c

SCENE_SRC=	$(SCENE_DIR)/scene.c

SHADER_SRC=	$(SHADER_DIR)/loadshader.c \
			$(SHADER_DIR)/raytracing.c \
			$(SHADER_DIR)/rt_lighting.c \
			$(SHADER_DIR)/intersect.c \
			$(SHADER_DIR)/intersect_planes.c \
			$(SHADER_DIR)/intersect_spheres.c \
			$(SHADER_DIR)/intersect_cylinders.c \
			$(SHADER_DIR)/intersect_cones.c \
			$(SHADER_DIR)/scattering.c \
			$(SHADER_DIR)/utils.c \
			$(SHADER_DIR)/color_utils.c \
			$(SHADER_DIR)/base_shaders.c

SHAPES_SRC = 	$(SHAPES_DIR)/plane.c \
			$(SHAPES_DIR)/mesh.c \
			$(SHAPES_DIR)/sphere.c \
			$(SHAPES_DIR)/cylinder.c \
			$(SHAPES_DIR)/cone.c \
			$(SHAPES_DIR)/shapes_tools.c \
			$(SHAPES_DIR)/new_shape.c

READLINE_SRC = $(READLINE_DIR)/get_next_line.c \
				$(READLINE_DIR)/get_next_line_utils.c

PARSING_SRC = $(PARSING_DIR)/parser.c \
			$(PARSING_DIR)/shapes.c \
			$(PARSING_DIR)/utils.c \
			$(PARSING_DIR)/utils_2.c

SRC= $(SRC_DIR)/minirt.c
SRC+= $(FT_SRC) $(WIN_SRC) $(UTILS_SRC) $(CAM_SRC) $(RENDER_SRC) $(CONTROLS_SRC) $(SCENE_SRC) $(SHADER_SRC) $(SHAPES_SRC) $(READLINE_SRC) $(PARSING_SRC)

OBJECTS= $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS= $(OBJECTS:.o=.d)

FLAGS= -std=c99 -Wall -Wextra -Werror -MMD -g3 ${LIBS} -fsanitize=address
OBJ_FLAGS=  -I$(SRC_DIR) -I$(GL_DIR) -I$(MLX_DIR) -Wall -Wextra -Werror -MMD -g3 -fsanitize=address

all: $(NAME)

$(NAME): dirs compile

help :
	@echo $(SRC)
	@echo $(OBJECTS)
	@echo $(DEPS)

compile: $(OBJECTS) $(MLX) $(GL)
	@echo "Compiling $(NAME)"
	@ $(CC) $^ $(FLAGS) -o $(NAME)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "Compiling $@"
	$(CC) $(OBJ_FLAGS) -c $< -o $@
	@echo "Including dependencies for $@"
	-@$(CC) $(OBJ_FLAGS) -MM $< -MT $@ -MF $(@:.o=.d)

-include $(DEPS)

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
	$(RM) $(OBJECTS) $(DEPS)
	$(RM) -r $(BUILD_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(GL_DIR) clean

fclean : clean
	$(RM) $(NAME)
	$(MAKE) -C $(GL_DIR) fclean

re : fclean all
