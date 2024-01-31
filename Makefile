# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoizel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 09:38:02 by aoizel            #+#    #+#              #
#    Updated: 2024/01/31 15:08:42 by aoizel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL:		all

NAME 			=	mini_rt

LIBFTPRINTF		=	libftprintf/libftprintf.a

LIBFTPRINTF_DIR	=	libftprintf/

INCLUDES		=	-I. -I ~/minilibx-linux/ 

LINKS			=	-L$(LIBFTPRINTF_DIR) -L ~/minilibx-linux/ -lftprintf -lmlx -lXext -lX11 -lm

CFLAGS 			=	-Wall -Wextra -Werror

CC 				=	cc #$(CFLAGS)

SOURCES 		=	mini_rt.c utils.c utils2.c utils3.c utils4.c init.c mlx_utils.c \
					mini_rt2.c intersections.c intersections2.c\
					parse.c parse_utils.c parse_items.c error_check.c \
					error_check_utils.c error_check_utils2.c error_check_items.c \
					error_check_items2.c parse_items2.c

OBJECTS_DIR		=	.objs/

OBJECTS 		=	$(addprefix $(OBJECTS_DIR),$(SOURCES:.c=.o))

DEPENDENCIES	=	Makefile

MAKE			=	@make --no-print-directory


all:		libft $(OBJECTS_DIR) 
				$(MAKE) $(NAME)

$(NAME):	$(OBJECTS) | $(OBJECTS_DIR) $(LIBFTPRINTF)
				$(CC) $(OBJECTS) $(LINKS) $(INCLUDES) -o $(NAME)

$(OBJECTS_DIR):
				mkdir -p .objs

libft:
				$(MAKE) -C $(LIBFTPRINTF_DIR)

$(OBJECTS_DIR)%.o: %.c $(DEPENDENCIES)  $(LIBFTPRINTF)
				$(CC) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIR)%.d: %.c | $(OBJECTS_DIR)
	$(CC) $< -MT $(OBJECTS_DIR)$(<:.c=.o) -MM -MP -MF $@

clean:
				$(MAKE) clean -C $(LIBFTPRINTF_DIR)
				rm -rf $(OBJECTS_DIR)

fclean:		clean
				$(MAKE) fclean -C $(LIBFTPRINTF_DIR)
				rm -rf $(NAME)

re:			fclean 
				make all

.PHONY: 	all clean fclean re libft

-include $(OBJECTS:.o=.d)
