/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/utils.hpp"

void printColor(const char* code, const char* message) {
    std::cout << code << message << RESET;
}

void printStatus(int status) {
    static int all;
    static int correct;

    if (status == 1) {
        std::cout << OK;
        ++correct;
    } else if (status == 0) {
        std::cout << KO;
    } else {
        std::cout << '\n' << CYAN << "RESULT " << correct << "/"
            << all << RESET << '\n';
        return;
    }
    ++all;
}

int comp(const int x, const int y) {
    return x - y;
}

void printTime(void) {
    if (!TIME_TEST) {
        return;
    }
    static clock_t          t;
    static double           time_took;

    if (!t) {
        t = clock();
    } else {
        t = clock() - t;
        time_took = static_cast<double>(t) / CLOCKS_PER_SEC;
        std::cout << "\n  TIME TOOK:   " << time_took;
        if (STD) {
            std::cout << "\n  MAX TIME:    " << (time_took * 20) << '\n';
        } else {
            std::cout << "\n\n";
        }
        t = clock();
    }
}
