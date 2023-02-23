NAME	=	ft_containers

OBJ_DIR =	objects/
SRC_DIR	=	./

SOURCE	=	main.cpp
OBJECT	=	$(addprefix $(OBJ_DIR),$(SOURCE:%.cpp=%.o))

HEADERS =	algorithm/equal.hpp \
			iterators/iterator_traits.hpp \
			iterators/reverse_iter.hpp \
			type_traits/type_traits.hpp \
			vector/vector.hpp \
			algorithm/lexicographical_compare.hpp \
			iterators/random_access_iter.hpp \
			stack/stack.hpp \
			utility/pair.hpp \

VECTOR_UTILS = tests/vector/utils.cpp
VECTOR1	=	tests/vector/running_tests.cpp
VECTOR2	=	tests/vector/output_tests.cpp

CC		=	c++
CFLAGS	=	-Wno-long-long -Wall -Wextra -Werror -std=c++98 -pedantic-errors

PRINT	=	$(shell which echo) -e
RM		=	rm -rf

ITALIC_LIGHTER_YELLOW	= "\e[1;33m"
BOLD_GREEN		= "\e[0;92m"
BOLD_RED		= "\e[0;91m"
RESET_COLOR		= "\e[0m"

$(OBJ_DIR)%.o:		$(SRC_DIR)/%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

all:				$(NAME)

bonus:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

vector1:
	$(CC) $(CFLAGS) $(VECTOR_UTILS) $(VECTOR1) -o vector_running_tests
	clear
	./vector_running_tests

vector2:
	@$(CC) $(CFLAGS) $(VECTOR_UTILS) $(VECTOR2) -g3 -o ftvector_output_tests
	@$(CC) $(CFLAGS) -D STD=1 $(VECTOR_UTILS) $(VECTOR2) -o stdvector_output_tests
	@./ftvector_output_tests > ftOutput.txt
	@./stdvector_output_tests > stdOutput.txt
	clear

	@diff -u ftOutput.txt stdOutput.txt > diffOutput.txt; \
	if test -s diffOutput.txt; then \
		$(PRINT) $(BOLD_RED) "Test failed\n"$(RESET_COLOR); \
		cat diffOutput.txt; \
	else \
		$(PRINT) $(BOLD_GREEN) "Test passed!"$(RESET_COLOR); \
	fi

clean:
	$(RM) ftvector_output_tests stdvector_output_tests ftOutput.txt stdOutput.txt diffOutput.txt
	$(RM) vector_running_tests
	$(RM) $(OBJ_DIR)
	$(RM) *.txt

fclean:				clean
	$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
