#include "SETestApp1.hpp"

#include <iostream>


USEDUMPFLAG;

SETestApp1::SETestApp1() :
     SEApplication<GLfloat>("SETestApp1"),
     speedFactor(0.001),
     objSize(5.0),
     c_(NULL),
     prim(NULL),
     l1(NULL),
     l2(NULL),
     rotAxis(0,1,0),
     objId(-1),
     ccId(-1),
     l1Id(-1),
     l2Id(-1),
     isWireOn(false)
{

}

void SETestApp1::init(int argc, char **argv)
{
     SEApplication<GLfloat>::init(argc, argv);

     switchToSphere();

     ccId = rs_->currentCamera;

     l1Id = rs_->createRO(SEROType::LIGHT_RO, SELightTypes::DIRECTIONAL);
     l2Id = rs_->createRO(SEROType::LIGHT_RO, SELightTypes::SPOT);

     l1 = dynamic_cast<SEOpenGLDirectionalLight*>(rs_->getLight(l1Id));
     l1->setDirection(1,-1,-1);
     l1->setIntensity(0.8);
     l1->toggle();

     l2 = dynamic_cast<SEOpenGLSpotLight*>(rs_->getLight(l2Id));
     l2->setDirection(0,0,-1);
     l2->setTranslation(0,-5,10);
     l2->rotateByDegrees(1,0,0,30);
     l2->setIntensity(0.6);
     l2->toggle();

     try
     {
         c_ = dynamic_cast<SECamera<GLfloat> *>(rs_->getCamera(ccId));
         c_->setTranslation(0,0,20);
     }
     catch (...)
     {
         c_=NULL;
     }
}

void SETestApp1::run()
{
    t_.reset();
    t_.setAccumulatorPeriod(SEMathUtil<GLfloat>::TWOPI);
    t_.setSpeedFactor(speedFactor);
    SEApplication<GLfloat>::run();
}

void SETestApp1::quit()
{
    SEApplication<GLfloat>::quit();
}

void SETestApp1::update()
{
    if (objId>=0)
    {
        /**/
        GLfloat s = sin(t_.getCumulativeInterval());
        rs_->getObject(objId)->setScale(0.75 + s/4);
        /**/
        rs_->getObject(objId)->rotateByRadians(rotAxis, t_.getInterval());
        prim->setColor(s/2,1-s,-s/2);
        /**/
    }
}

void SETestApp1::display()
{
    SEApplication<GLfloat>::display();
}

void SETestApp1::key(unsigned char key, int x, int y)
{
    switch(key)
     {
        case '.':
        case '>':
            speedFactor *= 1.1;
            t_.setSpeedFactor(speedFactor);
            break;
        case ',':
        case '<':
            speedFactor /= 1.1;
            t_.setSpeedFactor(speedFactor);
            break;
        case 'w':
        case 'W':
            if (c_!=NULL) c_->translateBy(0,0,-2);
            break;
        case 's':
        case 'S':
            if (c_!=NULL) c_->translateBy(0,0,2);
            break;
        case 'a':
        case 'A':
            if (c_!=NULL) c_->translateBy(-2,0,0);
            break;
        case 'd':
        case 'D':
            if (c_!=NULL) c_->translateBy(2,0,0);
            break;
        case '=':
        case '+':
            if (c_!=NULL) c_->translateBy(0,2,0);
            break;
        case '-':
        case '_':
            if (c_!=NULL) c_->translateBy(0,-2,0);
            break;
        case '1':
            switchToSphere();
            break;
        case '2':
            switchToCube();
            break;
        case '3':
            switchToCone();
            break;
        case '4':
            switchToTorus();
            break;
        case '5':
            switchToTeapot();
            break;
        case ' ':
            isWireOn=!isWireOn;
            if (prim!=NULL) prim->toggleState();
            break;
        case 'L':
            l1->toggle();
            break;
        case 'l':
            l2->toggle();
            break;
        case '0':
            DUMPFLAG(true);
            break;
        default:
            SEApplication<GLfloat>::key(key,x,y);
     }
}

void SETestApp1::switchToSphere()
{
    SEQuaternion<GLfloat> tr;

    if (prim!=NULL) tr=prim->rotation;

    destroyCurrentObj();

    objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::SPHERE_PRIM);

    prim = dynamic_cast<SEOpenGLPrimitive*>(rs_->getObject(objId));

    try
    {
        SEOpenGLSphere* s = dynamic_cast<SEOpenGLSphere*>(prim);
        s->setRadius(objSize);
        s->setSlices(16);
        s->setStacks(16);
    } catch (...) {
    }

    if (isWireOn) prim->toggleState();

    prim->setRotation(tr);
}

void SETestApp1::switchToCube()
{
    SEQuaternion<GLfloat> tr;

    if (prim!=NULL) tr=prim->rotation;

    destroyCurrentObj();

    objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::CUBE_PRIM);

    prim = dynamic_cast<SEOpenGLPrimitive*>(rs_->getObject(objId));

    dynamic_cast<SEOpenGLCube*>(prim)->setSize(objSize);

    if (isWireOn) prim->toggleState();

    prim->setRotation(tr);
}

void SETestApp1::switchToCone()
{
    SEQuaternion<GLfloat> tr;

    if (prim!=NULL) tr=prim->rotation;

    destroyCurrentObj();

    objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::CONE_PRIM);

    prim = dynamic_cast<SEOpenGLPrimitive*>(rs_->getObject(objId));

    try
    {
        SEOpenGLCone* c= dynamic_cast<SEOpenGLCone*>(prim);
        c->setHeight(objSize);
        c->setBase(3*objSize/4);
        c->setSlices(16);
        c->setStacks(16);
    } catch (...) {
    }

    if (isWireOn) prim->toggleState();

    prim->setRotation(tr);
}

void SETestApp1::switchToTorus()
{
    SEQuaternion<GLfloat> tr;

    if (prim!=NULL) tr=prim->rotation;

    destroyCurrentObj();

    objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::TORUS_PRIM);

    prim = dynamic_cast<SEOpenGLPrimitive*>(rs_->getObject(objId));

    try
    {
        SEOpenGLTorus *t = dynamic_cast<SEOpenGLTorus*>(prim);
        t->setInnerR(objSize-2);
        t->setOuterR(objSize);
        t->setSides(16);
        t->setRings(16);
    } catch (...) {
    }

    if (isWireOn) prim->toggleState();

    prim->setRotation(tr);
}

void SETestApp1::switchToTeapot()
{
    SEQuaternion<GLfloat> tr;

    if (prim!=NULL) tr=prim->rotation;

    destroyCurrentObj();

    objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::TEAPOT_PRIM);

    prim = dynamic_cast<SEOpenGLPrimitive*>(rs_->getObject(objId));

    dynamic_cast<SEOpenGLTeapot*>(prim)->setSize(objSize);

    if (isWireOn) prim->toggleState();

    prim->setRotation(tr);
}

void SETestApp1::destroyCurrentObj()
{
    if (objId >= 0)
    {
        rs_->destroyRO(objId);
        objId=-1;
    }
}
