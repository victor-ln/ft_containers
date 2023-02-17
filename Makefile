NAME	=	ft_containers

SOURCE	=	main.cpp

HEADERS =	algorithm/equal.hpp \
			iterators/iterator_traits.hpp \
			iterators/reverse_iter.hpp \
			type_traits/type_traits.hpp \
			vector/vector.hpp \
			algorithm/lexicographical_compare.hpp \
			iterators/random_access_iter.hpp \
			stack/stack.hpp \
			utility/pair.hpp \

CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors

RM		=	rm -rf

all:				$(NAME)

bonus:				$(NAME)

$(NAME):			$(HEADERS)
		$(CC) $(CFLAGS) $(SOURCE) -o $(NAME)

clean:
		$(RM) $(OBJ_DIR)

fclean:				clean
		$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
