#ifndef __SETESTAPP1_H__
#define __SETESTAPP1_H__

#include <se.h>



class SETestApp1 : public SEApplication<GLfloat>
{
  public:
            SETestApp1();
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

  private:
    int                objId;
    uint32_t           ccId;
    int                l1Id;
    int                l2Id;
//    uint32_t           sphereId;
//    uint32_t           cubeId;
//    uint32_t           coneId;
//    uint32_t           torusId;
//    uint32_t           teapotId;
    SECamera<GLfloat>* c_;
    SEOpenGLPrimitive* prim;
    SEOpenGLDirectionalLight* l1;
    SEOpenGLSpotLight* l2;
    SETimer<GLfloat>   t_;
    GLfloat            speedFactor;
    GLfloat            objSize;
    SEVec3<GLfloat>    rotAxis;
    bool               isWireOn;

    void               switchToSphere();
    void               switchToCube();
    void               switchToCone();
    void               switchToTorus();
    void               switchToTeapot();

    void               destroyCurrentObj();
};

#endif // __SETESTAPP1_H__
