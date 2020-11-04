SRCS =				srcs/maths/rotation.c \
				srcs/maths/vector_calculation.c \
				srcs/maths/vector_color.c \
				srcs/maths/vector_translation.c \
				srcs/maths/vector.c \
				\
				srcs/parsing/parsing_object.c \
				srcs/parsing/parsing_scene_elem.c \
				srcs/parsing/parsing.c \
				\
				srcs/raytracing/intersect/intersect.c \
				srcs/raytracing/intersect/intersect_cylinder.c \
				srcs/raytracing/intersect/intersect_plan.c \
				srcs/raytracing/intersect/intersect_sphere.c \
				srcs/raytracing/intersect/intersect_square.c \
				srcs/raytracing/intersect/intersect_triangle.c \
				srcs/raytracing/lightning/lightning.c \
				srcs/raytracing/lightning/check_light_cylinder.c \
				srcs/raytracing/lightning/check_light.c \
				srcs/raytracing/lightning/set_color.c \
				srcs/raytracing/lightning/shiny.c \
				srcs/raytracing/raytracing.c \
				srcs/raytracing/reflect.c \
				\
				srcs/scene/camera.c \
				srcs/scene/canvas.c \
				srcs/scene/handle_key.c \
				srcs/scene/image.c \
				srcs/scene/light.c \
				srcs/scene/scene_cpy.c \
				srcs/scene/scene.c \
				srcs/scene/objects/cylinder.c \
				srcs/scene/objects/lstobjects.c \
				srcs/scene/objects/plan.c \
				srcs/scene/objects/sphere.c \
				srcs/scene/objects/square.c \
				srcs/scene/objects/triangle.c \
				\
				srcs/utils/error.c \
				srcs/utils/export_bmp.c \
				srcs/utils/ft_strcmp.c \
				srcs/utils/get_next_line.c \
				srcs/utils/no_leaks.c \
				srcs/utils/utils.c \
				\
				srcs/minirt.c

NAME = miniRT

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -DLINUX

COMMAND		= clang

RM		= /bin/rm -f


LIB		= ./minilibx-linux/libmlx.a


INCLUDE		= -L./includes/ minilibx-linux/libmlx.a -lXext -lX11 -lm -lbsd

MLX		= ./minilibx-linux


all: ${NAME}

${NAME}:	minilibx ${OBJS}
		${COMMAND} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} ${LIB}

.c.o:
		$(COMMAND) -w $(CFLAGS) ${INCLUDE} -I ./includes/ -c $< -o ${<:.c=.o} ${LIB}

minilibx:
		$(MAKE) -C ./minilibx-linux

bonus:		CFLAGS += -DBONUS
bonus:		${NAME}

clean:
		$(MAKE) -C ./minilibx-linux/. clean
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}
		${RM} ./minilibx-linux/libmlx.a

re:		fclean all

.PHONY: all clean fclean re
