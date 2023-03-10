/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/set_tests.hpp"

static void algorithmsTest(void);
static void iteratorTest(void);
static void clearTest(void);
static void sizeTest(void);

int main(void) {
    algorithmsTest();
    iteratorTest();
    clearTest();
    sizeTest();
    printStatus(RESULT);
    return 0;
}

static void algorithmsTest(void) {
    printColor(CYAN, "\n[ LEXICOGRAPHICAL ]\n");

    {
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        ft::set<int> V1(array, array + 9);
        ft::set<int> V2(array, array + 10);
        {
            printColor(BGWHITE, "\n├─ Different size\n");
            printStatus(ft::lexicographical_compare(V1.begin(), V1.end(),
                                                    V2.begin(), V2.end()));
            V1.insert(9);

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
            printStatus(ft::equal(V1.begin(), V1.end(), V2.begin()));

            printColor(BGWHITE, "\n├─ Different size\n");
            V1.erase(9);
            printStatus(ft::equal(V1.begin(), V1.end(), V2.begin()));

            printColor(BGWHITE,
                "\n├─ Same size and different value with pred\n");
            V1.insert(10);
            printStatus(!ft::equal(V1.begin(), V1.end(), V2.begin(), comp));
        }
    }
}

static void clearTest(void) {
    printColor(CYAN, "\n[ CLEAR ]\n\n");
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    ft::set<int>             ftS(array, array + 10);
    std::set<int>            stdS(array, array + 10);

    ftS.clear();
    stdS.clear();
    printStatus(compare_containers(ftS, stdS, compare<int>));
}

static void iteratorTest(void) {
    int a[] = { 1, 2, 3, 4, 5 };
    ft::set<int>                     ftS(a, a + 5);
    std::set<int>                    stdS(a, a + 5);
    const ft::set<int>               constFtS(a, a + 5);

    printColor(CYAN, "\n[ ITERATORS ]\n");
    {
        printColor(CYAN, "\n  { random_access_iterator }\n");
        printColor(CYAN, "\n    ( member functions )\n");
        t_ftIterator                      ftIt = ftS.begin();
        t_stdIterator                     stdIt = stdS.begin();

        printColor(BGWHITE, "\n├─ iterator::operator*\n");
        printStatus(*ftIt == *stdIt);

        printColor(BGWHITE, "\n├─ iterator::operator++\n");
        printStatus(*ftIt++ == *stdIt++);
        printStatus(*ftIt == *stdIt);
        printStatus(*++ftIt == *++stdIt);

        printColor(BGWHITE, "\n├─ iterator::operator--\n");
        printStatus(*ftIt-- == *stdIt--);
        printStatus(*ftIt == *stdIt);
        printStatus(*--ftIt == *--stdIt);

        printColor(BGWHITE, "\n├─ iterator::operator->\n");
        std::set<std::string>        stdStrV;
        ft::set<std::string>         ftStrV;
        stdStrV.insert(std::string("Hello"));
        ftStrV.insert(std::string("Hello"));

        const ft::set<std::string>   ftConstStrV(ftStrV);

        printStatus(stdStrV.begin()->size() == ftStrV.begin()->size());
        printStatus(stdStrV.begin()->size() == ftConstStrV.begin()->size());

        printColor(CYAN, "\n    ( non-member functions )\n");
        {
            t_ftIterator   ftCmpIt(ftIt);
            t_stdIterator  stdCmpIt(stdIt);

            printColor(BGWHITE, "\n├─ iterator::operator==\n");
            printStatus((ftIt == ftCmpIt) == (stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator!=\n");
            printStatus((++ftIt != ftCmpIt) == (++stdIt != stdCmpIt));
        }
    }
    {
        t_ftReverseIterator               ftIt = ftS.rbegin();
        t_stdReverseIterator              stdIt = stdS.rbegin();
        std::advance(ftIt, 2);
        std::advance(stdIt, 2);
        {
            t_ftConstReverseIterator      ftConstIt = constFtS.rbegin();
            t_stdConstReverseIterator     stdConstIt = stdS.rbegin();
            std::advance(ftConstIt, 2);
            std::advance(stdConstIt, 2);

            printColor(CYAN, "\n  { reverse_iterator }\n");
            printColor(CYAN, "\n    ( member functions )\n");
            printColor(BGWHITE, "\n├─ reverse_iterator::base()\n");
            printStatus(*ftIt.base() == *stdIt.base());
            printStatus(*ftConstIt.base() == *stdConstIt.base());

            printColor(BGWHITE, "\n├─ reverse_iterator::operator*\n");
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

        printColor(BGWHITE, "\n├─ reverse_iterator::operator->\n");
        std::set<std::string>        stdStrV;
        ft::set<std::string>         ftStrV;
        stdStrV.insert(std::string("Hello"));
        ftStrV.insert(std::string("Hello"));

        const ft::set<std::string>   ftConstStrV(ftStrV);

        printStatus(stdStrV.rbegin()->size() == ftStrV.rbegin()->size());
        printStatus(stdStrV.rbegin()->size() == ftConstStrV.rbegin()->size());
        printColor(CYAN, "\n    ( non-member functions )\n");
        {
            t_ftReverseIterator   ftCmpIt(ftIt);
            t_stdReverseIterator  stdCmpIt(stdIt);

            printColor(BGWHITE, "\n├─ reverse_iterator::operator==\n");
            printStatus((ftIt == ftCmpIt) == (stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ reverse_iterator::operator!=\n");
            printStatus((++ftIt != ftCmpIt) == (++stdIt != stdCmpIt));
        }
    }
    {
        printColor(BGWHITE, "\n├─ begin()\n");
        t_ftConstIterator                 ftConstIt = constFtS.begin();
        t_ftIterator                      ftIt = ftS.begin();
        t_stdIterator                     stdIt = stdS.begin();

        printStatus(*ftIt == *stdIt);
        printStatus(*ftConstIt == *ftIt);
        printStatus(*ftConstIt == *stdIt);
    }
    {
        printColor(BGWHITE, "\n├─ rbegin()\n");
        t_ftConstReverseIterator          ftConstIt = constFtS.rbegin();
        t_ftReverseIterator               ftIt = ftS.rbegin();
        t_stdReverseIterator              stdIt = stdS.rbegin();

        printStatus(*ftIt == *stdIt);
        printStatus(*ftConstIt == *ftIt);
        printStatus(*ftConstIt == *stdIt);
    }
    {
        printColor(BGWHITE, "\n├─ end()\n");
        t_ftConstIterator                 ftConstIte = --constFtS.end();
        t_ftIterator                      ftIte = --ftS.end();
        t_stdIterator                     stdIte = --stdS.end();

        printStatus(*ftIte == *stdIte);
        printStatus(*ftConstIte == *ftIte);
        printStatus(*ftConstIte == *stdIte);
    }
    {
        printColor(BGWHITE, "\n├─ rend()\n");
        t_ftConstReverseIterator          ftConstIte = --constFtS.rend();
        t_ftReverseIterator               ftIte = --ftS.rend();
        t_stdReverseIterator              stdIte = --stdS.rend();

        printStatus(*ftIte == *stdIte);
        printStatus(*ftConstIte == *ftIte);
        printStatus(*ftConstIte == *stdIte);
    }
}

static void sizeTest(void) {
    printColor(CYAN, "\n[ SIZE ]\n");
    {
        printColor(BGWHITE, "\n├─ size (non-empty set)\n");
        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        ft::set<int>             ftS(array, array + 10);
        std::set<int>            stdS(array, array + 10);

        printStatus(ftS.size() == ftS.size());
    }
    {
        printColor(BGWHITE, "\n├─ size (empty set)\n");
        ft::set<int>             ftS;
        std::set<int>            stdS;

        printStatus(ftS.size() == stdS.size());
    }
}
