#ifndef __SEGLUTFLOWCONTROLLER_H__
#define __SEGLUTFLOWCONTROLLER_H__

#include <GL/glut.h>

#include "SEFlowController.h"

class SEGLUTFlowController : public SEFlowController
{
  public:
    virtual void mainLoop() { glutMainLoop(); }
};

#endif
