/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/map_tests.hpp"

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

    s_create_pairs  pairs(10);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());

    std::cout << "\n[ CONSTRUCTORS ]\n";
    printTime(0);
    {
        std::cout << "\n\nEmpty map\n";
        t_ftStrIntMap             m;

        printContainer(m, print);
    }
    {
        std::cout << "\n\nRange constructor (pointer)\n";
        ft::map<std::string, int>             m(p_begin.ft, p_end.ft);

        printContainer(m, print);
    }
    {
        std::cout << "\n\nRange constructor (iterator)\n";
        const ft::map<std::string, int>     to_copy_from(p_begin.ft, p_end.ft);
        ft::map<std::string, int>           m(to_copy_from.begin(), to_copy_from.end());

        printContainer(m, print);
    }
    {
        std::cout << "\n\nRange constructor with empty range\n";
        t_ftStrIntPair            *pairs = 0;
        t_ftStrIntMap             m(pairs, pairs);

        printContainer(m, print);
    }
    {
        std::cout << "\n\nCopy constructor\n";
        const t_ftStrIntMap           m1(p_begin.ft, p_end.ft);
        t_ftStrIntMap                 m2(m1);

        printContainer(m1, print);
        printContainer(m2, print);
    }
    {
        std::cout << "\n\nCopy constructor with empty map\n";
        t_ftStrIntMap             m1;
        t_ftStrIntMap             m2(m1);

        printContainer(m1, print);
        printContainer(m2, print);
    }
    printTime(1);
}

static void swapTest(void) {

    s_create_pairs  pairs(AMOUNT);
    s_pairs         p_begin(pairs.begin());

    std::cout << "\n[ SWAP ]\n";
    printTime(0);
    t_ftStrIntMap m1(p_begin.ft, p_begin.ft + (pairs.size / 2));
    t_ftStrIntMap m2(p_begin.ft + (pairs.size / 2), p_begin.ft + pairs.size);

    m1.swap(m2);
    printContainer(m1, print);
    printContainer(m2, print);

    swap(m1, m2);
    printContainer(m1, print);
    printContainer(m2, print);
    printTime(1);
}

static void operationsTest(void) {
    t_ftStrIntMap           m;
    std::string             str("a");

    for (int i = 0; i < 100; i++) {
        m[str] = i;
        ++str[0];
    }
    const t_ftStrIntMap     constM(m);

    t_ftIterator            it;
    std::cout << "\n[ OPERATIONS ]\n";
    printTime(0);
    {
        std::cout << "\n[ FIND ]\n";

        it = m.find("b");

        if (it != constM.end()) {
            std::cout << "Found key: " << it->first
                    << " value: " << it->second << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        it = m.find("c");

        if (it != constM.end()) {
            std::cout << "Key: " << it->first
                    << " value: " << it->second << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        it = m.find("h");
        std::cout << (it == m.end()) << '\n';
    }
    {
        std::cout << "\n[ FIND (const) ]\n";

        if (constM.find("b") != constM.end()) {
            std::cout << "Found key: " << constM.find("b")->first
                    << " value: " << constM.find("b")->second << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        if (constM.find("c") != constM.end()) {
            std::cout << "Key: " << constM.find("c")->first
                    << " value: " << constM.find("c")->second << '\n';
        } else {
            std::cout << "Element not found\n";
        }

        std::cout << (constM.find("h") == constM.end()) << '\n';
    }
    {
        std::cout << "\n[ COUNT ]\n";

        std::cout << "Found " << m.count("b")
                << " elements with key b\n";

        std::cout << "Found " << m.count("w")
                << " elements with key w\n";
    }
    {
        std::cout << "\n[ LOWER_BOUND ]\n";

        it = m.lower_bound("b");
        if (it != m.end()) {
            std::cout << "Lower bound for key b is element with key "
                    << it->first << " and value " << it->second << '\n';
        } else {
            std::cout << "Lower bound not found\n";
        }

        it = m.lower_bound("d");
        if (it != m.end()) {
            std::cout << "Lower bound for key d is element with key "
                    << it->first << " and value " << it->second << '\n';
        } else {
            std::cout << "Lower bound not found\n";
        }
    }
    {
        std::cout << "\n[ UPPER_BOUND ]\n";

        it = m.upper_bound("b");
        if (it != m.end()) {
            std::cout << "Upper bound for key b is element with key "
                    << it->first << " and value " << it->second << '\n';
        } else {
            std::cout << "Upper bound not found\n";
        }

        it = m.upper_bound("c");
        if (it != m.end()) {
            std::cout << "Upper bound for key c is element with key "
                    << it->first << " and value " << it->second << '\n';
        } else {
            std::cout << "Upper bound not found\n";
        }
    }
    {
        std::cout << "\n[ EQUAL_RANGE ]\n";

        ft::pair<t_ftIterator, t_ftIterator> ret = m.equal_range("b");
        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';
    }
    printTime(1);
}

static void relationalOperatorsTest(void) {

    s_create_pairs          pairs(AMOUNT);
    s_pairs                 p_begin(pairs.begin());
    s_pairs                 p_end(pairs.end());

    t_ftStrIntMap           M1(p_begin.ft, p_end.ft);
    t_ftStrIntMap           M2(p_begin.ft, p_end.ft);

    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    printTime(0);
    std::cout << "\n\noperator ==\n";
    std::cout << "is equal: " << (M1 == M2);

    std::cout << "\n\noperator !=\n";
    M1.erase(--M1.end());
    std::cout << "is not equal: " << (M1 != M2);

    std::cout << "\n\noperator <\n";
    std::cout << "is less than: " << (M1 < M2);

    std::cout << "\n\noperator <=\n";
    std::cout << "is less than and not equal: " << (M1 <= M2 && M1 != M2);
    M1.insert(ft::make_pair(std::string("0"), 0));
    std::cout << "is less than and equal: " << (M1 <= M2 && M1 == M2);

    std::cout << "\n\noperator >\n";
    M1.insert(ft::make_pair(std::string("9999999999999999999"), 0));
    std::cout << "is greater than : " << (M1 > M2);

    std::cout << "\n\noperator >=\n";
    std::cout << "is greater than and not equal: " << (M1 >= M2 && M1 != M2);
    std::cout << '\n';
    M1.erase(--M1.end());
    std::cout << "is greater than and equal: " << (M1 >= M2 && M1 == M2);
    std::cout << '\n';
    printTime(1);
}

static void assignmentOperatorTest(void) {

    s_create_pairs  pairs(AMOUNT);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());

    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    printTime(0);
    {
        t_ftStrIntMap m1;
        {
            t_ftStrIntMap m2(p_begin.ft, p_begin.ft + (pairs.size / 3));
            m1 = m2;
        }
    }
    {
        t_ftStrIntMap m1;
        t_ftStrIntMap m2(p_begin.ft, p_begin.ft + (pairs.size / 2));

        m1 = m2;
        printContainer(m1, print);
        printContainer(m2, print);

        t_ftStrIntMap v3(p_begin.ft, p_end.ft);
        m1 = v3;
        printContainer(m1, print);
        printContainer(v3, print);
    }
    printTime(1);
}

static void eraseTest(void) {

    s_create_pairs      pairs(AMOUNT);
    s_pairs             p_begin(pairs.begin());
    s_pairs             p_end(pairs.end());
    t_ftIterator        it;
    std::cout << "\n[ ERASE ]\n";
    printTime(0);
    {
        t_ftStrIntMap   m(p_begin.ft, p_end.ft);
        std::cout << "\n\nErase single element (1/3)\n";
        m.erase(m.begin());

        printContainer(m, print);

        std::cout << "\n\nErase single element (2/3)\n";
        it = m.begin();
        srand(AMOUNT);
        std::advance(it, rand() % AMOUNT);
        std::string key = it->first;

        std::size_t ret = m.erase(key);
        std::cout << "Erase return (1/2) : " << ret << '\n';

        ret = m.erase(key);
        std::cout << "Erase return (2/2) : " << ret << '\n';

        printContainer(m, print);

        std::cout << "\n\nErase single element (3/3)\n";
        m.erase(--m.end());

        printContainer(m, print);
    }
    {
        t_ftIterator    first;
        t_ftIterator    last;
        {
            std::cout << "\n\nErase a range of elements (1/2)\n";
            t_ftStrIntMap m(p_begin.ft, p_end.ft);
            first   = m.begin();
            last    = first;

            std::advance(last, pairs.size / 2);

            m.erase(first, last);
            printContainer(m, print);
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            t_ftStrIntMap   m(p_begin.ft, p_end.ft);
            first   = m.begin();
            last    = first;

            std::advance(first, (pairs.size * 0.3));
            std::advance(last, ((pairs.size * 0.7)));

            m.erase(first, last);
            printContainer(m, print);
        }
    }
    printTime(1);
}

static void insertTest(void) {
    t_ftStrIntMap       m;

    s_create_pairs      pairs(AMOUNT);
    s_pairs             p_begin(pairs.begin());
    s_pairs             p_end(pairs.end());
    std::cout << "\n[ INSERT ]\n";
    printTime(0);
    {
        t_ftIterator    it;

        std::cout << "\n\ninsert single element (1/3)\n";
        it = m.insert(m.begin(), ft::make_pair(std::string("10"), 42));

        printContainer(m, print);
        std::cout << "insert return: Key: " << it->first
                    << " Value: " << it->second << '\n';

        std::cout << "\n\ninsert single element (2/3)\n";
        m.insert(ft::make_pair(std::string("42"), 10));

        printContainer(m, print);

        std::cout << "\n\ninsert single element (3/3)\n";
        m.insert(m.begin(), ft::make_pair(std::string("12"), 12));

        printContainer(m, print);
    }
    {
        std::cout << "\n\ninsert multiple elements (1/3)\n";
        m.insert(p_begin.ft, p_begin.ft + static_cast<size_t>(pairs.size * 0.3));

        printContainer(m, print);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        m.insert(p_begin.ft + static_cast<size_t>(pairs.size * 0.5),
                 p_begin.ft + static_cast<size_t>(pairs.size * 0.8));

        printContainer(m, print);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        m.insert(p_begin.ft + static_cast<size_t>(pairs.size * 0.3), p_end.ft);

        printContainer(m, print);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        t_ftStrIntMap   m(p_begin.ft, p_end.ft);

        m.insert(m.begin(), m.end());
        printContainer(m, print);
    }
    printTime(1);
}
