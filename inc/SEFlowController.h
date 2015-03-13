#ifndef __SEFLOWCONTROLLER_H__
#define __SEFLOWCONTROLLER_H__

class SEFlowController
{
  public:
    typedef enum {NULL_FC, GLUT_FC, NUM_FC} tFlowController;

    virtual void mainLoop() = 0;
    virtual void bindCallbacks() = 0;

    tFlowController getType() { return t_; }

    void requestExit() { exit_=true; }

    ~SEFlowController() {}
  protected:
    SEFlowController(tFlowController t) { t_=t; exit_=false; }

    bool exitRequested() { return exit_; }

  private:
    tFlowController t_;
    bool            exit_;
};

class SENullFlowController : public SEFlowController
{
  public:
    SENullFlowController() : SEFlowController(SEFlowController::NULL_FC) {}
    ~SENullFlowController() {}

    virtual void mainLoop() { while (!exitRequested()) int a=1; }
    virtual void bindCallbacks() {}
};

#endif
