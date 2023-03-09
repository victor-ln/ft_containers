/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/map_tests.hpp"

static void algorithmsTest(void);
static void accessorsTest(void);
static void iteratorTest(void);
static void clearTest(void);
static void sizeTest(void);

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

    s_create_pairs  pairs(15);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());
    {
        ftStrIntMap     M1(p_begin.ft, p_end.ft);
        stdStrIntMap    M2(p_begin.std, p_begin.std + 14);
        {
            printColor(BGWHITE, "\n├─ Different size\n");
            printStatus(ft::lexicographical_compare(M1.begin(), M1.end(),
                                                    M2.begin(), M2.end(), compare()));

            M2.insert(p_begin.std[14]);

            printColor(BGWHITE, "\n├─ Same size and value with pred\n");
            printStatus(!ft::lexicographical_compare(M1.begin(), M1.end(),
                                                M2.begin(), M2.end(), compare()));
        }
        {
            printColor(CYAN, "\n[ EQUAL ]\n");

            printColor(BGWHITE, "\n├─ Same size and value\n");
            printStatus(ft::equal(M1.begin(), M1.end(), M2.begin(), equal()));

            printColor(BGWHITE, "\n├─ Different size\n");
            M1.erase(p_begin.ft[10].first);
            printStatus(!ft::equal(M1.begin(), M1.end(), M2.begin(), equal()));

            printColor(BGWHITE, "\n├─ Different value\n");
            M2.erase(p_begin.ft[11].first);
            printStatus(!ft::equal(M1.begin(), M1.end(), M2.begin(), equal()));
        }
    }
}

static void clearTest(void) {
    printColor(CYAN, "\n[ CLEAR ]\n\n");
    s_create_pairs  pairs(15);
    s_pairs         p_begin(pairs.begin());
    s_pairs         p_end(pairs.end());

    ftStrIntMap     ftM(p_begin.ft, p_end.ft);
    stdStrIntMap    stdM(p_begin.std, p_end.std);

    ftM.clear();
    stdM.clear();
    printStatus(compare_containers(ftM, stdM, equal()));
}

static void iteratorTest(void) {
    s_create_pairs      pairs(15);
    s_pairs             p_begin(pairs.begin());
    s_pairs             p_end(pairs.end());

    ftStrIntMap         ftM(p_begin.ft, p_end.ft);
    stdStrIntMap        stdM(p_begin.std, p_end.std);
    const ftStrIntMap   constFtM(p_begin.ft, p_end.ft);

    printColor(CYAN, "\n[ ITERATORS ]\n");
    {
        printColor(CYAN, "\n  { bidirectional_iterator }\n");
        printColor(CYAN, "\n    ( member functions )\n");

        ftIterator                      ftIt = ftM.begin();
        stdIterator                     stdIt = stdM.begin();

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
            ftIterator   ftCmpIt(ftIt);
            stdIterator  stdCmpIt(stdIt);

            printColor(BGWHITE, "\n├─ iterator::operator==\n");
            printStatus((ftIt == ftCmpIt) == (stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator!=\n");
            printStatus((++ftIt != ftCmpIt) == (++stdIt != stdCmpIt));
        }
    }
    {
        ftReverseIterator               ftIt = ftM.rbegin();
        stdReverseIterator              stdIt = stdM.rbegin();
        std::advance(ftIt, 2);
        std::advance(stdIt, 2);
        {
            ftConstReverseIterator      ftConstIt = constFtM.rbegin();
            stdConstReverseIterator     stdConstIt = stdM.rbegin();
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
            ftReverseIterator   ftCmpIt(ftIt);
            stdReverseIterator  stdCmpIt(stdIt);

            printColor(BGWHITE, "\n├─ iterator::operator==\n");
            printStatus((ftIt == ftCmpIt) == (stdIt == stdCmpIt));

            printColor(BGWHITE, "\n├─ iterator::operator!=\n");
            printStatus((++ftIt != ftCmpIt) == (++stdIt != stdCmpIt));
        }
    }
    {
        printColor(BGWHITE, "\n├─ begin()\n");
        ftConstIterator                 ftConstIt = constFtM.begin();
        ftIterator                      ftIt = ftM.begin();
        stdIterator                     stdIt = stdM.begin();

        printStatus(equal()(*ftIt, *stdIt));
        printStatus(*ftConstIt == *ftIt);
        printStatus(equal()(*ftConstIt, *stdIt));
    }
    {
        printColor(BGWHITE, "\n├─ rbegin()\n");
        ftConstReverseIterator          ftConstIt = constFtM.rbegin();
        ftReverseIterator               ftIt = ftM.rbegin();
        stdReverseIterator              stdIt = stdM.rbegin();

        printStatus(equal()(*ftIt, *stdIt));
        printStatus(*ftConstIt == *ftIt);
        printStatus(equal()(*ftConstIt, *stdIt));
    }
    {
        printColor(BGWHITE, "\n├─ end()\n");
        ftConstIterator                 ftConstIte = --constFtM.end();
        ftIterator                      ftIte = --ftM.end();
        stdIterator                     stdIte = --stdM.end();

        printStatus(equal()(*ftIte, *stdIte));
        printStatus(*ftConstIte == *ftIte);
        printStatus(equal()(*ftConstIte, *stdIte));
    }
    {
        printColor(BGWHITE, "\n├─ rend()\n");
        ftConstReverseIterator          ftConstIte = --constFtM.rend();
        ftReverseIterator               ftIte = --ftM.rend();
        stdReverseIterator              stdIte = --stdM.rend();

        printStatus(equal()(*ftIte, *stdIte));
        printStatus(*ftConstIte == *ftIte);
        printStatus(equal()(*ftConstIte, *stdIte));
    }
}

static void sizeTest(void) {
    s_create_pairs  new_pairs(15);
    s_pairs         p_begin(new_pairs.begin());
    s_pairs         p_end(new_pairs.end());

    printColor(CYAN, "\n[ SIZE ]\n");
    {
        printColor(BGWHITE, "\n├─ size (non-empty map)\n");
        ftStrIntMap             ftM(p_begin.ft, p_end.ft);
        stdStrIntMap            stdM(p_begin.std, p_end.std);

        printStatus(ftM.size() == ftM.size());
    }
    {
        printColor(BGWHITE, "\n├─ size (empty map)\n");
        ftStrIntMap             ftM;
        stdStrIntMap            stdM;

        printStatus(ftM.size() == stdM.size());
    }
}

static void accessorsTest(void) {
    printColor(CYAN, "\n[ ACCESSORS ]\n\n");
    s_create_pairs  new_pairs(15);
    s_pairs         p_begin(new_pairs.begin());
    ftStrIntMap     ftM;
    stdStrIntMap    stdM;

    for (int i = 0; i < 10; i++) {
        ftM[p_begin.ft[i].first] = p_begin.ft[i].second;
        stdM[p_begin.std[i].first] = p_begin.std[i].second;
    }

    printColor(BGWHITE, "\n├─ operator[]\n");
    printStatus(ftM[p_begin.ft[4].first] == stdM[p_begin.std[4].first]);
    ftM[p_begin.ft[4].first] = p_begin.ft[11].second;
    printStatus(ftM[p_begin.ft[4].first] != stdM[p_begin.std[4].first]);
    ftM[p_begin.ft[4].first] = p_begin.ft[4].second;

    printColor(BGWHITE, "\n├─ at()\n");
    printStatus(ftM.at(p_begin.ft[4].first) == stdM.at(p_begin.std[4].first));
    ftM.at(p_begin.ft[4].first) = p_begin.ft[12].second;
    printStatus(ftM.at(p_begin.ft[4].first) != stdM.at(p_begin.std[4].first));
}
