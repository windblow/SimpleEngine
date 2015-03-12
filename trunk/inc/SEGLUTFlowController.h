#ifndef __SEGLUTFLOWCONTROLLER_H__
#define __SEGLUTFLOWCONTROLLER_H__

#include <GL/glut.h>

#include "SEFlowController.h"

class SEGLUTFlowController : public SEFlowController
{
  public:
    SEGLUTFlowController();
    ~SEGLUTFlowController() {}

    virtual void mainLoop() { glutMainLoop(); }
};

#endif
