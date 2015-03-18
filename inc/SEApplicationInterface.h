#ifndef __SEAPPLICATIONINTERFACE_H__
#define __SEAPPLICATIONINTERFACE_H__

#include "SERenderService.h"
#include "SEWindowManager.h"
#include "SEFlowController.h"

class SEApplicationInterface
{
  public:
    const bool &isRunning;
    const bool &isUpdating;

    virtual void init(int argc, char **argv) = 0;

    virtual void run()=0;
    virtual void update()=0;

    virtual void quit()=0;

    virtual void pause() { update_=!update_; }

    virtual SEWindowManager              *wm() = 0;
    virtual SEFlowController             *fc() = 0;
    virtual SERenderService              *rs() = 0;

    // Funções virtuais de controle
	virtual void reshape(int width, int height) {}
	virtual void display() = 0;
	virtual void key(unsigned char key, int x, int y) {}
	virtual void pressFuncKey(int key, int x1, int y1) {}
	virtual void releaseFuncKey(int key, int x, int y) {}
	virtual void mouseMotion(int x, int y) {}
	virtual void mousePassiveMotion(int x, int y) {}
	virtual void mouseButton(int button, int state, int x, int y) {}
	virtual void idle() {}

    ~SEApplicationInterface() {}

  protected:
    bool run_;
    bool update_;

    SEApplicationInterface() : isRunning(run_), isUpdating(update_) {}
};

#endif // __SEAPPLICATIONINTERFACE_H__
