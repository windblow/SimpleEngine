#include "../inc/SimpleEngine.h"

#include <iostream>
#include <string>

// Inicializa��o das vari�veis est�ticas

bool SimpleEngine::appLoaded_ = false;

SEConfigurationLoader *SimpleEngine::cl_ = NULL;
SEServiceLocator *SimpleEngine::sl_ = NULL;

SEApplication *SimpleEngine::app_ = NULL;

int SimpleEngine::argc_ = 0;
char **SimpleEngine::argv_ = NULL;

void SimpleEngine::startup(int argc, char **argv)
{
  SimpleEngine::argc_ = argc;
  SimpleEngine::argv_ = argv;
  
  init();
}
  
void SimpleEngine::loadApp(SEApplication *app)
{
  if (appLoaded())
    unloadApp();
  
  app_=app;
  
  appLoaded_=true;
  
  app_->init(argc_, argv_);
}

void SimpleEngine::unloadApp()
{
  if (appLoaded_)
  {
    app_->quit();
    appLoaded_=false;
    delete(app_);
    app_=NULL;
  }
}

/*** Fun��es b�sicas de inicializa��o e finaliza��o ***/
void SimpleEngine::init()
{
    cl_ = new SEConfigurationLoader("se.ini");
    sl_ = new SEServiceLocator();
}

void SimpleEngine::quit()
{
    unloadApp();
    
    delete(cl_);
    delete(sl_);
}

void SimpleEngine::reset()
{
	quit();
	init();
}

void SimpleEngine::runApp()
{
  if (appLoaded_)
    app_->mainLoop();
}

void SimpleEngine::quitProgram()
{
	//TODO: finaliza��o correta de vari�veis de aplica��o
	quit();
	exit(0);
}
