#include "../inc/SimpleEngine.h"

#include <iostream>
#include <string>

// Inicialização das variáveis estáticas
SEConfigurationLoader *SimpleEngine::cl_        = NULL;
SEServiceLocator      *SimpleEngine::sl_        = NULL;
SEFlowController      *SimpleEngine::fc_        = NULL;
//
SEApplication         *SimpleEngine::app_       = NULL;
//
int                    SimpleEngine::argc_      = 0;
char                 **SimpleEngine::argv_      = NULL;
//
bool                   SimpleEngine::appLoaded_ = false;
//

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

/*** Funções básicas de inicialização e finalização ***/
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
    app_->run();
}

void SimpleEngine::quitApplication()
{
	if (appLoaded_)
      app_->quit();
}
