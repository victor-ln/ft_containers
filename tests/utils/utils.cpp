/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "../includes/utils.hpp"

void printColor(const char* code, const char* message) {
    std::cout << code << message << RESET;
}

void delay(void) {
    usleep(1000 * DELAY);
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
    delay();
}

int comp(const int x, const int y) {
    return x - y;
}

void printTime(int option) {
    if (!TIME_TEST) {
        return;
    }
    static clock_t          t;
    static double           time_took;
    static double           total_time;

    if (!option) {
        t = clock();
        std::cout << "-----/-----/-----/-----\n\n";
    } else if (option == 1) {
        t = clock() - t;
        time_took = static_cast<double>(t) / CLOCKS_PER_SEC;
        std::cout << "\n  TIME TOOK:   " << time_took;
        if (STD) {
            std::cout << "\n  MAX TIME:    " << (time_took * 20) << '\n';
        } else {
            std::cout << "\n\n";
        }
        total_time += time_took;
    } else {
        std::cout << "\n  TOTAL TIME:  " << total_time << '\n';
    }
}

int*    createArray(std::size_t size) {
    if (size) {
        int *array = new int[size];

        for (std::size_t i = 0; i < size; ++i) {
            array[i] = i;
        }
        std::random_shuffle(array, array + size);
        return array;
    }
    return 0;
}
