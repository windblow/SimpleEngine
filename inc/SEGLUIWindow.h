#ifndef __SEGLUIWINDOW_H__
#define __SEGLUIWINDOW_H__

#include "SEWindow.h"

#include <GL/glui.h>
#include <GL/glut.h>

#include <string>

class SEGLUIWindow : public SEWindow
{
  friend class SEGLUIWindowManager;
  
  protected:
          SEGLUIWindow(int w, int h, std::string t="", int px=0, int py=0);
          ~SEGLUIWindow() {}

  public:
         virtual void reshape(int nw, int nh);
         virtual void redisplay();
};

#endif
