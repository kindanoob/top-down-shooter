#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <ctime>



namespace Random{
    //std::random_device rd;
    std::mt19937 gen(time(nullptr));
    //gen.seed(1);
    //gen.seed(time(nullptr));

    int int_in_range(int low, int high){
        std::uniform_int_distribution<> dis(low, high);
        return dis(gen);
    }

    double double_in_range(double low, double high){
        std::uniform_real_distribution<> dis(low, high);
        return dis(gen);
    }

    void test(){
        for(int i = 0; i < 10; ++i){
            std::cout << int_in_range(1, 100)  << std::endl;
            //std::cout << double_in_range(0, 1)  << std::endl;
        }
    }
}
#endif // RANDOM_H
