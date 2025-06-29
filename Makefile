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
	# CFLAGS += -fsanitize=address
	# LDFLAGS += -fsanitize=address
endif

SRC := \
	draw_pixels.c\
	environment.c\
	main.c\
	object_util.c\
	parse_ambient.c\
	parse.c\
	parse_camera.c\
	parse_light.c\
	parse_plane.c\
	parse_sphere.c\
	parse_util.c\
	plane.c\
	rotate.c\
	sphere.c\
	vector_arithmetic.c\
	vector_calc.c\
	vector_conversion.c\
	vector_init.c\
	vector_length.c\
	vector_product.c\
	vector_reflect_refract.c\
	vector_utility.c

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

.bonus: $(BONUS_OBJ) $(LIBFT)
	$(CC) $(BONUS_OBJ) $(LDFLAGS) -o $(MINIRT)
	touch .bonus

bonus: .bonus