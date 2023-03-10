/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/containers/set_tests.hpp"

static void relationalOperatorsTest(void);
static void assignmentOperatorTest(void);
static void constructorsTest(void);
static void operationsTest(void);
static void insertTest(void);
static void eraseTest(void);
static void swapTest(void);

const int     g_array_size = AMOUNT;
const int     *g_array = createArray(g_array_size);

int main(void) {
    relationalOperatorsTest();
    assignmentOperatorTest();
    constructorsTest();
    operationsTest();
    insertTest();
    eraseTest();
    swapTest();
    printTime(RESULT);
    delete[] g_array;
    return 0;
}

static void constructorsTest(void) {
    std::cout << "\n[ CONSTRUCTORS ]\n";
    printTime(0);
    {
        std::cout << "\n\nEmpty set\n";
        ft::set<int>             s;

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\nRange constructor (pointer)\n";
        ft::set<int>             s(g_array, g_array + g_array_size);

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\nRange constructor (iterator)\n";
        const std::set<int>      to_copy_from(g_array, g_array + g_array_size);
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
        const ft::set<int>           s1(g_array, g_array + g_array_size);
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
    printTime(1);
}

static void swapTest(void) {
    ft::set<int> s1(g_array, g_array + (g_array_size / 2));
    ft::set<int> s2(g_array + (g_array_size / 2), g_array + g_array_size);

    std::cout << "\n[ SWAP ]\n";
    printTime(0);
    s1.swap(s2);
    printContainer(s1, print<int>);
    printContainer(s2, print<int>);

    swap(s1, s2);
    printContainer(s1, print<int>);
    printContainer(s2, print<int>);
    printTime(1);
}

static void relationalOperatorsTest(void) {
    ft::set<int>             s1(g_array, g_array + g_array_size);
    ft::set<int>             s2(g_array, g_array + g_array_size);

    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    printTime(0);
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
    std::cout << '\n';
    printTime(1);
}

static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    printTime(0);
    {
        /* Deep copying */
        ft::set<int> s1;
        {
            ft::set<int> s2(g_array, g_array + (g_array_size / 3));
            s1 = s2;
        }
    }
    {
        ft::set<int> s1;
        ft::set<int> s2(g_array, g_array + (g_array_size / 2));

        s1 = s2;
        printContainer(s1, print<int>);
        printContainer(s2, print<int>);
        ft::set<int> v3(g_array, g_array + g_array_size);
        s1 = v3;
        printContainer(s1, print<int>);
        printContainer(v3, print<int>);
    }
    printTime(1);
}

static void operationsTest(void) {
    ft::set<std::string>           s;
    std::string                    str("a");
    int                            j = 0;

    for (int i = 0; i < AMOUNT; i++) {
        s.insert(str);
        str[j]++;
        if (str[j] > 'z') {
            str += "a";
            j++;
        }
    }

    const ft::set<std::string>     constS(s);
    ft::set<std::string>::iterator it;

    std::cout << "\n[ OPERATIONS ]\n";
    printTime(0);
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
    printTime(1);
}

static void eraseTest(void) {
    t_ftIterator      it;
    std::cout << "\n[ ERASE ]\n";
    printTime(0);
    {
        ft::set<int> s(g_array, g_array + g_array_size);
        std::cout << "\n\nErase single element (1/3)\n";
        s.erase(s.begin());

        printContainer(s, print<int>);

        std::cout << "\n\nErase single element (2/3)\n";
        it = s.begin();
        std::advance(it, g_array_size / 2);
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
            ft::set<int> s(g_array, g_array + g_array_size);
            first   = s.begin();
            last    = first;

            std::advance(last, g_array_size / 2);
            s.erase(first, last);

            printContainer(s, print<int>);
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            ft::set<int> s(g_array, g_array + g_array_size);
            first   = s.begin();
            last    = first;

            std::advance(first, g_array_size * 0.3);
            std::advance(last, g_array_size * 0.7);

            s.erase(first, last);
            printContainer(s, print<int>);
        }
    }
    printTime(1);
}


static void insertTest(void) {
    ft::set<int> s;
    std::cout << "\n[ INSERT ]\n";
    printTime(0);
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
        s.insert(g_array, g_array + static_cast<size_t>(g_array_size * 0.3));

        printContainer(s, print<int>);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        s.insert(g_array + static_cast<size_t>(g_array_size * 0.5),
                 g_array + static_cast<size_t>(g_array_size * 0.7));

        printContainer(s, print<int>);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        s.insert(g_array + static_cast<size_t>(g_array_size * 0.3),
                 g_array + g_array_size);

        printContainer(s, print<int>);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        ft::set<int>             s(g_array, g_array + g_array_size);

        s.insert(s.begin(), s.end());
        printContainer(s, print<int>);
    }
    printTime(1);
}
