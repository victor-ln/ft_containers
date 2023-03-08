/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "map_tests.hpp"

static void relationalOperatorsTest(void);
static void assignmentOperatorTest(void);
static void constructorsTest(void);
static void insertTest(void);
static void assignTest(void);
static void eraseTest(void);
static void swapTest(void);

int main(void) {
    relationalOperatorsTest();
    assignmentOperatorTest();
    constructorsTest();
    assignTest();
    insertTest();
    eraseTest();
    swapTest();
    return 0;
}

static ftStrIntPair* createStrIntPairs(std::size_t size) {
    if (size) {
        std::stringstream   ss;
        std::string         str;
        ftStrIntPair          *pair_list = new ftStrIntPair[size];

        srand(size);
        for (std::size_t i = 0; i < size; ++i) {
            ss << i, ss >> str;
            pair_list[i] = ftStrIntPair(str, rand());
        }
    }
}

static void constructorsTest(void) {
    ftStrIntPair* pairs = createStrIntPairs(10);

    std::cout << "\n[ CONSTRUCTORS ]\n";
    {
        std::cout << "\n\nEmpty map\n";
        ftStrIntMap             m;

        printContainer(m, print);
    }
    {
        std::cout << "\n\nRange constructor (pointer)\n";
        ft::map<std::string, int>             m(pairs, pairs + 10);

        printContainer(m, print);
    }
    {
        std::cout << "\n\nRange constructor (iterator)\n";
        const std::map<std::string, int>    to_copy_from(pairs, pairs + 10);
        ft::map<std::string, int>           m(to_copy_from.begin(), to_copy_from.end());

        printContainer(m, print);
    }
    {
        std::cout << "\n\nRange constructor with empty range\n";
        int array[] = {0};
        ftStrIntMap             m(array, array);

        printContainer(m, print);
    }
    {
        std::cout << "\n\nCopy constructor\n";
        const ftStrIntMap           v1(pairs, pairs + 10);
        ftStrIntMap                 v2(v1);

        printContainer(v1, print);
        printContainer(v2, print);
    }
    {
        std::cout << "\n\nCopy constructor with empty map\n";
        ftStrIntMap             v1;
        ftStrIntMap             v2(v1);

        printContainer(v1, print);
        printContainer(v2, print);
    }
    delete []pairs;
}

static void swapTest(void) {
    std::cout << "\n[ SWAP ]\n\n";
    ftStrIntMap v1(3, 42);
    ftStrIntMap v2(5, 21);

    v1.swap(v2);
    printContainer(v1, print);
    printContainer(v2, print);

    swap(v1, v2);
    printContainer(v1, print);
    printContainer(v2, print);
}

static void relationalOperatorsTest(void) {
    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    ftStrIntPair* pairs = createStrIntPairs(10);
    ftStrIntMap             V1(pairs, pairs + 10);
    ftStrIntMap             V2(pairs, pairs + 10);

    std::cout << "\n\noperator ==\n";
    std::cout << "is equal: " << (V1 == V2);

    std::cout << "\n\noperator !=\n";
    V1.erase(--V1.end());
    std::cout << "is not equal: " << (V1 != V2);

    std::cout << "\n\noperator <\n";
    std::cout << "is less than: " << (V1 < V2);

    std::cout << "\n\noperator <=\n";
    std::cout << "is less than and not equal: " << (V1 <= V2 && V1 != V2);
    V1.insert(ft::make_pair(std::string("0"), 0));
    std::cout << "is less than and equal: " << (V1 <= V2 && V1 == V2);

    std::cout << "\n\noperator >\n";
    V1.insert(ft::make_pair(std::string("9999999999999999999"), 0));
    std::cout << "is greater than : " << (V1 > V2);

    std::cout << "\n\noperator >=\n";
    std::cout << "is greater than and not equal: " << (V1 >= V2 && V1 != V2);
    V1.erase(--V1.end());
    std::cout << "is greater than and equal: " << (V1 >= V2 && V1 == V2);
    delete []pairs;
}

static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    {
        std::cout << "\n\nDeep copying\n";
        ftStrIntMap v1;
        {
            ftStrIntMap v2(10, 100);
            v1 = v2;
        }
    }
    {
        ftStrIntMap v1;
        ftStrIntMap v2(15, 200);

        std::cout << "\n\nEqual\n";
        v1 = v2;
        printContainer(v1, print);
        printContainer(v2, print);
        ftStrIntMap v3(20, 500);
        v1 = v3;
        printContainer(v1, print);
        printContainer(v3, print);
    }
}

static void eraseTest(void) {
    std::cout << "\n[ ERASE ]\n";
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    ftIterator      it;
    {
        ftStrIntMap m(a, a + 9);
        std::cout << "\n\nErase single element (1/3)\n";
        m.erase(m.begin());

        printContainer(m, print);

        std::cout << "\n\nErase single element (2/3)\n";
        it = m.begin();
        std::advance(it, 5);
        m.erase(it);

        printContainer(m, print);

        std::cout << "\n\nErase single element (3/3)\n";
        m.erase(--m.end());

        printContainer(m, print);
    }
    {
        ftIterator      first;
        ftIterator      last;
        {
            std::cout << "\n\nErase a range of elements (1/2)\n";
            ftStrIntMap m(a, a + 9);
            first   = m.begin();
            last    = first;

            std::advance(last, 5);

            m.erase(first, last);
            printContainer(m, print);
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            ftStrIntMap m(a, a + 9);
            first   = m.begin();
            last    = first;

            std::advance(first, 3);
            std::advance(first, 7);

            m.erase(first, last);
            printContainer(m, print);
        }
    }
}

static void insertTest(void) {
    std::cout << "\n[ INSERT ]\n";
    ftStrIntMap m;
    {
        ftIterator  it;

        std::cout << "\n\ninsert single element (1/3)\n";
        m.insert(m.begin(), ft::make_pair(std::string("10"), 42));

        printContainer(m, print);

        std::cout << "\n\ninsert single element (2/3)\n";
        m.insert(m.begin() + 5, 42);

        printContainer(m, print);

        std::cout << "\n\ninsert single element (3/3)\n";
        m.insert(m.end(), 42);

        printContainer(m, print);
    }
    {
        int arr[] = { 1, 2, 3 };
        std::cout << "\n\ninsert multiple elements (1/3)\n";
        m.insert(m.begin(), arr, arr + 3);

        printContainer(m, print);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        m.insert(m.begin() + 5, arr, arr + 3);

        printContainer(m, print);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        m.insert(m.end(), arr, arr + 3);

        printContainer(m, print);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        ftStrIntMap             m(10, 100);

        m.insert(m.begin(), m.begin(), m.end());
        printContainer(m, print);
    }
}

static void assignTest(void) {
    std::cout << "\n[ ASSIGN ]\n";
    {
        std::cout << "\n\nassign count\n";
        ftStrIntMap             m(10, 100);

        m.assign(5, 200);
        printContainer(m, print);
    }
    {
        std::cout << "\n\nassign range\n";
        int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        const std::map<int>      array(5, 100);
        ftStrIntMap             m(a, a + 9);

        m.assign(array.begin(), array.end());
        printContainer(m, print);
    }
    {
        std::cout << "\n\nassign with input iterator\n";
        int a[] = { 1, 2, 3, 4, 5 };
        ftStrIntMap m(5, 10);

        m.assign(a, a + 5);
        printContainer(m, print);
    }
    {
        std::cout << "\n\nassign with empty map\n";
        ftStrIntMap             m(10, 100);
        ftStrIntMap             v2;

        m.assign(v2.begin(), v2.end());
        printContainer(m, print);
    }
    {
        std::cout << "\n\nassign from empty map\n";
        ftStrIntMap m;

        m.assign(m.begin(), m.end());
        printContainer(m, print);
    }
    {
        std::cout << "\n\nassign to itself\n";
        ftStrIntMap             m(10, 100);

        m.assign(m.begin(), m.end());
        printContainer(m, print);
    }
}
