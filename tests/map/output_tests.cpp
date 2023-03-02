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

static void constructorsTest(void) {
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "\n[ CONSTRUCTORS ]\n";
    {
        std::cout << "\n\nEmpty map\n";
        ft::map<int>             v;

        printmap(v);
    }
    {
        std::cout << "\n\nRepeated elements\n";
        ft::map<int>             v(10, 100);

        printmap(v);
    }
    {
        std::cout << "\n\nRange constructor (pointer)\n";
        ft::map<int>             v(a, a + 9);

        printmap(v);
    }
    {
        std::cout << "\n\nRange constructor (iterator)\n";
        const std::map<int>      array(10, 100);
        ft::map<int>             v(array.begin(), array.end());

        printmap(v);
    }
    {
        std::cout << "\n\nRange constructor with empty range\n";
        int array[] = {0};
        ft::map<int>             v(array, array);

        printmap(v);
    }
    {
        std::cout << "\n\nCopy constructor\n";
        const ft::map<int>           v1(a, a + 9);
        ft::map<int>                 v2(v1);

        printmap(v1);
        printmap(v2);
    }
    {
        std::cout << "\n\nCopy constructor with empty map\n";
        ft::map<int>             v1;
        ft::map<int>             v2(v1);

        printmap(v1);
        printmap(v2);
    }
}

static void swapTest(void) {
    std::cout << "\n[ SWAP ]\n\n";
    ft::map<int> v1(3, 42);
    ft::map<int> v2(5, 21);

    v1.swap(v2);
    printmap(v1);
    printmap(v2);

    swap(v1, v2);
    printmap(v1);
    printmap(v2);
}

static void relationalOperatorsTest(void) {
    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    ft::map<int>             V1(10, 1);
    ft::map<int>             V2(10, 1);

    std::cout << "\n\noperator ==\n";
    std::cout << "is equal: " << (V1 == V2);

    std::cout << "\n\noperator !=\n";
    V1.pop_back();
    std::cout << "is not equal: " << (V1 != V2);

    std::cout << "\n\noperator <\n";
    std::cout << "is less than: " << (V1 < V2);

    std::cout << "\n\noperator <=\n";
    std::cout << "is less than and not equal: " << (V1 <= V2 && V1 != V2);
    V1.push_back(1);
    std::cout << "is less than and equal: " << (V1 <= V2 && V1 == V2);

    std::cout << "\n\noperator >\n";
    V1.push_back(100);
    std::cout << "is greater than : " << (V1 > V2);

    std::cout << "\n\noperator >=\n";
    std::cout << "is greater than and not equal: " << (V1 >= V2 && V1 != V2);
    V1.pop_back();
    std::cout << "is greater than and equal: " << (V1 >= V2 && V1 == V2);
}

static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    {
        std::cout << "\n\nDeep copying\n";
        ft::map<int> v1;
        {
            ft::map<int> v2(10, 100);
            v1 = v2;
        }
    }
    {
        ft::map<int> v1;
        ft::map<int> v2(15, 200);

        std::cout << "\n\nEqual\n";
        v1 = v2;
        printmap(v1);
        printmap(v2);
        ft::map<int> v3(20, 500);
        v1 = v3;
        printmap(v1);
        printmap(v3);
    }
}

static void eraseTest(void) {
    std::cout << "\n[ ERASE ]\n";
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    ftIterator      it;
    {
        ft::map<int> v(a, a + 9);
        std::cout << "\n\nErase single element (1/3)\n";
        it  = v.erase(v.begin());

        printmap(v);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\nErase single element (2/3)\n";
        it  = v.erase(v.begin() + 5);

        printmap(v);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\nErase single element (3/3)\n";
        it  = v.erase(--v.end());

        printmap(v);
        std::cout << "Return iterator: " << *it << '\n';
    }
    {
        ftIterator      first;
        ftIterator      last;
        {
            std::cout << "\n\nErase a range of elements (1/2)\n";
            ft::map<int> v(a, a + 9);
            first   = v.begin();
            last    = v.begin() + 5;
            it      = v.erase(first, last);

            printmap(v);
            std::cout << "Return iterator: " << *it << '\n';
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            ft::map<int> v(a, a + 9);
            first   = v.begin() + 3;
            last    = v.begin() + 7;
            it      = v.erase(first, last);

            printmap(v);
            std::cout << "Return iterator: " << *it << '\n';
        }
    }
}


static void insertTest(void) {
    std::cout << "\n[ INSERT ]\n";
    ft::map<int> v(10, 100);
    {
        ftIterator  it;

        std::cout << "\n\ninsert single element (1/3)\n";
        it = v.insert(v.begin(), 42);

        printmap(v);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\ninsert single element (2/3)\n";
        it = v.insert(v.begin() + 5, 42);

        printmap(v);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\ninsert single element (3/3)\n";
        it = v.insert(v.end(), 42);

        printmap(v);
        std::cout << "Return iterator: " << *it << '\n';
    }
    {
        int arr[] = { 1, 2, 3 };
        std::cout << "\n\ninsert multiple elements (1/3)\n";
        v.insert(v.begin(), arr, arr + 3);

        printmap(v);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        v.insert(v.begin() + 5, arr, arr + 3);

        printmap(v);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        v.insert(v.end(), arr, arr + 3);

        printmap(v);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        ft::map<int>             v(10, 100);

        v.insert(v.begin(), v.begin(), v.end());
        printmap(v);
    }
}

static void assignTest(void) {
    std::cout << "\n[ ASSIGN ]\n";
    {
        std::cout << "\n\nassign count\n";
        ft::map<int>             v(10, 100);

        v.assign(5, 200);
        printmap(v);
    }
    {
        std::cout << "\n\nassign range\n";
        int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        const std::map<int>      array(5, 100);
        ft::map<int>             v(a, a + 9);

        v.assign(array.begin(), array.end());
        printmap(v);
    }
    {
        std::cout << "\n\nassign with input iterator\n";
        int a[] = { 1, 2, 3, 4, 5 };
        ft::map<int> v(5, 10);

        v.assign(a, a + 5);
        printmap(v);
    }
    {
        std::cout << "\n\nassign with empty map\n";
        ft::map<int>             v(10, 100);
        ft::map<int>             v2;

        v.assign(v2.begin(), v2.end());
        printmap(v);
    }
    {
        std::cout << "\n\nassign from empty map\n";
        ft::map<int> v;

        v.assign(v.begin(), v.end());
        printmap(v);
    }
    {
        std::cout << "\n\nassign to itself\n";
        ft::map<int>             v(10, 100);

        v.assign(v.begin(), v.end());
        printmap(v);
    }
}
