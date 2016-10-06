#ifndef __SETESTAPP2_H__
#define __SETESTAPP2_H__

#include <se.h>

class SETestApp2 : public SEApplication<GLfloat>
{
  public:
            SETestApp2() : SEApplication<GLfloat>("SETestApp2"), t_(), c_(NULL), l_(NULL), speedFactor(0.001), rotateCam(false) {}
    virtual ~SETestApp2() {}

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

  private:
    uint32_t            objId;
    uint32_t            ccId;
    SEOpenGLCamera     *c_;
    SEOpenGLPointLight *l_;
    SETimer<GLfloat>    t_;
    GLfloat             speedFactor;
    bool                rotateCam;

//    static tPots pots_[255][255][255];
//    static void  initPots() { for (int i=0;i<255;++i) for (int j=0;j<255;++j) for (int k=0;k<255;++k) pots_[i][j][k]=NULL; }
};

#endif // __SETESTAPP1_H__
