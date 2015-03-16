#include "../inc/SEGLUIWindowManager.h"
#include "../inc/SEGLUIWindow.h"

SEGLUIWindowManager::SEGLUIWindowManager()
  : SEWindowManager(SEWindowManager::GLUI_WM)
{
}

SEGLUIWindowManager::SEGLUIWindowManager(int argc, char **argv)
  : SEWindowManager(SEWindowManager::GLUI_WM, argc, argv)
{
  glutInit(&argc, argv);
}

long SEGLUIWindowManager::createNewWindow(int w, int h, std::string t, int posx, int posy)
{
  SEGLUIWindow *nw = new SEGLUIWindow(w, h, t, posx, posy);
  currentId_ = nw->getId();
  w_[currentId_] = nw;
  
  return (currentId_);
}

void SEGLUIWindowManager::registerDisplayFunction(void (*f)(void))
{
  glutDisplayFunc(f);
}

void SEGLUIWindowManager::registerReshapeFunction(void (*f) (int, int))
{
  GLUI_Master.set_glutReshapeFunc(f);
}

void SEGLUIWindowManager::registerIdleFunction(void (*f) (void))
{
  GLUI_Master.set_glutIdleFunc(f);
}
