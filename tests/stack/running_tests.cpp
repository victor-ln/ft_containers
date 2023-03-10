/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/containers/stack_tests.hpp"

template <typename Container>
static void pushBackTest(void);

template <typename Container>
static void popBackTest(void);

template <typename Container>
static void sizeTest(void);

int main(void) {
    pushBackTest<ft::vector<int> >();
    pushBackTest<std::list<int> >();
    pushBackTest<std::deque<int> >();
    popBackTest<ft::vector<int> >();
    popBackTest<std::list<int> >();
    popBackTest<std::deque<int> >();
    sizeTest<ft::vector<int> >();
    sizeTest<std::list<int> >();
    sizeTest<std::deque<int> >();
    printStatus(RESULT);
    return 0;
}

template <typename Container>
static void pushBackTest(void) {
    printColor(CYAN, "\n[ PUSH_BACK ]\n");
    {
        printColor(BGWHITE, "\n├─ push (non-empty stack)\n");
        Container                   c(10, 100);
        ft::stack<int, Container>   ftStack(c);
        std::stack<int, Container>  stdStack(c);
        ftStack.push(42);
        stdStack.push(42);

        printStatus(ftStack.empty() == stdStack.empty());
        printStatus(ftStack.size() == stdStack.size());
        printStatus(ftStack.top() == stdStack.top());
    }
    {
        printColor(BGWHITE, "\n├─ push (empty stack)\n");
        ft::stack<int, Container>             ftStack;
        std::stack<int, Container>            stdStack;
        ftStack.push(42);
        stdStack.push(42);

        printStatus(ftStack.empty() == stdStack.empty());
        printStatus(ftStack.size() == stdStack.size());
        printStatus(ftStack.top() == stdStack.top());
    }
}

template <typename Container>
static void popBackTest(void) {
    printColor(CYAN, "\n[ POP_BACK ]\n");
    {
        printColor(BGWHITE, "\n├─ pop\n");
        int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        Container                           range1(a, a + 9);
        Container                           range2(a, a + 9);
        ft::stack<int, Container>           ftStack(range1);
        std::stack<int, Container>          stdStack(range2);

        ftStack.pop();
        stdStack.pop();

        printStatus(ftStack.empty() == stdStack.empty());
        printStatus(ftStack.size() == stdStack.size());
        printStatus(ftStack.top() == stdStack.top());

        bool    equal;

        do {
            equal = ftStack.top() == stdStack.top();
            ftStack.pop();
            stdStack.pop();
        } while (!ftStack.empty() && !stdStack.empty() && equal);

        printStatus(equal);
        printStatus(ftStack.empty() == stdStack.empty());
        printStatus(ftStack.size() == stdStack.size());
    }
}

template <typename Container>
static void sizeTest(void) {
    printColor(CYAN, "\n[ SIZE ]\n");
    {
        printColor(BGWHITE, "\n├─ size (non-empty stack)\n");
        Container                  c(10);
        ft::stack<int, Container>             ftStack(c);
        std::stack<int, Container>            stdStack(c);

        printStatus(ftStack.size() == ftStack.size());
        printStatus(ftStack.empty() == ftStack.empty());
        c = Container(10, 10);
        printStatus(ftStack.size() == ftStack.size());
        printStatus(ftStack.empty() == ftStack.empty());
    }
    {
        printColor(BGWHITE, "\n├─ size (empty stack)\n");
        ft::stack<int, Container>             ftStack;
        std::stack<int, Container>            stdStack;

        printStatus(ftStack.size() == stdStack.size());
        printStatus(ftStack.empty() == ftStack.empty());
    }
}
