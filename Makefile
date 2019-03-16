#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/30 21:52:55 by vmazurok          #+#    #+#              #
#    Updated: 2018/03/30 21:52:58 by vmazurok         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC		=	gcc
CFLAGS	=	-O3 -Wall -Wextra -Werror
GFX		=	-F frameworks -framework SDL2
NAME	=	Wolf3D
SRC		=	get_next_line.c \
			main.c \
			map_parcing.c \
			error_hendler.c \
			draw_func.c \
			additional_functions.c
			
BINS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	cd libft ; make ; cd ..
	$(CC) $(CFLAGS) -o $(NAME) $(BINS) $(GFX) libft/libft.a

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	cd libft ; make clean ; cd ..
	rm -f $(BINS)

fclean: clean
	cd libft ; make fclean ; cd ..
	rm -f $(NAME)

re: fclean all