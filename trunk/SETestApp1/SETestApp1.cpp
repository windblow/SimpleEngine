#include <iostream>

#include "SETestApp1.hpp"

void SETestApp1::init(int argc, char **argv)
{
     SEApplication::init(argc, argv);
     
     //wm_->createNewWindow(640,480,title_,10,10);

}

void SETestApp1::mainLoop()
{
     std::cout << "Teste deu certo" << std::endl;
}

void SETestApp1::quit()
{
}
