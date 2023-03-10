/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/set_tests.hpp"

static void relationalOperatorsTest(void);
static void assignmentOperatorTest(void);
static void constructorsTest(void);
static void operationsTest(void);
static void insertTest(void);
static void eraseTest(void);
static void swapTest(void);

int main(void) {
    relationalOperatorsTest();
    assignmentOperatorTest();
    constructorsTest();
    operationsTest();
    insertTest();
    eraseTest();
    swapTest();
    return 0;
}

static void constructorsTest(void) {
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "\n[ CONSTRUCTORS ]\n";
    {
        std::cout << "\n\nEmpty set\n";
        ft::set<int>             s;

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\nRange constructor (pointer)\n";
        ft::set<int>             s(array, array + 9);

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\nRange constructor (iterator)\n";
        const std::set<int>      to_copy_from(array, array + 9);
        ft::set<int>             s(to_copy_from.begin(), to_copy_from.end());

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\nRange constructor with empty range\n";
        int array[] = {0};
        ft::set<int>             s(array, array);

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\nCopy constructor\n";
        const ft::set<int>           s1(array, array + 9);
        ft::set<int>                 s2(s1);

        printContainer(s1, print<int>);
        printContainer(s2, print<int>);
    }
    {
        std::cout << "\n\nCopy constructor with empty set\n";
        ft::set<int>             s1;
        ft::set<int>             s2(s1);

        printContainer(s1, print<int>);
        printContainer(s2, print<int>);
    }
}

static void swapTest(void) {
    std::cout << "\n[ SWAP ]\n\n";
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ft::set<int> s1(array, array + 5);
    ft::set<int> s2(array + 5, array + 10);

    s1.swap(s2);
    printContainer(s1, print<int>);
    printContainer(s2, print<int>);

    swap(s1, s2);
    printContainer(s1, print<int>);
    printContainer(s2, print<int>);
}

static void relationalOperatorsTest(void) {
    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    ft::set<int>             s1(array, array + 9);
    ft::set<int>             s2(array, array + 9);

    std::cout << "\n\noperator ==\n";
    std::cout << "is equal: " << (s1 == s2);

    std::cout << "\n\noperator !=\n";
    s1.erase(--s1.end());
    std::cout << "is not equal: " << (s1 != s2);

    std::cout << "\n\noperator <\n";
    std::cout << "is less than: " << (s1 < s2);

    std::cout << "\n\noperator <=\n";
    std::cout << "is less than and not equal: " << (s1 <= s2 && s1 != s2);
    s1.insert(9);
    std::cout << "is less than and equal: " << (s1 <= s2 && s1 == s2);

    std::cout << "\n\noperator >\n";
    s1.insert(100);
    std::cout << "is greater than : " << (s1 > s2);

    std::cout << "\n\noperator >=\n";
    std::cout << "is greater than and not equal: " << (s1 >= s2 && s1 != s2);
    s1.erase(--s1.end());
    std::cout << "is greater than and equal: " << (s1 >= s2 && s1 == s2);
}

static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    int array[30];

    srand(30);
    for (int i = 0; i < 30; i++) { array[i] = rand(); }
    {
        /* Deep copying */
        ft::set<int> s1;
        {
            ft::set<int> s2(array, array + 10);
            s1 = s2;
        }
    }
    {
        ft::set<int> s1;
        ft::set<int> s2(array, array + 20);

        s1 = s2;
        printContainer(s1, print<int>);
        printContainer(s2, print<int>);
        ft::set<int> v3(array, array + 30);
        s1 = v3;
        printContainer(s1, print<int>);
        printContainer(v3, print<int>);
    }
}

static void operationsTest(void) {
    ft::set<std::string>           s;
    std::string                     str("a");

    for (int i = 0; i < 100; i++) {
        s.insert(str);
        str[0]++;
    }

    const ft::set<std::string>     constS(s);

    ft::set<std::string>::iterator it;
    {
        std::cout << "\n[ FIND ]\n";

        it = s.find("b");

        if (it != constS.end()) {
            std::cout << "Found value: " << *it << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        it = s.find("c");

        if (it != constS.end()) {
            std::cout << "Found value: " << *it << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        it = s.find("h");
        std::cout << (it == s.end()) << '\n';
    }
    {
        std::cout << "\n[ FIND (const) ]\n";

        if (constS.find("b") != constS.end()) {
            std::cout << "Found key: " << *constS.find("b") << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        if (constS.find("c") != constS.end()) {
            std::cout << "Key: " << *constS.find("c") << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        std::cout << (constS.find("h") == constS.end()) << '\n';
    }
    {
        std::cout << "\n[ COUNT ]\n";

        std::cout << "Found " << s.count("b") << " elements with key b\n";

        std::cout << "Found " << s.count("w") << " elements with key w\n";
    }
    {
        std::cout << "\n[ LOWER_BOUND ]\n";

        it = s.lower_bound("b");
        if (it != s.end()) {
            std::cout << "Lower bound for b is " << *it << '\n';
        } else {
            std::cout << "Lower bound not found\n";
        }

        it = s.lower_bound("d");
        if (it != s.end()) {
            std::cout << "Lower bound for d is " << *it << '\n';
        } else {
            std::cout << "Lower bound not found\n";
        }
    }
    {
        std::cout << "\n[ UPPER_BOUND ]\n";

        it = s.upper_bound("b");
        if (it != s.end()) {
            std::cout << "Upper bound for b is " << *it << '\n';
        } else {
            std::cout << "Upper bound not found\n";
        }

        it = s.upper_bound("c");
        if (it != s.end()) {
            std::cout << "Upper bound for c is " << *it << '\n';
        } else {
            std::cout << "Upper bound not found\n";
        }
    }
    {
        std::cout << "\n[ EQUAL_RANGE ]\n";

        ft::pair<ft::set<std::string>::iterator, ft::set<std::string>::iterator> ret = s.equal_range("b");
        std::cout << "lower bound points to: ";
        std::cout << *ret.first << " => " << *ret.first << '\n';

        std::cout << "upper bound points to: ";
        std::cout << *ret.second << " => " << *ret.second << '\n';
    }
}

static void eraseTest(void) {
    std::cout << "\n[ ERASE ]\n";
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    t_ftIterator      it;
    {
        ft::set<int> s(array, array + 9);
        std::cout << "\n\nErase single element (1/3)\n";
        s.erase(s.begin());

        printContainer(s, print<int>);

        std::cout << "\n\nErase single element (2/3)\n";
        it = s.begin();
        std::advance(it, 5);
        int         key = *it;

        std::size_t ret = s.erase(key);
        std::cout << "Erase return (1/2) : " << ret << '\n';

        ret = s.erase(key);
        std::cout << "Erase return (2/2) : " << ret << '\n';

        printContainer(s, print<int>);

        std::cout << "\n\nErase single element (3/3)\n";
        s.erase(--s.end());

        printContainer(s, print<int>);
    }
    {
        t_ftIterator      first;
        t_ftIterator      last;
        {
            std::cout << "\n\nErase a range of elements (1/2)\n";
            ft::set<int> s(array, array + 9);
            first   = s.begin();
            last    = first;

            std::advance(last, 5);
            s.erase(first, last);

            printContainer(s, print<int>);
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            ft::set<int> s(array, array + 9);
            first   = s.begin();
            last    = first;

            std::advance(first, 3);
            std::advance(last, 7);

            s.erase(first, last);
            printContainer(s, print<int>);
        }
    }
}


static void insertTest(void) {
    std::cout << "\n[ INSERT ]\n";
    ft::set<int> s;
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        t_ftIterator  it;

        std::cout << "\n\ninsert single element (1/3)\n";
        it = s.insert(s.begin(), 42);

        printContainer(s, print<int>);
        std::cout << "Iterator returned: " << *it << '\n';

        std::cout << "\n\ninsert single element (2/3)\n";
        t_ftPairReturn ret = s.insert(42);

        printContainer(s, print<int>);
        std::cout   << "Pair returned: Key: " << *ret.first
                    << " Value: " << ret.second << '\n';

        std::cout << "\n\ninsert single element (3/3)\n";
        ret = s.insert(42);

        printContainer(s, print<int>);
        std::cout   << "Pair returned: Key: " << *ret.first
                    << " Value: " << ret.second << '\n';
    }
    {
        std::cout << "\n\ninsert multiple elements (1/3)\n";
        s.insert(array, array + 3);

        printContainer(s, print<int>);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        s.insert(array + 5, array + 7);

        printContainer(s, print<int>);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        s.insert(array + 3, array + 10);

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        ft::set<int>             s(array, array + 10);

        s.insert(s.begin(), s.end());
        printContainer(s, print<int>);
    }
}
