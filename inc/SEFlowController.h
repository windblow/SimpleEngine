#ifndef __SEFLOWCONTROLLER_H__
#define __SEFLOWCONTROLLER_H__

class SEFlowController
{
  public:
    typedef enum {NULL_FC, GLUT_FC, NUM_FC} tFlowController;
  
    virtual void mainLoop() = 0;
};

class SENullFlowController : public SEFlowController
{
  public:
    virtual void mainLoop()
    {
      return;
    }
};

#endif
