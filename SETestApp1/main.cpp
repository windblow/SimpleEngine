#include <cstdlib>
#include <iostream>

#include <se.h>

#include "SETestApp1.hpp"

int main(int argc, char *argv[])
{
    SimpleEngine::startup(argc, argv);

    SimpleEngine::loadApp(new SETestApp1());

    SimpleEngine::runApp();

    SimpleEngine::quit();

    SYSTEMPAUSE;
    return EXIT_SUCCESS;
}