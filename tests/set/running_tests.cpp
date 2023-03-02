/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "set_tests.hpp"

static void algorithmsTest(void);
static void exceptionsTest(void);
static void accessorsTest(void);
static void iteratorTest(void);
static void pushBackTest(void);
static void popBackTest(void);
static void reserveTest(void);
static void resizeTest(void);
static void clearTest(void);
static void sizeTest(void);

int main(void) {
    exceptionsTest();
    algorithmsTest();
    accessorsTest();
    iteratorTest();
    pushBackTest();
    popBackTest();
    reserveTest();
    resizeTest();
    clearTest();
    sizeTest();
    printStatus(RESULT);
    return 0;
}

static void algorithmsTest(void) {
    printColor(CYAN, "\n[ LEXICOGRAPHICAL ]\n");

    {
        ft::set<int> V1(14, 10);
        ft::set<int> V2(15, 10);
        {
            printColor(BGWHITE, "\n├─ Different size\n");
            printStatus(ft::lexicographical_compare(V1.begin(), V1.end(),
                                                    V2.begin(), V2.end()));
            V1.push_back(10);

            printColor(BGWHITE, "\n├─ Same size and value\n");
            printStatus(!ft::lexicographical_compare(V1.begin(), V1.end(),
                                                    V2.begin(), V2.end()));

            printColor(BGWHITE, "\n├─ Same size and value with pred\n");
            printStatus(!ft::lexicographical_compare(V1.begin(), V1.end(),
                                                V2.begin(), V2.end(), comp));
        }
        {
            printColor(CYAN, "\n[ EQUAL ]\n");

            printColor(BGWHITE, "\n├─ Same size and value\n");
            printStatus(ft::equal(V1.begin(), V1.end(), V2.data()));

            printColor(BGWHITE, "\n├─ Different size\n");
            V1.pop_back();
            printStatus(ft::equal(V1.begin(), V1.end(), V2.data()));

            printColor(BGWHITE,
                "\n├─ Same size and different value with pred\n");
            V1.push_back(1000);
            printStatus(!ft::equal(V1.begin(), V1.end(), V2.begin(), comp));
        }
    }
}

static void clearTest(void) {
    printColor(CYAN, "\n[ CLEAR ]\n\n");
    ft::set<int>             ftV(10, 1);
    std::set<int>            stdV(10, 1);

    ftV.clear();
    stdV.clear();
    printStatus(compare_containers(ftV, stdV));
}

static void resizeTest(void) {
    printColor(CYAN, "\n[ RESIZE ]\n");
    {
        printColor(BGWHITE, "\n├─ resizing to a smaller size\n");
        ft::set<int> ftV(5, 42);
        std::set<int> stdV(5, 42);
        ftV.resize(3);
        stdV.resize(3);
        printStatus(compare_containers(ftV, stdV));
    }
    {
        printColor(BGWHITE,
            "\n├─ resizing to a larger size, with default value\n");
        ft::set<int> ftV(3, 42);
        std::set<int> stdV(3, 42);
        ftV.resize(5);
        stdV.resize(5);
        printStatus(compare_containers(ftV, stdV));
    }
    {
        printColor(BGWHITE,
            "\n├─ resizing to a larger size, with custom value\n");
        ft::set<int> ftV(3, 42);
        std::set<int> stdV(3, 42);
        ftV.resize(5, 84);
        stdV.resize(5, 84);
        printStatus(compare_containers(ftV, stdV));
    }
}

static void reserveTest(void) {
    printColor(CYAN, "\n[ RESERVE ]\n");
    {
        printColor(BGWHITE,
            "\n├─ capacity increases by the requested amount\n");
        ft::set<int> ftV;
        std::set<int> stdV;
        ftV.reserve(10);
        stdV.reserve(10);
        printStatus(ftV.capacity() == stdV.capacity());
        printStatus(ftV.size() == stdV.size());

        const size_t old_capacity = ftV.capacity();
        ftV.reserve(20);
        stdV.reserve(20);
        printStatus(ftV.capacity() == old_capacity + 10);
        printStatus(ftV.size() == stdV.size());
    }
    {
        printColor(BGWHITE, "\n├─ smaller capacity than the current size doesn't modify the size.\n");
        ft::set<int> ftV;
        std::set<int> stdV;
        ftV.reserve(10);
        stdV.reserve(10);
        printStatus(ftV.capacity() == stdV.capacity());
        printStatus(ftV.size() == stdV.size());

        const size_t old_size = ftV.size();
        ftV.reserve(5);
        stdV.reserve(5);
        printStatus(ftV.capacity() == 10);
        printStatus(ftV.size() == old_size);
    }
    {
        printColor(BGWHITE, "\n├─ capacity smaller than the current size doesn't invalidate any iterators or references to elements.\n");
        int a[] = { 1, 2, 3, 4, 5 };
        ft::set<int> ftV(a, a + 5);
        std::set<int> stdV(a, a + 5);

        ftV.reserve(10);
        stdV.reserve(10);
        printStatus(ftV.capacity() == stdV.capacity());
        printStatus(ftV.size() == stdV.size());

        ftIterator  ft_it = ftV.begin() + 2;
        stdIterator or_it = stdV.begin() + 2;
        const size_t old_size = ftV.size();

        ftV.reserve(5);
        stdV.reserve(5);
        printStatus(ftV.capacity() == 10);
        printStatus(ftV.size() == old_size);
        printStatus(*ft_it == *or_it);
    }
}

static void iteratorTest(void) {
    int a[] = { 1, 2, 3, 4, 5 };
    ft::set<int>                     ftV(a, a + 5);
    std::set<int>                    stdV(a, a + 5);
    const ft::set<int>               constFtV(a, a + 5);

    printColor(CYAN, "\n[ ITERATORS ]\n");
    {
        printColor(CYAN, "\n  { random_access_iterator }\n");
        printColor(CYAN, "\n    ( member functions )\n");
        ftIterator                      ftIt = ftV.begin() + 2;
        stdIterator                     stdIt = stdV.begin() + 2;
        {
            ftConstIterator             ftConstIt = constFtV.begin() + 2;
            stdConstIterator            stdConstIt = stdV.begin() + 2;

            printColor(BGWHITE, "\n├─ iterator::base()\n");
            printStatus(*ftIt.base() == *stdIt.base());
            printStatus(*ftConstIt.base() == *stdConstIt.base());

            printColor(BGWHITE, "\n├─ iterator::operator[]\n");
            printStatus(ftIt[0] == stdIt[0]);
            printStatus(ftConstIt[0] == stdConstIt[0]);

            ftIt[0] = 10;
            stdIt[0] = 10;
            printStatus(ftIt[0] == stdIt[0]);
    
            printColor(BGWHITE, "\n├─ iterator::operator*\n");
            *ftIt = 1;
            *stdIt = 1;
            printStatus(*ftIt == *stdIt);
        }

        printColor(BGWHITE, "\n├─ iterator::operator++\n");
        printStatus(*ftIt++ == *stdIt++);
        printStatus(*ftIt == *stdIt);
        printStatus(*++ftIt == *++stdIt);

        printColor(BGWHITE, "\n├─ iterator::operator--\n");
        printStatus(*ftIt-- == *stdIt--);
        printStatus(*ftIt == *stdIt);
        printStatus(*--ftIt == *--stdIt);

        printColor(BGWHITE, "\n├─ iterator::operator+=\n");
        printStatus(*(ftIt += 2) == *(stdIt += 2));

        printColor(BGWHITE, "\n├─ iterator::operator-=\n");
        printStatus(*(ftIt -= 2) == *(stdIt -= 2));

        printColor(BGWHITE, "\n├─ iterator::operator+\n");
        printStatus(*(ftIt + 2) == *(stdIt + 2));

        printColor(BGWHITE, "\n├─ iterator::operator-\n");
        printStatus(*(ftIt - 2) == *(stdIt - 2));

        printColor(BGWHITE, "\n├─ iterator::operator->\n");
        std::set<std::string>        stdStrV(1, "Hello");
        ft::set<std::string>         ftStrV(1, "Hello");
        const ft::set<std::string>   ftConstStrV(1, "Hello");

        printStatus(stdStrV.begin()->size() == ftStrV.begin()->size());
        printStatus(stdStrV.begin()->size() == ftConstStrV.begin()->size());

        printColor(CYAN, "\n    ( non-member functions )\n");
        {
            ftIterator   ftCmpIt(ftIt);
            stdIterator  stdCmpIt(stdIt);

            printColor(BGWHITE, "\n├─ iterator::operator==\n");
            printStatus((ftIt == ftCmpIt) == (stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator!=\n");
            printStatus((++ftIt != ftCmpIt) == (++stdIt != stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator>\n");
            printStatus((ftIt > ftCmpIt) == (stdIt > stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator>=\n");
            printStatus((ftIt >= ftCmpIt && ftIt != ftCmpIt) == \
                        (stdIt >= stdCmpIt && stdIt != stdCmpIt));
            ++ftCmpIt;
            ++stdCmpIt;
            printStatus((ftIt >= ftCmpIt && ftIt == ftCmpIt) == \
                        (stdIt >= stdCmpIt && stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator<\n");
            ++ftCmpIt;
            ++stdCmpIt;
            printStatus((ftIt < ftCmpIt) == (stdIt < stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator<=\n");
            printStatus((ftIt <= ftCmpIt && ftIt != ftCmpIt) == \
                        (stdIt <= stdCmpIt && stdIt != stdCmpIt));
            --ftCmpIt;
            --stdCmpIt;
            printStatus((ftIt <= ftCmpIt && ftIt == ftCmpIt) == \
                        (stdIt <= stdCmpIt && stdIt == stdCmpIt));
        }
    }
    {
        ftReverseIterator               ftIt = ftV.rbegin() + 2;
        stdReverseIterator              stdIt = stdV.rbegin() + 2;
        {
            ftConstReverseIterator      ftConstIt = constFtV.rbegin() + 2;
            stdConstReverseIterator     stdConstIt = stdV.rbegin() + 2;

            printColor(CYAN, "\n  { reverse_iterator }\n");
            printColor(CYAN, "\n    ( member functions )\n");
            printColor(BGWHITE, "\n├─ reverse_iterator::base()\n");
            printStatus(*ftIt.base() == *stdIt.base());
            printStatus(*ftConstIt.base() == *stdConstIt.base());

            printColor(BGWHITE, "\n├─ reverse_iterator::operator[]\n");
            printStatus(ftIt[0] == stdIt[0]);
            printStatus(ftConstIt[0] == ftConstIt[0]);
            ftIt[0] = 10;
            stdIt[0] = 10;
            printStatus(ftIt[0] == stdIt[0]);

            printColor(BGWHITE, "\n├─ reverse_iterator::operator*\n");
            *ftIt = 1;
            *stdIt = 1;
            printStatus(*ftIt == *stdIt);
        }

        printColor(BGWHITE, "\n├─ reverse_iterator::operator++\n");
        printStatus(*ftIt++ == *stdIt++);
        printStatus(*ftIt == *stdIt);
        printStatus(*++ftIt == *++stdIt);

        printColor(BGWHITE, "\n├─ reverse_iterator::operator--\n");
        printStatus(*ftIt-- == *stdIt--);
        printStatus(*ftIt == *stdIt);
        printStatus(*--ftIt == *--stdIt);

        printColor(BGWHITE, "\n├─ reverse_iterator::operator+=\n");
        printStatus(*(ftIt += 2) == *(stdIt += 2));

        printColor(BGWHITE, "\n├─ reverse_iterator::operator-=\n");
        printStatus(*(ftIt -= 2) == *(stdIt -= 2));

        printColor(BGWHITE, "\n├─ reverse_iterator::operator+\n");
        printStatus(*(ftIt + 2) == *(stdIt + 2));

        printColor(BGWHITE, "\n├─ reverse_iterator::operator-\n");
        printStatus(*(ftIt - 2) == *(stdIt - 2));

        printColor(BGWHITE, "\n├─ reverse_iterator::operator->\n");
        std::set<std::string>        stdStrV(1, "Hello");
        ft::set<std::string>         ftStrV(1, "Hello");
        const ft::set<std::string>   ftConstStrV(1, "Hello");

        printStatus(stdStrV.rbegin()->size() == ftStrV.rbegin()->size());
        printStatus(stdStrV.rbegin()->size() == ftConstStrV.rbegin()->size());
        printColor(CYAN, "\n    ( non-member functions )\n");
        {
            ftReverseIterator   ftCmpIt(ftIt);
            stdReverseIterator  stdCmpIt(stdIt);

            printColor(BGWHITE, "\n├─ iterator::operator==\n");
            printStatus((ftIt == ftCmpIt) == (stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator!=\n");
            printStatus((++ftIt != ftCmpIt) == (++stdIt != stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator>\n");
            printStatus((ftIt > ftCmpIt) == (stdIt > stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator>=\n");
            printStatus((ftIt >= ftCmpIt && ftIt != ftCmpIt) == \
                        (stdIt >= stdCmpIt && stdIt != stdCmpIt));
            ++ftCmpIt;
            ++stdCmpIt;
            printStatus((ftIt >= ftCmpIt && ftIt == ftCmpIt) == \
                        (stdIt >= stdCmpIt && stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator<\n");
            ++ftCmpIt;
            ++stdCmpIt;
            printStatus((ftIt < ftCmpIt) == (stdIt < stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator<=\n");
            printStatus((ftIt <= ftCmpIt && ftIt != ftCmpIt) == \
                        (stdIt <= stdCmpIt && stdIt != stdCmpIt));
            --ftCmpIt;
            --stdCmpIt;
            printStatus((ftIt <= ftCmpIt && ftIt == ftCmpIt) == \
                        (stdIt <= stdCmpIt && stdIt == stdCmpIt));
        }
    }
    {
        printColor(BGWHITE, "\n├─ begin()\n");
        ftConstIterator                 ftConstIt = constFtV.begin();
        ftIterator                      ftIt = ftV.begin();
        stdIterator                     stdIt = stdV.begin();

        printStatus(*ftIt == *stdIt);
        printStatus(*ftConstIt == *ftIt);
        printStatus(*ftConstIt == *stdIt);
    }
    {
        printColor(BGWHITE, "\n├─ rbegin()\n");
        ftConstReverseIterator          ftConstIt = constFtV.rbegin();
        ftReverseIterator               ftIt = ftV.rbegin();
        stdReverseIterator              stdIt = stdV.rbegin();

        printStatus(*ftIt == *stdIt);
        printStatus(*ftConstIt == *ftIt);
        printStatus(*ftConstIt == *stdIt);
    }
    {
        printColor(BGWHITE, "\n├─ end()\n");
        ftConstIterator                 ftConstIte = constFtV.end();
        ftIterator                      ftIte = ftV.end();
        stdIterator                     stdIte = stdV.end();

        printStatus(*ftIte == *stdIte);
        printStatus(*ftConstIte == *ftIte);
        printStatus(*ftConstIte == *stdIte);
    }
    {
        printColor(BGWHITE, "\n├─ rend()\n");
        ftConstReverseIterator          ftConstIte = constFtV.rend();
        ftReverseIterator               ftIte = ftV.rend();
        stdReverseIterator              stdIte = stdV.rend();

        printStatus(*ftIte == *stdIte);
        printStatus(*ftConstIte == *ftIte);
        printStatus(*ftConstIte == *stdIte);
    }
}

static void pushBackTest(void) {
    printColor(CYAN, "\n[ PUSH_BACK ]\n");
    {
        printColor(BGWHITE, "\n├─ push_back (non-empty set)\n");
        ft::set<int>             ftV(10, 100);
        std::set<int>            stdV(10, 100);
        ftV.push_back(42);
        stdV.push_back(42);

        printStatus(*(--ftV.end()) == *(--stdV.end()));
    }
    {
        printColor(BGWHITE, "\n├─ push_back (empty set)\n");
        ft::set<int>             ftV;
        std::set<int>            stdV;
        ftV.push_back(42);
        stdV.push_back(42);

        printStatus(*(--ftV.end()) == *(--stdV.end()));
    }
}

static void popBackTest(void) {
    printColor(CYAN, "\n[ POP_BACK ]\n");
    {
        printColor(BGWHITE, "\n├─ pop_back (non-empty set)\n");
        int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        ft::set<int>             ftV(a, a + 9);
        std::set<int>            stdV(a, a + 9);
        ftV.pop_back();
        stdV.pop_back();

        printStatus(compare_begin_and_end(ftV, stdV));
        printStatus(ftV.capacity() == stdV.capacity());
        printStatus(!ftV.empty());
    }
    {
        printColor(BGWHITE, "\n├─ pop_back (empty set)\n");
        ft::set<int>             ftV;
        ftV.pop_back();
        printStatus(ftV.empty());
    }
}

static void sizeTest(void) {
    printColor(CYAN, "\n[ SIZE ]\n");
    {
        printColor(BGWHITE, "\n├─ size (non-empty set)\n");
        ft::set<int>             ftV(10);
        std::set<int>            stdV(10);

        printStatus(ftV.size() == ftV.size());
    }
    {
        printColor(BGWHITE, "\n├─ size (empty set)\n");
        ft::set<int>             ftV;
        std::set<int>            stdV;

        printStatus(ftV.size() == stdV.size());
    }
    printColor(CYAN, "\n[ CAPACITY ]\n");
    {
        printColor(BGWHITE, "\n├─ capacity (non-empty set)\n");
        ft::set<int>             ftV(10);
        std::set<int>            stdV(10);
        printStatus(ftV.capacity() == stdV.capacity());
    }
    {
        printColor(BGWHITE, "\n├─ capacity (empty set)\n");
        ft::set<int>             ftV;
        std::set<int>            stdV;
        printStatus(ftV.capacity() == stdV.capacity());
    }
}

static void accessorsTest(void) {
    printColor(CYAN, "\n[ ACCESSORS ]\n\n");
    ft::set<int>     ftV(10);
    std::set<int>    stdV(10);
    for (int i = 0; i < 10; i++) {
        ftV[i] = i;
        stdV[i] = i;
    }
    const ft::set<int>   constFtV(ftV);

    printColor(BGWHITE, "\n├─ operator[]\n");
    printStatus(ftV[4] == stdV[4]);
    printColor(BGWHITE, "\n├─ operator[] const\n");
    printStatus(constFtV[4] == stdV[4]);

    printColor(BGWHITE, "\n├─ at()\n");
    printStatus(ftV.at(4) == stdV.at(4));
    ftV.at(4) = 42;
    printStatus(ftV.at(4) != stdV.at(4));
    ftV.at(4) = 4;
    printColor(BGWHITE, "\n├─ at() const\n");
    printStatus(constFtV.at(4) == stdV.at(4));

    printColor(BGWHITE, "\n├─ front()\n");
    printStatus(ftV.front() == stdV.front());
    ftV.front() = 12;
    printStatus(ftV.front() != stdV.front());
    ftV.front() = 0;
    printColor(BGWHITE, "\n├─ front() const\n");
    printStatus(constFtV.front() == stdV.front());

    printColor(BGWHITE, "\n├─ back()\n");
    printStatus(ftV.back() == stdV.back());
    ftV.back() = 25;
    printStatus(ftV.back() != stdV.back());
    ftV.back() = 9;
    printColor(BGWHITE, "\n├─ back() const\n");
    printStatus(constFtV.back() == stdV.back());

    int *ftData = ftV.data();
    int *stdData = stdV.data();
    const int *constFtData = constFtV.data();

    printColor(BGWHITE, "\n├─ data()\n");
    printStatus(*ftData == *stdData);
    ftData[4] = 42;
    printStatus(ftV[4] != stdV[4]);
    printColor(BGWHITE, "\n├─ data() const\n");
    printStatus(*constFtData == *stdData);
}

static void exceptionsTest(void) {
    printColor(CYAN, "\n[ EXCEPTIONS ]\n\n");
    {
        printColor(BGWHITE, "\n├─ accessing empty set\n");
        ft::set<int>         emptyVec;
        const ft::set<int>   constEmptyVec;
        accessorTestAux1(emptyVec, 42);
        accessorTestAux2(emptyVec, 25);
        accessorTestAux1(constEmptyVec, 42);
        accessorTestAux2(constEmptyVec, 25);
    }
    {
        printColor(BGWHITE, "\n├─ accessing out of range\n");
        ft::set<int>         v(1, 42);
        const ft::set<int>   constV(1, 42);
        accessorTestAux1(v, 1);
        accessorTestAux2(v, 1);
        accessorTestAux1(constV, 1);
        accessorTestAux2(constV, 1);
    }

    printColor(BGWHITE, "\n├─ pushing back an element at its max_size\n");
    try {
        ft::set<int> v(std::numeric_limits<size_t>::max());
        v.push_back(1);
        std::cerr << EXCEPT_MSG_03;
        printStatus(false);
    } catch (const std::exception& e) { printStatus(true); }

    printColor(BGWHITE, "\n├─ resizing to larger than its max_size\n");
    try {
        ft::set<int> v(1);
        v.resize(v.max_size() + 1);
        std::cerr << EXCEPT_MSG_02;
        printStatus(false);
    } catch (const std::length_error& e) { printStatus(true); }

    printColor(BGWHITE, "\n├─ resizing to negative size\n");
    try {
        ft::set<int> v(1);
        v.resize(-1);
        std::cerr << EXCEPT_MSG_04;
        printStatus(false);
    } catch (const std::length_error& e) { printStatus(true); }

    printColor(BGWHITE, "\n├─ reserving to negative size\n");
    try {
        ft::set<int> v;
        v.reserve(-1);
        std::cerr << EXCEPT_MSG_05;
        printStatus(false);
    } catch (const std::length_error& e) { printStatus(true); }

    printColor(BGWHITE, "\n├─ assigning to larger than its max_size\n");
    try {
        ft::set<int> v(1);
        v.assign(v.max_size() + 1, 42);
        std::cerr << EXCEPT_MSG_06;
        printStatus(false);
    } catch (const std::length_error& e) { printStatus(true); }

    printColor(BGWHITE,
        "\n├─ inserting with more elements than its max_size\n");
    try {
        ft::set<int> v(1);
        v.insert(v.begin(), v.max_size() + 1, 10);
        std::cerr << EXCEPT_MSG_07;
        printStatus(false);
    } catch (const std::length_error& e) { printStatus(true); }
}
