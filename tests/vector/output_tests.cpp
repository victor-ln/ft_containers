/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/containers/vector_tests.hpp"

static void relationalOperatorsTest(void);
static void assignmentOperatorTest(void);
static void constructorsTest(void);
static void insertTest(void);
static void assignTest(void);
static void eraseTest(void);
static void swapTest(void);

const int     g_array_size = AMOUNT;
const int     *g_array = createArray(g_array_size);

int main(void) {
    relationalOperatorsTest();
    assignmentOperatorTest();
    constructorsTest();
    assignTest();
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
        std::cout << "\n\nEmpty vector\n";
        ft::vector<int>             v;

        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nRepeated elements\n";
        ft::vector<int>             v(AMOUNT, 100);

        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nRange constructor (pointer)\n";
        ft::vector<int>             v(g_array, g_array + g_array_size);

        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nRange constructor (iterator)\n";
        const std::vector<int>      array(AMOUNT, 100);
        ft::vector<int>             v(array.begin(), array.end());

        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nRange constructor with empty range\n";
        int array[] = {0};
        ft::vector<int>             v(array, array);

        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nCopy constructor\n";
        const ft::vector<int>           v1(g_array, g_array + g_array_size);
        ft::vector<int>                 v2(v1);

        printContainer(v1, print<int>);
        printContainer(v2, print<int>);
    }
    {
        std::cout << "\n\nCopy constructor with empty vector\n";
        ft::vector<int>             v1;
        ft::vector<int>             v2(v1);

        printContainer(v1, print<int>);
        printContainer(v2, print<int>);
    }
    printTime(1);
}

static void swapTest(void) {
    std::cout << "\n[ SWAP ]\n";
    ft::vector<int> v1(g_array, g_array + (g_array_size / 2));
    ft::vector<int> v2(g_array + (g_array_size / 2), g_array + g_array_size);

    printTime(0);
    v1.swap(v2);
    printContainer(v1, print<int>);
    printContainer(v2, print<int>);

    swap(v1, v2);
    printContainer(v1, print<int>);
    printContainer(v2, print<int>);
    printTime(1);
}

static void relationalOperatorsTest(void) {
    ft::vector<int>             V1(g_array, g_array + g_array_size);
    ft::vector<int>             V2(g_array, g_array + g_array_size);

    std::cout << "\n[ RELATIONAL OPERATORS ]\n";
    printTime(0);
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
    std::cout << '\n';
    printTime(1);
}

static void assignmentOperatorTest(void) {
    std::cout << "\n[ ASSIGNMENT OPERATOR ]\n";
    printTime(0);
    {
        /*  Deep copying */
        ft::vector<int> v1;
        {
            ft::vector<int> v2(10, 100);
            v1 = v2;
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2(15, 200);

        /* Equal */
        v1 = v2;
        printContainer(v1, print<int>);
        printContainer(v2, print<int>);
        ft::vector<int> v3(20, 500);
        v1 = v3;
        printContainer(v1, print<int>);
        printContainer(v3, print<int>);
    }
    printTime(1);
}

static void eraseTest(void) {
    ft::vector<int>::iterator      it;

    std::cout << "\n[ ERASE ]\n";
    printTime(1);
    {
        ft::vector<int> v(g_array, g_array + g_array_size);
        std::cout << "\n\nErase single element (1/3)\n";
        it  = v.erase(v.begin());

        printContainer(v, print<int>);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\nErase single element (2/3)\n";
        it  = v.erase(v.begin() + 5);

        printContainer(v, print<int>);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\nErase single element (3/3)\n";
        it  = v.erase(--v.end());

        printContainer(v, print<int>);
        std::cout << "Return iterator: " << *it << '\n';
    }
    {
        ft::vector<int>::iterator      first;
        ft::vector<int>::iterator      last;
        {
            std::cout << "\n\nErase a range of elements (1/2)\n";
            ft::vector<int> v(g_array, g_array + g_array_size);
            first   = v.begin();
            last    = v.begin() + (g_array_size / 2);
            it      = v.erase(first, last);

            printContainer(v, print<int>);
            std::cout << "Return iterator: " << *it << '\n';
        }
        {
            std::cout << "\n\nErase a range of elements (2/2)\n";
            ft::vector<int> v(g_array, g_array + g_array_size);
            first   = v.begin() + (g_array_size * 0.3);
            last    = v.begin() + (g_array_size * 0.7);
            it      = v.erase(first, last);

            printContainer(v, print<int>);
            std::cout << "Return iterator: " << *it << '\n';
        }
    }
    printTime(1);
}


static void insertTest(void) {
    std::cout << "\n[ INSERT ]\n";
    printTime(0);

    ft::vector<int> v(AMOUNT, 100);
    {
        ft::vector<int>::iterator  it;

        std::cout << "\n\ninsert single element (1/3)\n";
        it = v.insert(v.begin(), 42);

        printContainer(v, print<int>);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\ninsert single element (2/3)\n";
        it = v.insert(v.begin() + (g_array_size / 2), 42);

        printContainer(v, print<int>);
        std::cout << "Return iterator: " << *it << '\n';

        std::cout << "\n\ninsert single element (3/3)\n";
        it = v.insert(v.end(), 42);

        printContainer(v, print<int>);
        std::cout << "Return iterator: " << *it << '\n';
    }
    {
        std::cout << "\n\ninsert multiple elements (1/3)\n";
        v.insert(v.begin(), g_array,
                 g_array + static_cast<size_t>(g_array_size * 0.3));

        printContainer(v, print<int>);

        std::cout << "\n\ninsert multiple elements (2/3)\n";
        v.insert(v.begin() + (g_array_size / 2), g_array,
                 g_array + static_cast<size_t>(g_array_size * 0.3));

        printContainer(v, print<int>);

        std::cout << "\n\ninsert multiple elements (3/3)\n";
        v.insert(v.end(), g_array,
                 g_array + static_cast<size_t>(g_array_size * 0.3));

        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\ninsert to itself\n";
        ft::vector<int>             v(AMOUNT, 100);

        v.insert(v.begin(), v.begin(), v.end());
        printContainer(v, print<int>);
    }
    printTime(1);
}

static void assignTest(void) {
    std::cout << "\n[ ASSIGN ]\n";
    printTime(0);
    {
        std::cout << "\n\nassign count\n";
        ft::vector<int>             v(AMOUNT, 100);

        v.assign(5, 200);
        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nassign range\n";
        const std::vector<int>      array(5, 100);
        ft::vector<int>             v(g_array, g_array + g_array_size);

        v.assign(array.begin(), array.end());
        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nassign with input iterator\n";
        ft::vector<int> v(5, 10);

        v.assign(g_array, g_array + (g_array_size / 2));
        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nassign with empty vector\n";
        ft::vector<int>             v(AMOUNT, 100);
        ft::vector<int>             v2;

        v.assign(v2.begin(), v2.end());
        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nassign from empty vector\n";
        ft::vector<int> v;

        v.assign(v.begin(), v.end());
        printContainer(v, print<int>);
    }
    {
        std::cout << "\n\nassign to itself\n";
        ft::vector<int>             v(AMOUNT, 100);

        v.assign(v.begin(), v.end());
        printContainer(v, print<int>);
    }
    printTime(1);
}
