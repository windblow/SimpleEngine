#include "../inc/SEOpenGLCamera.h"

#include <iostream>

#define DUMPONCE(x) if (dumpOnce) std::cout << x << std::endl

extern bool dumpOnce;

void SEOpenGLCamera::setupFrame() const
{
     glMatrixMode(GL_PROJECTION);
     DUMPONCE("glMatrixMode(GL_PROJECTION)");
     glLoadMatrixf(projection.transposed().m);
     DUMPONCE("glLoadMatrixf({"<<std::endl<<projection<<"})");

     glMatrixMode(GL_MODELVIEW);
     DUMPONCE("glMatrixMode(GL_MODELVIEW)");
     glLoadMatrixf(getInverseModelMatrix().transpose().m);
     DUMPONCE("glLoadMatrixf({"<<std::endl<<getInverseModelMatrix()<<"})");
}
