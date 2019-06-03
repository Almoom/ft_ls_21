# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 13:04:11 by ljalikak          #+#    #+#              #
#    Updated: 2019/04/04 13:04:14 by ljalikak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = ft_ls

make:
	@$(CC) -o $(NAME) *.c /Users/ljalikak/Documents/Libft/Libft_21/libft.a
	./ft_ls

clean:
	@rm -f /Users/ljalikak/Documents/Libft/Libft_21/*.o

fclean: clean
	@rm -f *.out

re: fclean all
