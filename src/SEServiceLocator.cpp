#include "../inc/SEServiceLocator.h"
#include "../inc/SimpleEngine.h"
#include "../inc/SEOpenGLRenderService.h"
#include "../inc/SEGLUIWindowManager.h"
#include "../inc/SEGLUTFlowController.h"

void SEServiceLocator::configRenderService(SERenderService::tRenderService s)
{
  switch(s)
  {
    case (SERenderService::OPENGL_RS):  rs_ = new SEOpenGLRenderService(); break;
    case (SERenderService::NULL_RS):    rs_ = new SENullRenderService();   break;
    case (SERenderService::DIRECTX_RS):
    default: return;
  }

  rs_->startup();
}

void SEServiceLocator::configWindowManager(SEWindowManager::tWindowManager s, int argc, char **argv)
{
  switch(s)
  {
    case (SEWindowManager::GLUT_WM):
    case (SEWindowManager::GLUI_WM): wm_ = new SEGLUIWindowManager(argc, argv); break;
    case (SEWindowManager::NULL_WM): wm_ = new SENullWindowManager(); break;
    case (SEWindowManager::GLEW_WM):
    default: return;
  }
}

void SEServiceLocator::configFlowController(SEFlowController::tFlowController s)
{
  // Segurança: não deixa tentar configurar um SEGLUTFlowController antes de configurar um SEGLUTWindowManager
  if (s==SEFlowController::GLUT_FC && wm_==NULL)
    configWindowManager(SEWindowManager::GLUT_WM, SimpleEngine::argc(), SimpleEngine::argv());

  switch(s)
  {
    case (SEFlowController::GLUT_FC): fc_ = new SEGLUTFlowController(); break;
    case (SEFlowController::NULL_FC): fc_ = new SENullFlowController(); break;
    default: return;
  }
}

SERenderService *SEServiceLocator::getRenderService()
{
  if (rs_==NULL)
    configRenderService((SERenderService::tRenderService) SimpleEngine::cl()->getKeyi("tRenderService"));

  return (rs_);
}

SEWindowManager *SEServiceLocator::getWindowManager()
{
  if (wm_==NULL)
    configWindowManager((SEWindowManager::tWindowManager) SimpleEngine::cl()->getKeyi("tWindowManager"),0,NULL);

  return (wm_);
}

SEFlowController *SEServiceLocator::getFlowController()
{
  if (fc_==NULL)
    configFlowController((SEFlowController::tFlowController) SimpleEngine::cl()->getKeyi("tFlowController"));

  return (fc_);
}
