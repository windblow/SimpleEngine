#include "SETestApp1.hpp"
#include <iostream>
#include <SERenderService.h>
#include <SERenderObject.h>
#include <SEPrimitive.h>
#include <SEMath.h>


void SETestApp1::init(int argc, char **argv)
{
     SEApplication<GLfloat>::init(argc, argv);

     wm_->createNewWindow(1024,768,title_,10,10);

     fc_->bindCallbacks();

     /** Isso definitivamente não deveria estar direto no app, e sim dentro de uma cena, mas o engine não impede essa utilização **/
     objId = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimitive::TEAPOT_PRIM);

     if (objId > 0)
     try {
       teapot = dynamic_cast<SETeapot<GLfloat>*>(rs_->getObject(objId));
       teapot->setSize(5.0);
     } catch (...) {
       teapot = NULL;
     }
}

void SETestApp1::run()
{
    t_.reset();
    SEApplication<GLfloat>::run();
}

void SETestApp1::quit()
{
    SEApplication<GLfloat>::quit();
}

void SETestApp1::update()
{
    if (teapot!=NULL)
    {
        GLfloat s = 5.0 + sin(t_.getInterval()/speedFactor);
        //std::cout << "expected size: " << s << std::endl;
        teapot->setSize(s);
    }
    if (t_.getInterval() > SEMathUtil<GLfloat>::TWOPI*speedFactor) t_.reset();
}

void SETestApp1::display()
{
    SEApplication<GLfloat>::display();
}

void SETestApp1::key(unsigned char key, int x, int y)
{
    switch(key)
     {
        case 27 :
        case 'q':
            quit();
            break;
        case '+':
            speedFactor *= 1.10;
            break;
        case '-':
            speedFactor /= 1.10;
            break;
     }
}
