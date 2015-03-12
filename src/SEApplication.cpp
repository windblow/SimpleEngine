#include "../inc/SEApplication.h"
#include "../inc/SimpleEngine.h"

SEApplication::~SEApplication()
{
  SimpleEngine::sl()->destroyFlowController();
  SimpleEngine::sl()->destroyWindowManager();
  SimpleEngine::sl()->destroyRenderService();
}

void SEApplication::init(int argc, char **argv)
{
     // Inicialização geral da aplicação
    SimpleEngine::sl()->configRenderService(SERenderService::OPENGL_RS);
    rs_ = SimpleEngine::sl()->getRenderService();

    SimpleEngine::sl()->configWindowManager(SEWindowManager::GLUI_WM, argc, argv);
    wm_ = SimpleEngine::sl()->getWindowManager();

    SimpleEngine::sl()->configFlowController(SEFlowController::GLUT_FC);
    fc_ = SimpleEngine::sl()->getFlowController();
}

void SEApplication::mainLoop()
{
    if (fc_ != NULL) fc_->mainLoop();
}
void SEApplication::quit()
{
     // Procedimentos finais da aplicação
}
