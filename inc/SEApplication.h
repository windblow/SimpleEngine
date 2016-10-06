#ifndef __SEAPPLICATION_H__
#define __SEAPPLICATION_H__

#include <string>
#include <iostream>

#include "SEApplicationInterface.h"
#include "SESceneManager.h"
#include "SimpleEngine.h"

/*
 * Classe: SEApplication
 *
 *   Classe base de aplicações desenvolvidas com a Simple Engine
 *
*/

template <class T> class SEApplication : public SEApplicationInterface
{
  public:

    virtual void init(int argc, char **argv);

    virtual void run();

    virtual void quit();

    virtual ~SEApplication();

    virtual SERenderService              *rs() { return static_cast<SERenderService *>(rs_); }
    virtual SEWindowManager              *wm() { return wm_; }
    virtual SEFlowController             *fc() { return fc_; }

	virtual void display() { if (rs_!=NULL) rs_->renderFrame(); }
	virtual void idle()    { this->update(); this->display(); }

	virtual void key(unsigned char key, int x, int y);

  protected:
    std::string title_;

    SESceneManager sm_;

    SERenderServiceInternals<T>  *rs_;
    SEWindowManager              *wm_;
    SEFlowController             *fc_;

    SEApplication(std::string t) :
        SEApplicationInterface(), title_(t), rs_(NULL), wm_(NULL), fc_(NULL)
    {}

    SEApplication(const char *t) :
        SEApplicationInterface(), title_(t), rs_(NULL), wm_(NULL), fc_(NULL)
    {}


};

// Declara os templates de função no header pois não há compilação de .cpp para classes template

template <class T> SEApplication<T>::~SEApplication()
{
    SimpleEngine::sl()->destroyFlowController();
    SimpleEngine::sl()->destroyWindowManager();
    SimpleEngine::sl()->destroyRenderService();
}

template <class T> void SEApplication<T>::init(int argc, char **argv)
{
     // Inicialização geral da aplicação
    SimpleEngine::sl()->configRenderService(SERenderService::OPENGL_RS);
    if (SimpleEngine::sl()->getRenderService()->RStype == SERenderService::OPENGL_RS)
      rs_ = static_cast<SERenderServiceInternals<T> *>(SimpleEngine::sl()->getRenderService());
    else
      rs_ = NULL;

    SimpleEngine::sl()->configWindowManager(SEWindowManager::GLUI_WM, argc, argv);
    wm_ = SimpleEngine::sl()->getWindowManager();

    SimpleEngine::sl()->configFlowController(SEFlowController::GLUT_FC);
    fc_ = SimpleEngine::sl()->getFlowController();

    // Cria a janela e associa os callbacks
    wm_->createNewWindow(800,600,title_,10,10);
    fc_->bindCallbacks();
}

template <class T> void SEApplication<T>::run()
{
    run_=true;
    if (fc_ != NULL) fc_->mainLoop();
}

template <class T> void SEApplication<T>::quit()
{
     run_=false;
}

template <class T> void SEApplication<T>::key(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        this->quit();
        break;
    }
}

#endif
