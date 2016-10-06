#include "SETestApp2.hpp"

void SETestApp2::init(int argc, char **argv)
{

     SEApplication<GLfloat>::init(argc, argv);

     int l1 = rs_->createRO(SEROType::LIGHT_RO, SELightTypes::POINT);
     l_ = dynamic_cast<SEOpenGLPointLight*>(rs_->getLight(l1));
     l_->setTranslation(250,0,0);
     l_->toggle();

     for (int i=0;i<10;++i)
     {
         for (int j=0;j<10;++j)
         {
             for (int k=0;k<10;++k)
             {
                 objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::SPHERE_PRIM);
                 if (objId > 0)
                 {
                     try
                     {
                         SEOpenGLSphere* o_ = dynamic_cast<SEOpenGLSphere*>(rs_->getObject(objId));
                         o_->setSize(15);
                         o_->setStacks(12);
                         o_->setSlices(12);
                         o_->setColori(25*i,25*j,25*k);
                         o_->setTranslation((25*i-128)*2.5,(128-25*j)*2.5,(25*k-128)*2.5);
                     }
                     catch (...)
                     {
                     }
                 }
             }
         }
     }

     ccId = dynamic_cast<SEOpenGLRenderService* >(rs_)->currentCamera;

     try
     {
         c_ = dynamic_cast<SEOpenGLCamera *>(rs_->getCamera(ccId));
         c_->setTranslation(-7.5,7.5,450);
     }
     catch (...)
     {
         c_=NULL;
     }

}

void SETestApp2::run()
{
    t_.reset();
    t_.setAccumulatorPeriod(SEMathUtil<GLfloat>::TWOPI);
    t_.setSpeedFactor(speedFactor);
    SEApplication<GLfloat>::run();
}

void SETestApp2::quit()
{
    SEApplication<GLfloat>::quit();
}

void SETestApp2::update()
{
    const SEVec4<GLfloat> cl(0,0,0,1);
    const SEVec4<GLfloat> cc(-7.5,7.5,0,1);
    const SEVec3<GLfloat> u(0,1,0);

    GLfloat c_interval = t_.getCumulativeInterval();
    GLfloat interval   = t_.getInterval();

    l_->orbit(cl,-u,interval);
    l_->setY(255*cos(4*c_interval));

    if (rotateCam)
    {
        c_->orbit(cc,u,interval);
        c_->rotateByRadians(u,interval);
    }

}

void SETestApp2::display()
{
    SEApplication<GLfloat>::display();
}

void SETestApp2::key(unsigned char key, int x, int y)
{
    switch(key)
     {
        case 'w':
        case 'W':
            if (c_!=NULL) c_->dolly(2);
            break;
        case 's':
        case 'S':
            if (c_!=NULL) c_->dolly(-2);
            break;
        case 'a':
        case 'A':
            if (c_!=NULL) c_->truck(-2);
            break;
        case 'd':
        case 'D':
            if (c_!=NULL) c_->truck(2);
            break;
        case 'e':
        case 'E':
            if (c_!=NULL) c_->panRightByDegrees(2);
            break;
        case 'q':
        case 'Q':
            if (c_!=NULL) c_->panLeftByDegrees(2);
            break;
        case '=':
        case '+':
            if (c_!=NULL) c_->pedestal(2);
            break;
        case '-':
        case '_':
            if (c_!=NULL) c_->pedestal(-2);
            break;
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
        case ' ':
            rotateCam=!rotateCam;
            break;
        default:
            SEApplication<GLfloat>::key(key,x,y);
     }
}
