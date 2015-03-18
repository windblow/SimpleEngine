#ifndef __SETESTAPP1_H__
#define __SETESTAPP1_H__

#include <GL/gl.h>

#include <SimpleEngine.h>
#include <SEApplication.h>

class SETestApp1 : public SEApplication<GLfloat>
{
  public:
            SETestApp1() : SEApplication<GLfloat>("SETestApp1") {}
    virtual ~SETestApp1() {}

    virtual void init(int argc, char **argv);

    virtual void update();

    virtual void run();

    virtual void quit();

    virtual void reshape(int width, int height) {}
	virtual void display();
	virtual void key(unsigned char key, int x, int y);
	virtual void pressFuncKey(int key, int x1, int y1) {}
	virtual void releaseFuncKey(int key, int x, int y) {}
	virtual void mouseMotion(int x, int y) {}
	virtual void mousePassiveMotion(int x, int y) {}
	virtual void mouseButton(int button, int state, int x, int y) {}
	virtual void idle() {}
};

#endif // __SETESTAPP1_H__
