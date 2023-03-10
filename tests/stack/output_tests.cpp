/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/containers/stack_tests.hpp"

template <typename Container>
static void relationalOperatorsTest(void);

template <typename Container>
static void assignmentOperatorTest(void);

template <typename Container>
static void constructorsTest(void);

const int     g_array_size = AMOUNT;
const int     *g_array = createArray(g_array_size);

int main(void) {
    {
        relationalOperatorsTest<ft::vector<int> >();
        relationalOperatorsTest<std::deque<int> >();
        relationalOperatorsTest<std::list<int> >();
    }
    {
        assignmentOperatorTest<ft::vector<int> >();
        assignmentOperatorTest<std::deque<int> >();
        assignmentOperatorTest<std::list<int> >();
    }
    {
        constructorsTest<ft::vector<int> >();
        constructorsTest<std::deque<int> >();
        constructorsTest<std::list<int> >();
    }
    return 0;
}

template <typename Container>
static void constructorsTest(void) {
    Container            filledContainer(10, 100);
    Container            rangedContainer(g_array, g_array + g_array_size);
    Container            emptyContainer;

    std::cout << "\n[ CONSTRUCTORS ]\n";
    printTime(0);
    {
        std::cout << "\n\nEmpty vector\n";
        ft::stack<int, Container>             stack_(emptyContainer);

        printStack(stack_);
    }
    {
        std::cout << "\n\nvector (1/2)\n";
        ft::stack<int, Container>             stack_(filledContainer);

        printStack(stack_);
    }
    {
        std::cout << "\n\nvector (1/2)\n";
        ft::stack<int, Container>             stack_(rangedContainer);

        printStack(stack_);
    }
    {
        std::cout << "\n\nCopy constructor (1/2)\n";
        const ft::stack<int, Container>           stack1(filledContainer);
        ft::stack<int, Container>                 stack2(stack1);

        printStack(stack2);
    }
    {
        std::cout << "\n\nCopy constructor (2/2)\n";
        const ft::stack<int, Container>           stack1(rangedContainer);
        ft::stack<int, Container>                 stack2(stack1);

        printStack(stack2);
    }
    {
        std::cout << "\n\nCopy constructor with empty stack\n";
        ft::stack<int, Container>             stack1(emptyContainer);
        ft::stack<int, Container>             stack2(stack1);

        printStack(stack1);
        printStack(stack2);
    }
    printTime(1);
}

template <typename Container>
static void relationalOperatorsTest(void) {
    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    printTime(0);
    Container                   c(g_array, g_array + g_array_size);
    ft::stack<int, Container>   stack1(c);
    ft::stack<int, Container>   stack2(c);

    std::cout << "\n\noperator ==\n";
    std::cout << "is equal: " << (stack1 == stack2);

    std::cout << "\n\noperator !=\n";
    stack1.pop();
    std::cout << "is not equal: " << (stack1 != stack2);

    std::cout << "\n\noperator <\n";
    std::cout << "is less than: " << (stack1 < stack2);

    std::cout << "\n\noperator <=\n";
    std::cout << "is less than and not equal: "
            << (stack1 <= stack2 && stack1 != stack2);
    stack1.push(1);
    std::cout << "is less than and equal: "
            << (stack1 <= stack2 && stack1 == stack2);

    std::cout << "\n\noperator >\n";
    stack1.push(100);
    std::cout << "is greater than : " << (stack1 > stack2);

    std::cout << "\n\noperator >=\n";
    std::cout << "is greater than and not equal: "
            << (stack1 >= stack2 && stack1 != stack2);
    stack1.pop();
    std::cout << "is greater than and equal: "
            << (stack1 >= stack2 && stack1 == stack2);
    std::cout << '\n';
    printTime(1);
}

template <typename Container>
static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    printTime(0);
    Container v;
    {
        ft::stack<int, Container> stack1(v);
        {
            ft::stack<int, Container> stack2(Container(10, 100));
            stack1 = stack2;
        }
    }
    {
        ft::stack<int, Container> stack1(v);
        ft::stack<int, Container> stack2(Container(15, 200));

        stack1 = stack2;
        printStack(stack1);
        printStack(stack2);
        ft::stack<int, Container> stack3(Container(20, 500));
        stack1 = stack3;
        printStack(stack1);
        printStack(stack3);
    }
    printTime(1);
}
