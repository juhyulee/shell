# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 15:18:02 by juhyulee          #+#    #+#              #
#    Updated: 2023/02/24 19:46:17 by siwolee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = -I../header

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c\
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
get_next_line_utils.c get_next_line.c ft_printf.c print_dec.c print_int.c print_ptr.c \
print_str.c print_un_dec.c printchar.c printhex_low.c \
printhex_upp.c printmodule.c\

SRCS_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

CC = cc
CFLAGS = -c -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

ifdef BONUS
	OBJS_ALL = $(OBJS) $(OBJS_B)
else
	OBJS_ALL = $(OBJS)
endif

all : 		$(NAME)

bonus :
	make BONUS=1 all

$(NAME) : 	$(OBJS_ALL)
			@$(AR) $(NAME) $(OBJS_ALL)

.c.o :
			@$(CC) $(CFLAGS) $(HEADER) $< -o $@ -I libft.h

clean :
			@$(RM) $(OBJS) $(OBJS_B)

fclean :	clean
			@$(RM) $(NAME)

re :		fclean all

.PHONY : all clean fclean re bonus
