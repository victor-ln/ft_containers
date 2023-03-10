/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/map_tests.hpp"

static void relationalOperatorsTest(void);
static void assignmentOperatorTest(void);
static void constructorsTest(void);
static void insertTest(void);
static void eraseTest(void);
static void swapTest(void);

int main(void) {
    relationalOperatorsTest();
    assignmentOperatorTest();
    constructorsTest();
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
    printTime();
}

static void swapTest(void) {
    std::cout << "\n[ SWAP ]\n\n";

    s_create_pairs  pairs(10);
    s_pairs         p_begin(pairs.begin());

    t_ftStrIntMap m1(p_begin.ft, p_begin.ft + 5);
    t_ftStrIntMap m2(p_begin.ft + 5, p_begin.ft + 10);

    m1.swap(m2);
    printContainer(m1, print);
    printContainer(m2, print);

    swap(m1, m2);
    printContainer(m1, print);
    printContainer(m2, print);
    printTime();
}

static void relationalOperatorsTest(void) {
    std::cout << "\n[ RELATIONAL OPERATORS ]\n";

    s_create_pairs          pairs(10);
    s_pairs                 p_begin(pairs.begin());
    s_pairs                 p_end(pairs.end());
    t_ftStrIntMap             M1(p_begin.ft, p_end.ft);
    t_ftStrIntMap             M2(p_begin.ft, p_end.ft);

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
    M1.erase(--M1.end());
    std::cout << "is greater than and equal: " << (M1 >= M2 && M1 == M2);
}

static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    printTime();

    s_create_pairs  pairs(30);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());
    {
        t_ftStrIntMap m1;
        {
            t_ftStrIntMap m2(p_begin.ft, p_begin.ft + 10);
            m1 = m2;
        }
    }
    {
        t_ftStrIntMap m1;
        t_ftStrIntMap m2(p_begin.ft, p_begin.ft + 20);

        m1 = m2;
        printContainer(m1, print);
        printContainer(m2, print);

        t_ftStrIntMap v3(p_begin.ft, p_end.ft);
        m1 = v3;
        printContainer(m1, print);
        printContainer(v3, print);
    }
    printTime();
}

static void eraseTest(void) {
    std::cout << "\n[ ERASE ]\n";

    s_create_pairs  pairs(10);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());
    t_ftIterator      it;
    {
        t_ftStrIntMap m(p_begin.ft, p_end.ft);
        std::cout << "\n\nErase single element (1/3)\n";
        m.erase(m.begin());

        printContainer(m, print);

        std::cout << "\n\nErase single element (2/3)\n";
        it = m.begin();
        std::advance(it, 5);
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
        t_ftIterator      first;
        t_ftIterator      last;
        {
            std::cout << "\n\nErase a range of elements (1/2)\n";
            t_ftStrIntMap m(p_begin.ft, p_end.ft);
            first   = m.begin();
            last    = first;

            std::advance(last, 5);

            m.erase(first, last);
            printContainer(m, print);
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            t_ftStrIntMap m(p_begin.ft, p_end.ft);
            first   = m.begin();
            last    = first;

            std::advance(first, 3);
            std::advance(last, 7);

            m.erase(first, last);
            printContainer(m, print);
        }
    }
    printTime();
}

static void insertTest(void) {
    std::cout << "\n[ INSERT ]\n";
    t_ftStrIntMap     m;

    s_create_pairs  pairs(10);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());
    {
        t_ftIterator  it;

        std::cout << "\n\ninsert single element (1/3)\n";
        it = m.insert(m.begin(), ft::make_pair(std::string("10"), 42));

        printContainer(m, print);
        std::cout << "insert return: Key: " << it->first << " Value: " << it->second << '\n';

        std::cout << "\n\ninsert single element (2/3)\n";
        m.insert(ft::make_pair(std::string("42"), 10));

        printContainer(m, print);

        std::cout << "\n\ninsert single element (3/3)\n";
        m.insert(m.begin(), ft::make_pair(std::string("12"), 12));

        printContainer(m, print);
    }
    {
        std::cout << "\n\ninsert multiple elements (1/3)\n";
        m.insert(p_begin.ft, p_begin.ft + 3);

        printContainer(m, print);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        m.insert(p_begin.ft + 5, p_begin.ft + 7);

        printContainer(m, print);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        m.insert(p_begin.ft + 3, p_end.ft);

        printContainer(m, print);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        t_ftStrIntMap             m(p_begin.ft, p_end.ft);

        m.insert(m.begin(), m.end());
        printContainer(m, print);
    }
    printTime();
}
