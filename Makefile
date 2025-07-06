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
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS := -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

ifdef DEBUG
	CFLAGS += -g
else
	CFLAGS += -O2
endif

SRC := \
	texture.c\
	environment.c\
	hit_def.c\
	hit_util.c\
	main.c\
	matrix_0.c\
	matrix_1.c\
	object_util.c\
	parse_ambient.c\
	parse.c\
	parse_camera.c\
	parse_light.c\
	parse_scene_file.c\
	parse_sphere.c\
	parse_plane.c\
	parse_util.c\
	plane_checkerboard.c\
	plane_ops.c\
	plane.c\
	render.c\
	rotate.c\
	sphere_0.c\
	sphere_1.c\
	sphere_checkerboard.c\
	vector_arithmetic_0.c\
	vector_arithmetic_1.c\
	vector_calc.c\
	vector_conversion.c\
	vector_init.c\
	vector_length.c\
	vector_product.c\
	vector_reflect_refract.c\
	vector_utility.c\
	vec4.c\
	viewport.c

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