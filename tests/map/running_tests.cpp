/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/containers/map_tests.hpp"

static void algorithmsTest(void);
static void accessorsTest(void);
static void iteratorTest(void);
static void clearTest(void);
static void sizeTest(void);

const s_create_pairs  g_pairs(15);
const s_pairs         g_pair_begin(g_pairs.begin());
const s_pairs         g_pair_end(g_pairs.end());

int main(void) {
    algorithmsTest();
    accessorsTest();
    iteratorTest();
    clearTest();
    sizeTest();
    printStatus(RESULT);
    return 0;
}

static void algorithmsTest(void) {
    printColor(CYAN, "\n[ LEXICOGRAPHICAL ]\n");
    {
        t_ftStrIntMap   M1(g_pair_begin.ft, g_pair_end.ft);
        t_stdStrIntMap  M2(g_pair_begin.std, g_pair_begin.std + 14);
        {
            printColor(BGWHITE, "\n├─ Different size\n");
            printStatus(ft::lexicographical_compare(M1.begin(), M1.end(),
                                                    M2.begin(), M2.end(),
                                                    compare()));

            M2.insert(g_pair_begin.std[14]);

            printColor(BGWHITE, "\n├─ Same size and value with pred\n");
            printStatus(!ft::lexicographical_compare(M1.begin(), M1.end(),
                                                     M2.begin(), M2.end(),
                                                     compare()));
        }
        {
            printColor(CYAN, "\n[ EQUAL ]\n");

            printColor(BGWHITE, "\n├─ Same size and value\n");
            printStatus(ft::equal(M1.begin(), M1.end(), M2.begin(), equal()));

            printColor(BGWHITE, "\n├─ Different size\n");
            M1.erase(g_pair_begin.ft[10].first);
            printStatus(!ft::equal(M1.begin(), M1.end(), M2.begin(), equal()));

            printColor(BGWHITE, "\n├─ Different value\n");
            M2.erase(g_pair_begin.ft[11].first);
            printStatus(!ft::equal(M1.begin(), M1.end(), M2.begin(), equal()));
        }
    }
}

static void clearTest(void) {
    printColor(CYAN, "\n[ CLEAR ]\n\n");

    t_ftStrIntMap   ftM(g_pair_begin.ft, g_pair_end.ft);
    t_stdStrIntMap  stdM(g_pair_begin.std, g_pair_end.std);

    ftM.clear();
    stdM.clear();
    printStatus(compare_containers(ftM, stdM, equal()));
}

static void iteratorTest(void) {
    t_ftStrIntMap   ftM(g_pair_begin.ft, g_pair_end.ft);
    t_stdStrIntMap  stdM(g_pair_begin.std, g_pair_end.std);
    const t_ftStrIntMap constFtM(g_pair_begin.ft, g_pair_end.ft);

    printColor(CYAN, "\n[ ITERATORS ]\n");
    {
        printColor(CYAN, "\n  { bidirectional_iterator }\n");
        printColor(CYAN, "\n    ( member functions )\n");

        t_ftIterator                      ftIt = ftM.begin();
        t_stdIterator                     stdIt = stdM.begin();

        printColor(BGWHITE, "\n├─ iterator::operator*\n");
        printStatus(equal()(*ftIt, *stdIt));

        printColor(BGWHITE, "\n├─ iterator::operator++\n");
        printStatus(equal()(*ftIt++, *stdIt++));
        printStatus(equal()(*ftIt, *stdIt));
        printStatus(equal()(*++ftIt, *++stdIt));

        printColor(BGWHITE, "\n├─ iterator::operator--\n");
        printStatus(equal()(*ftIt--, *stdIt--));
        printStatus(equal()(*ftIt, *stdIt));
        printStatus(equal()(*--ftIt, *--stdIt));

        printColor(BGWHITE, "\n├─ iterator::operator->\n");

        printStatus(ftIt->first == stdIt->first);
        printStatus(ftIt->first == constFtM.begin()->first);

        printStatus(ftIt->second == stdIt->second);
        printStatus(ftIt->second == constFtM.begin()->second);

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
        t_ftReverseIterator               ftIt = ftM.rbegin();
        t_stdReverseIterator              stdIt = stdM.rbegin();
        std::advance(ftIt, 2);
        std::advance(stdIt, 2);
        {
            t_ftConstReverseIterator      ftConstIt = constFtM.rbegin();
            t_stdConstReverseIterator     stdConstIt = stdM.rbegin();
            std::advance(ftConstIt, 2);
            std::advance(stdConstIt, 2);

            printColor(CYAN, "\n  { reverse_iterator }\n");
            printColor(CYAN, "\n    ( member functions )\n");
            printColor(BGWHITE, "\n├─ reverse_iterator::base()\n");
            printStatus(equal()(*ftIt.base(), *stdIt.base()));
            printStatus(equal()(*ftConstIt.base(), *stdConstIt.base()));

            printColor(BGWHITE, "\n├─ reverse_iterator::operator*\n");
            printStatus(equal()(*ftIt, *stdIt));
        }

        printColor(BGWHITE, "\n├─ reverse_iterator::operator++\n");
        printStatus(equal()(*ftIt++, *stdIt++));
        printStatus(equal()(*ftIt, *stdIt));
        printStatus(equal()(*++ftIt, *++stdIt));

        printColor(BGWHITE, "\n├─ reverse_iterator::operator--\n");
        printStatus(equal()(*ftIt--, *stdIt--));
        printStatus(equal()(*ftIt, *stdIt));
        printStatus(equal()(*--ftIt, *--stdIt));

        printColor(BGWHITE, "\n├─ reverse_iterator::operator->\n");
        printStatus(ftIt->first == stdIt->first);
        printStatus(ftM.begin()->first == stdM.begin()->first);
        printStatus(ftM.begin()->first == constFtM.begin()->first);

        printStatus(ftIt->second == stdIt->second);
        printStatus(ftM.begin()->second == stdM.begin()->second);
        printStatus(ftM.begin()->second == constFtM.begin()->second);

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
        t_ftConstIterator                 ftConstIt = constFtM.begin();
        t_ftIterator                      ftIt = ftM.begin();
        t_stdIterator                     stdIt = stdM.begin();

        printStatus(equal()(*ftIt, *stdIt));
        printStatus(*ftConstIt == *ftIt);
        printStatus(equal()(*ftConstIt, *stdIt));
    }
    {
        printColor(BGWHITE, "\n├─ rbegin()\n");
        t_ftConstReverseIterator          ftConstIt = constFtM.rbegin();
        t_ftReverseIterator               ftIt = ftM.rbegin();
        t_stdReverseIterator              stdIt = stdM.rbegin();

        printStatus(equal()(*ftIt, *stdIt));
        printStatus(*ftConstIt == *ftIt);
        printStatus(equal()(*ftConstIt, *stdIt));
    }
    {
        printColor(BGWHITE, "\n├─ end()\n");
        t_ftConstIterator                 ftConstIte = --constFtM.end();
        t_ftIterator                      ftIte = --ftM.end();
        t_stdIterator                     stdIte = --stdM.end();

        printStatus(equal()(*ftIte, *stdIte));
        printStatus(*ftConstIte == *ftIte);
        printStatus(equal()(*ftConstIte, *stdIte));
    }
    {
        printColor(BGWHITE, "\n├─ rend()\n");
        t_ftConstReverseIterator          ftConstIte = --constFtM.rend();
        t_ftReverseIterator               ftIte = --ftM.rend();
        t_stdReverseIterator              stdIte = --stdM.rend();

        printStatus(equal()(*ftIte, *stdIte));
        printStatus(*ftConstIte == *ftIte);
        printStatus(equal()(*ftConstIte, *stdIte));
    }
}

static void sizeTest(void) {
    printColor(CYAN, "\n[ SIZE ]\n");
    {
        printColor(BGWHITE, "\n├─ size (non-empty map)\n");
        t_ftStrIntMap   ftM(g_pair_begin.ft, g_pair_end.ft);
        t_stdStrIntMap  stdM(g_pair_begin.std, g_pair_end.std);

        printStatus(ftM.size() == ftM.size());
    }
    {
        printColor(BGWHITE, "\n├─ size (empty map)\n");
        t_ftStrIntMap   ftM;
        t_stdStrIntMap  stdM;

        printStatus(ftM.size() == stdM.size());
    }
}

static void accessorsTest(void) {
    printColor(CYAN, "\n[ ACCESSORS ]\n\n");
    t_ftStrIntMap   ftM;
    t_stdStrIntMap  stdM;

    for (int i = 0; i < 10; i++) {
        ftM[g_pair_begin.ft[i].first] = g_pair_begin.ft[i].second;
        stdM[g_pair_begin.std[i].first] = g_pair_begin.std[i].second;
    }

    printColor(BGWHITE, "\n├─ operator[]\n");
    printStatus(ftM[g_pair_begin.ft[4].first] == stdM[g_pair_begin.std[4].first]);
    ftM[g_pair_begin.ft[4].first] = g_pair_begin.ft[11].second;
    printStatus(ftM[g_pair_begin.ft[4].first] != stdM[g_pair_begin.std[4].first]);
    ftM[g_pair_begin.ft[4].first] = g_pair_begin.ft[4].second;

    printColor(BGWHITE, "\n├─ at()\n");
    printStatus(ftM.at(g_pair_begin.ft[4].first) == stdM.at(g_pair_begin.std[4].first));
    ftM.at(g_pair_begin.ft[4].first) = g_pair_begin.ft[12].second;
    printStatus(ftM.at(g_pair_begin.ft[4].first) != stdM.at(g_pair_begin.std[4].first));
}
