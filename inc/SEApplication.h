#ifndef __SEAPPLICATION_H__
#define __SEAPPLICATION_H__

#include <string>

#include "SESceneManager.h"
#include "SERenderService.h"
#include "SEWindowManager.h"
#include "SEFlowController.h"

/*
 * Classe: SEApplication
 *
 *   Classe base de aplicações desenvolvidas com a Simple Engine
 *
*/

class SEApplication
{
  public:
    ~SEApplication();

    virtual void init(int argc, char **argv);

    virtual void mainLoop();

    virtual void quit();

    SERenderService  *rs() { return rs_; }
    SEWindowManager  *wm() { return wm_; }
    SEFlowController *fc() { return fc_; }

    // Funções virtuais de controle
	virtual void reshape(int width, int height) {}
	virtual void display() {}
	virtual void key(unsigned char key, int x, int y) {}
	virtual void pressFuncKey(int key, int x1, int y1) {}
	virtual void releaseFuncKey(int key, int x, int y) {}
	virtual void mouseMotion(int x, int y) {}
	virtual void mousePassiveMotion(int x, int y) {}
	virtual void mouseButton(int button, int state, int x, int y) {}
	virtual void idle() {}

  protected:
    std::string title_;

    SESceneManager sm_;

    bool run_;

    SERenderService  *rs_;
    SEWindowManager  *wm_;
    SEFlowController *fc_;

    SEApplication(std::string t) : title_(t), run_(true), rs_(NULL), wm_(NULL), fc_(NULL) {}
    SEApplication(const char *t) : title_(t), run_(true), rs_(NULL), wm_(NULL), fc_(NULL) {}


};


#endif
