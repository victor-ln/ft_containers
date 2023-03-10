NAME	=	executables

LOGS_DIR		=	logs
EXECUTABLES_DIR =	executables

VECTOR_OUTPUT_EXECUTABLES	=	ftvector_output_tests stdvector_output_tests
SET_OUTPUT_EXECUTABLES		=	ftset_output_tests stdset_output_tests
MAP_OUTPUT_EXECUTABLES		=	ftmap_output_tests stdmap_output_tests
STACK_OUTPUT_EXECUTABLES	=	ftstack_output_tests stdstack_output_tests

VECTOR_TIME_EXECUTABLES		=	ftvector_time_tests stdvector_time_tests
SET_TIME_EXECUTABLES		=	ftset_time_tests stdset_time_tests
MAP_TIME_EXECUTABLES		=	ftmap_time_tests stdmap_time_tests
STACK_TIME_EXECUTABLES		=	ftstack_time_tests stdstack_time_tests

UTILS	=	tests/utils/utils.cpp

VECTOR1	=	tests/vector/running_tests.cpp
VECTOR2	=	tests/vector/output_tests.cpp

MAP1	=	tests/map/running_tests.cpp
MAP2	=	tests/map/output_tests.cpp

SET1	=	tests/set/running_tests.cpp
SET2	=	tests/set/output_tests.cpp

STACK1	=	tests/stack/running_tests.cpp
STACK2	=	tests/stack/output_tests.cpp

CC		=	c++
CFLAGS	=	-Wno-long-long -Wall -Wextra -Werror -std=c++98 -pedantic-errors -fsanitize=address

PRINT	=	$(shell which echo) -e
RM		=	rm -rf

ITALIC_LIGHTER_YELLOW	= "\e[1;33m"
BOLD_GREEN		= "\e[0;92m"
BOLD_RED		= "\e[0;91m"
CYAN_COLOR		= "\e[0;96m"
RESET_COLOR		= "\e[0m"

define time_test
	@./$(1) | grep -E 'TIME|-/-----' -A 1 -B 1 > ftTime.txt
	@./$(2) | grep -E 'TIME|-/-----' -A 1 -B 1 > stdTime.txt

	@$(PRINT) "\n------------ FT  TIME ------------ | ------------ STD TIME ------------\n"
	@pr -m -t ftTime.txt stdTime.txt
	@mkdir -p logs
	@mkdir -p logs/$(3)/
	@mv ftTime.txt stdTime.txt logs/$(3)/
endef

define compare_outputs
	@./$(1) > ftOutput.txt
	@./$(2) > stdOutput.txt

	@diff -u ftOutput.txt stdOutput.txt > diffOutput.txt; \
	if test -s diffOutput.txt; then \
		$(PRINT) $(BOLD_RED) "Test failed\n"$(RESET_COLOR); \
		cat diffOutput.txt; \
	else \
		$(PRINT) $(BOLD_GREEN) "Test passed!"$(RESET_COLOR); \
	fi
	@mkdir -p logs
	@mkdir -p logs/$(3)/
	@mv ftOutput.txt stdOutput.txt diffOutput.txt logs/$(3)/
endef

$(NAME): containers

all:	containers

containers:	vector1 vector2 vector3 map1 map2 map3 set1 set2 set3 stack1 stack2 stack3 
	@$(PRINT) $(CYAN_COLOR) "\n Results available in log directory\n" $(RESET_COLOR)

time:
	@if [ -n "$(target)" ]; then \
		$(PRINT) "\n------------ FT  TIME ------------ | ------------ STD TIME ------------\n"; \
		pr -m -t logs/$(target)/ftTime.txt logs/$(target)/stdTime.txt; \
	else \
		echo "Usage: make time target=<container_name>"; \
	fi

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@$(CC) $(CFLAGS) -D STD=1 $(OBJECTS) -o $(NAME)std

vector1:
	@$(CC) $(CFLAGS) $(UTILS) $(VECTOR1) -o vector_running_tests
	@./vector_running_tests
	@mkdir -p $(EXECUTABLES_DIR)/vector
	@mv vector_running_tests $(EXECUTABLES_DIR)/vector

vector2:
	@$(PRINT) $(CYAN_COLOR) "\n OUTPUT TESTS\n" $(RESET_COLOR)
	@@$(CC) $(CFLAGS) $(UTILS) $(VECTOR2) -o ftvector_output_tests
	@@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(VECTOR2) -o stdvector_output_tests
	$(call compare_outputs,ftvector_output_tests,stdvector_output_tests,vector)
	@mkdir -p $(EXECUTABLES_DIR)/vector
	@mv $(VECTOR_OUTPUT_EXECUTABLES) $(EXECUTABLES_DIR)/vector

vector3:
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 $(UTILS) $(VECTOR2) -o ftvector_time_tests
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 -D STD=1 $(UTILS) $(VECTOR2) -o stdvector_time_tests
	$(call time_test,ftvector_time_tests,stdvector_time_tests,vector)
	@mkdir -p $(EXECUTABLES_DIR)/vector
	@mv $(VECTOR_TIME_EXECUTABLES) $(EXECUTABLES_DIR)/vector

map1:
	@$(CC) $(CFLAGS) $(UTILS) $(MAP1) -o map_running_tests
	@./map_running_tests
	@mkdir -p $(EXECUTABLES_DIR)/map
	@mv map_running_tests $(EXECUTABLES_DIR)/map

map2:
	@$(PRINT) $(CYAN_COLOR) "\n OUTPUT TESTS\n" $(RESET_COLOR)
	@@$(CC) $(CFLAGS) $(UTILS) $(MAP2) -o ftmap_output_tests
	@@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(MAP2) -o stdmap_output_tests
	$(call compare_outputs,ftmap_output_tests,stdmap_output_tests,map)
	@mkdir -p $(EXECUTABLES_DIR)/map
	@mv $(MAP_OUTPUT_EXECUTABLES) $(EXECUTABLES_DIR)/map

map3:
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 $(UTILS) $(MAP2) -o ftmap_time_tests
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 -D STD=1 $(UTILS) $(MAP2) -o stdmap_time_tests
	$(call time_test,ftmap_time_tests,stdmap_time_tests,map)
	@mkdir -p $(EXECUTABLES_DIR)/map
	@mv $(MAP_TIME_EXECUTABLES) $(EXECUTABLES_DIR)/map

set1:
	@$(CC) $(CFLAGS) $(UTILS) $(SET1) -o set_running_tests
	@./set_running_tests
	@mkdir -p $(EXECUTABLES_DIR)/set
	@mv set_running_tests $(EXECUTABLES_DIR)/set

set2:
	@$(PRINT) $(CYAN_COLOR) "\n OUTPUT TESTS\n" $(RESET_COLOR)
	@@$(CC) $(CFLAGS) $(UTILS) $(SET2) -o ftset_output_tests
	@@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(SET2) -o stdset_output_tests
	$(call compare_outputs,ftset_output_tests,stdset_output_tests,set)
	@mkdir -p $(EXECUTABLES_DIR)/set
	@mv $(SET_OUTPUT_EXECUTABLES) $(EXECUTABLES_DIR)/set

set3:
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 $(UTILS) $(SET2) -o ftset_time_tests
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 -D STD=1 $(UTILS) $(SET2) -o stdset_time_tests
	$(call time_test,ftset_time_tests,stdset_time_tests,set)
	@mkdir -p $(EXECUTABLES_DIR)/set
	@mv $(SET_TIME_EXECUTABLES) $(EXECUTABLES_DIR)/set

stack1:
	@$(CC) $(CFLAGS) $(UTILS) $(STACK1) -o stack_running_tests
	@./stack_running_tests
	@mkdir -p $(EXECUTABLES_DIR)/stack
	@mv stack_running_tests $(EXECUTABLES_DIR)/stack

stack2:
	@$(PRINT) $(CYAN_COLOR) "\n OUTPUT TESTS\n" $(RESET_COLOR)
	@@$(CC) $(CFLAGS) $(UTILS) $(STACK2) -o ftstack_output_tests
	@@$(CC) $(CFLAGS) -D STD=1 $(UTILS) $(STACK2) -o stdstack_output_tests
	$(call compare_outputs,ftstack_output_tests,stdstack_output_tests,stack)
	@mkdir -p $(EXECUTABLES_DIR)/stack
	@mv $(STACK_OUTPUT_EXECUTABLES) $(EXECUTABLES_DIR)/stack

stack3:
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 $(UTILS) $(STACK2) -o ftstack_time_tests
	@@$(CC) $(CFLAGS) -D TIME_TEST=1 -D STD=1 $(UTILS) $(STACK2) -o stdstack_time_tests
	$(call time_test,ftstack_time_tests,stdstack_time_tests,stack)
	@mkdir -p $(EXECUTABLES_DIR)/stack
	@mv $(STACK_TIME_EXECUTABLES) $(EXECUTABLES_DIR)/stack

clean:
	$(RM) $(EXECUTABLES_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) logs

fclean:				clean
	$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
