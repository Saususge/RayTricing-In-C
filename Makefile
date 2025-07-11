LIB_DIR := lib
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft
BONUS_SRC_DIR := bonus_src
MLX_DIR := mlx
MLX := $(LIB_DIR)/libmlx_Linux.a
LIBFT := $(LIB_DIR)/libft.a
MINIRT := minirt

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -Istb
LDFLAGS := -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

ifdef DEBUG
	CFLAGS += -g
else
	CFLAGS += -O2
endif

SRC := \
	cylinder.c\
	cylinder_ops.c\
	cylinder_texture.c\
	cylinder_utils.c\
	environment.c\
	hit_def_0.c\
	hit_def_1.c\
	hit_def_2.c\
	hit_util.c\
	hook_key.c\
	hook_mouse.c\
	main.c\
	matrix_0.c\
	matrix_1.c\
	matrix_2.c\
	object_util.c\
	parse_ambient.c\
	parse.c\
	parse_camera.c\
	parse_cylinder.c\
	parse_light.c\
	parse_plane.c\
	parse_scene_file.c\
	parse_sphere.c\
	parse_util.c\
	plane.c\
	plane_helper.c\
	plane_texture.c\
	render.c\
	rotate.c\
	sphere_0.c\
	sphere_1.c\
	sphere_texture.c\
	transform_def.c\
	transform_helper.c\
	vec4.c\
	vec4_calc.c\
	vector_arithmetic_0.c\
	vector_arithmetic_1.c\
	vector_calc.c\
	vector_conversion.c\
	vector_init.c\
	vector_length.c\
	vector_product.c\
	vector_reflect_refract.c\
	vector_utility.c\
	viewport.c

BONUS_SRC := \
	bump_map_bonus.c\
	cone_0_bonus.c\
	cone_1_bonus.c\
	cone_texture_bonus.c\
	cone_utils_bonus.c\
	cylinder_bonus.c\
	cylinder_ops_bonus.c\
	cylinder_texture_bonus.c\
	cylinder_utils_bonus.c\
	environment_bonus.c\
	hit_def_0_bonus.c\
	hit_def_1_bonus.c\
	hit_def_2_bonus.c\
	hit_util_bonus.c\
	hook_key_bonus.c\
	hook_mouse_bonus.c\
	main_bonus.c\
	matrix_0_bonus.c\
	matrix_1_bonus.c\
	matrix_2_bonus.c\
	object_util_bonus.c\
	parse_ambient_bonus.c\
	parse_bonus.c\
	parse_camera_bonus.c\
	parse_cone_bonus.c\
	parse_cylinder_bonus.c\
	parse_light_bonus.c\
	parse_plane_bonus.c\
	parse_scene_file_bonus.c\
	parse_sphere_bonus.c\
	parse_util_bonus.c\
	plane_bonus.c\
	plane_helper_bonus.c\
	plane_texture_bonus.c\
	render_bonus.c\
	rotate_bonus.c\
	sphere_0_bonus.c\
	sphere_1_bonus.c\
	sphere_texture_bonus.c\
	texture_bonus.c\
	transform_def_bonus.c\
	transform_helper_bonus.c\
	vec4_bonus.c\
	vec4_calc_bonus.c\
	vector_arithmetic_0_bonus.c\
	vector_arithmetic_1_bonus.c\
	vector_calc_bonus.c\
	vector_conversion_bonus.c\
	vector_init_bonus.c\
	vector_length_bonus.c\
	vector_product_bonus.c\
	vector_reflect_refract_bonus.c\
	vector_utility_bonus.c\
	viewport_bonus.c

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

BONUS_OBJ := $(addprefix $(OBJ_DIR)/,$(BONUS_SRC:.c=.o))

vpath %.c $(SRC_DIR) $(BONUS_SRC_DIR)

.PHONY: all clean fclean re bonus

all: $(MINIRT)

$(MINIRT): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o:	%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(LIB_DIR):
	mkdir -p $@

$(LIBFT): | $(LIBFT_DIR) $(LIB_DIR)
	$(MAKE) -C $(LIBFT_DIR) all
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(MLX): | $(MLX_DIR) $(LIB_DIR)
	$(MAKE) -C $(MLX_DIR) all
	cp $(MLX_DIR)/libmlx_Linux.a $(MLX)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(MINIRT)
	rm -f .bonus
	rm -rf lib/
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.bonus: $(BONUS_OBJ) $(LIBFT) $(MLX)
	$(CC) $(BONUS_OBJ) $(LDFLAGS) -o $(MINIRT)
	touch .bonus

bonus: .bonus