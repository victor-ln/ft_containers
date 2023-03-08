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

UTILS = tests/utils/utils.cpp

VECTOR1	=	tests/vector/running_tests.cpp
VECTOR2	=	tests/vector/output_tests.cpp

VECTOR_EXECUTABLES	=	vector_running_tests ftvector_output_tests stdvector_output_tests
MAP_EXECUTABLES		=	set_running_tests ftset_output_tests stdset_output_tests
SET_EXECUTABLES		=	map_running_tests ftmap_output_tests stdmap_output_tests
STACK_EXECUTABLES	=	stack_running_tests ftstack_output_tests stdstack_output_tests

MAP1	=	tests/map/running_tests.cpp
MAP2	=	tests/map/output_tests.cpp

SET1	=	tests/set/running_tests.cpp
SET2	=	tests/set/output_tests.cpp

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
	$(CC) $(CFLAGS) $(UTILS) $(VECTOR1) -o vector_running_tests
	clear
	./vector_running_tests

vector2:
	@$(CC) $(CFLAGS) $(UTILS) $(VECTOR2) -o ftvector_output_tests
	@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(VECTOR2) -o stdvector_output_tests
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
	@mkdir -p logs
	@mkdir -p logs/vector/
	@mv ftOutput.txt stdOutput.txt diffOutput.txt logs/vector/

map1:
	$(CC) $(CFLAGS) $(UTILS) $(MAP1) -o map_running_tests
	clear
	./map_running_tests

map2:
	@$(CC) $(CFLAGS) $(UTILS) $(MAP2) -o ftmap_output_tests
	@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(MAP2) -o stdmap_output_tests
	@./ftmap_output_tests > ftOutput.txt
	@./stdmap_output_tests > stdOutput.txt
	clear

	@diff -u ftOutput.txt stdOutput.txt > diffOutput.txt; \
	if test -s diffOutput.txt; then \
		$(PRINT) $(BOLD_RED) "Test failed\n"$(RESET_COLOR); \
		cat diffOutput.txt; \
	else \
		$(PRINT) $(BOLD_GREEN) "Test passed!"$(RESET_COLOR); \
	fi
	@mkdir -p logs
	@mkdir -p logs/map/
	@mv ftOutput.txt stdOutput.txt diffOutput.txt logs/map/

set1:
	$(CC) $(CFLAGS) $(UTILS) $(SET1) -o set_running_tests
	clear
	./set_running_tests

set2:
	@$(CC) $(CFLAGS) $(UTILS) $(SET2) -o ftset_output_tests
	@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(SET2) -o stdset_output_tests
	@./ftset_output_tests > ftOutput.txt
	@./stdset_output_tests > stdOutput.txt
	clear

	@diff -u ftOutput.txt stdOutput.txt > diffOutput.txt; \
	if test -s diffOutput.txt; then \
		$(PRINT) $(BOLD_RED) "Test failed\n"$(RESET_COLOR); \
		cat diffOutput.txt; \
	else \
		$(PRINT) $(BOLD_GREEN) "Test passed!"$(RESET_COLOR); \
	fi
	@mkdir -p logs
	@mkdir -p logs/set/
	@mv ftOutput.txt stdOutput.txt diffOutput.txt logs/set/

stack1:
	$(CC) $(CFLAGS) $(UTILS) $(STACK1) -o stack_running_tests
	clear
	./stack_running_tests

stack2:
	@$(CC) $(CFLAGS) $(UTILS) $(STACK2) -o ftstack_output_tests
	@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(STACK2) -o stdstack_output_tests
	@./ftstack_output_tests > ftOutput.txt
	@./stdstack_output_tests > stdOutput.txt
	clear

	@diff -u ftOutput.txt stdOutput.txt > diffOutput.txt; \
	if test -s diffOutput.txt; then \
		$(PRINT) $(BOLD_RED) "Test failed\n"$(RESET_COLOR); \
		cat diffOutput.txt; \
	else \
		$(PRINT) $(BOLD_GREEN) "Test passed!"$(RESET_COLOR); \
	fi
	@mkdir -p logs
	@mkdir -p logs/stack/
	@mv ftOutput.txt stdOutput.txt diffOutput.txt logs/stack/

clean:
	$(RM) $(VECTOR_EXECUTABLES)
	$(RM) $(MAP_EXECUTABLES)
	$(RM) $(SET_EXECUTABLES)
	$(RM) $(STACK_EXECUTABLES)
	$(RM) $(OBJ_DIR)
	$(RM) logs

fclean:				clean
	$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
