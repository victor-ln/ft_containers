/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "utils.hpp"

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
