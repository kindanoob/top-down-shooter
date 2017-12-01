#include <iostream>
#include <list>
#include <random>
#include <new>


#include <SFML/Graphics.hpp>

#include "application.h"
//#include "resource_holder.h"
//#include "texture_manager.h"
#include "util_random.h"


int main()
{
    //srand(time(nullptr));
    Application *app = new Application();
    //Application app = Singleton::get_instance();
    app -> run();
    delete app;
    //Random::test();
    std::cout << "Hello world!" << std::endl;
    return 0;
}
