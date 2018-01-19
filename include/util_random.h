#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>
#include <ctime>



namespace Random{
    std::mt19937 gen(time(nullptr));

    int int_in_range(int low, int high) {
        std::uniform_int_distribution<> dis(low, high);
        return dis(gen);
    }

    double double_in_range(double low, double high) {
        std::uniform_real_distribution<> dis(low, high);
        return dis(gen);
    }

    void test() {
        for(int i = 0; i < 10; ++i) {
            std::cout << int_in_range(1, 100)  << std::endl;
        }
    }
}

#endif // RANDOM_H_
