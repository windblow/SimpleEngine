#include "SETestApp1.hpp"
#include <iostream>


void SETestApp1::init(int argc, char **argv)
{
     SEApplication::init(argc, argv);

     wm_->createNewWindow(1024,768,title_,10,10);

     fc_->bindCallbacks();

}

void SETestApp1::run()
{
    SEEntity ent1("Entity 1");
    SEEntity ent2;
    SEEntity ent3;

    std::cout << ent1.name.str << std::endl;
    std::cout << ent2.name.str << std::endl;
    std::cout << ent3.name.str << std::endl;

    SEApplication::run();
}

void SETestApp1::quit()
{
    SEApplication::quit();
}

void SETestApp1::display()
{

}
void SETestApp1::key(unsigned char key, int x, int y)
{
    switch(key)
     {
        case 27 :
        case 'q':
            quit();
            break;
     }
}
