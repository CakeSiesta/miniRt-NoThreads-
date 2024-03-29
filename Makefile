CC =			gcc

FLAGS =			-Wall -Wextra -Werror

RM =			rm -rf

LIBMLX =		libmlx.dylib \
				libmlx.a

DIR_HEADERS =	./includes/

DIR_SRCS =		./srcs/

DIR_OBJS =		./

SRC =			maths/rotation.c \
				maths/vector_calculation.c \
				maths/vector_color.c \
				maths/vector_translation.c \
				maths/vector.c \
				\
				parsing/parsing_object.c \
				parsing/parsing_scene_elem.c \
				parsing/parsing.c \
				\
				raytracing/intersect/intersect.c \
				raytracing/intersect/intersect_cylinder.c \
				raytracing/intersect/intersect_plan.c \
				raytracing/intersect/intersect_sphere.c \
				raytracing/intersect/intersect_square.c \
				raytracing/intersect/intersect_triangle.c \
				raytracing/lightning/lightning.c \
				raytracing/lightning/check_light_cylinder.c \
				raytracing/lightning/check_light.c \
				raytracing/lightning/set_color.c \
				raytracing/lightning/shiny.c \
				raytracing/raytracing.c \
				raytracing/reflect.c \
				\
				scene/camera.c \
				scene/canvas.c \
				scene/handle_key.c \
				scene/image.c \
				scene/light.c \
				scene/scene_cpy.c \
				scene/scene.c \
				scene/objects/cylinder.c \
				scene/objects/lstobjects.c \
				scene/objects/plan.c \
				scene/objects/sphere.c \
				scene/objects/square.c \
				scene/objects/triangle.c \
				\
				utils/error.c \
				utils/export_bmp.c \
				utils/ft_strcmp.c \
				utils/get_next_line.c \
				utils/no_leaks.c \
				utils/utils.c \
				\
				minirt.c

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

OBJS =			$(SRCS:.c=.o)

NAME =			miniRT

all:			$(NAME)

$(NAME) :		$(OBJS)
				@make -C ./minilibx_mms
				@make -C ./minilibx_opengl
				@cp ./minilibx_mms/libmlx.dylib libmlx.dylib
				@cp ./minilibx_opengl/libmlx.a libmlx.a
				$(CC) $(FLAGS) -I $(DIR_HEADERS) $(LIBMLX) $(OBJS) -o $(NAME)

%.o: %.c
				@gcc $(FLAGS) -I $(DIR_HEADERS) -c $< -o $@
				@echo "\x1b[32;01m\033[1mCompiled "$<" successfully!"

bonus:

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				@make clean -C ./minilibx_mms
				@make clean -C ./minilibx_opengl
				$(RM) libmlx.dylib
				$(RM) libmlx.a
				$(RM) $(NAME)

re:				fclean all

