#ifndef __SEGLUTFLOWCONTROLLER_H__
#define __SEGLUTFLOWCONTROLLER_H__

#include <GL/freeglut.h>

#include "SEFlowController.h"
#include "SimpleEngine.h"

class SEGLUTFlowController : public SEFlowController
{
  public:
    SEGLUTFlowController();
    ~SEGLUTFlowController() {}

    virtual void mainLoop();

    virtual void bindCallbacks();
};

#endif
