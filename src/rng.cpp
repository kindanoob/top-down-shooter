


#include "rng.h"

namespace Rng{
    ///seeding the RNG
    std::mt19937 gen(time(nullptr));
    //int int_in_range(int low, int high, std::mt19937& gen){
    int int_in_range(int low, int high){
        std::uniform_int_distribution<> dis(low, high);
        return dis(gen);
    }
}
