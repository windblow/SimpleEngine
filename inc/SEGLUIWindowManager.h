#ifndef __SEGLUIWINDOWMANAGER_H__
#define __SEGLUIWINDOWMANAGER_H__

#include <GL/glui.h>
#include <GL/glut.h>

#include "SEWindowManager.h"

class SEGLUIWindowManager : public SEWindowManager
{
  friend class SEServiceLocator;
         
  protected:
         SEGLUIWindowManager();
         SEGLUIWindowManager(int argc, char **argv);
         ~SEGLUIWindowManager();
  
  public:
         virtual long createNewWindow(int w, int h, std::string t = "", int posx = 0, int posy = 0);
         
         virtual void registerDisplayFunction(void (*f)(void));
         virtual void registerReshapeFunction(void (*f) (int, int));
         virtual void registerIdleFunction(void (*f) (void));
};

#endif
