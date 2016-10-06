#include "../inc/SEOpenGLCamera.h"
#include "../inc/SEDebugTools.h"

#include <iostream>

USEDUMPFLAG;

void SEOpenGLCamera::setupFrame() const
{
     DUMPONCE("===SEOpenGLCamera::setupFrame()===");
     glMatrixMode(GL_PROJECTION);
     DUMPONCE("glMatrixMode(GL_PROJECTION)");
     glLoadMatrixf(projection.transposed().m);
     DUMPONCE("glLoadMatrixf({"<<std::endl<<projection<<"})");

     glMatrixMode(GL_MODELVIEW);
     DUMPONCE("glMatrixMode(GL_MODELVIEW)");
     glLoadMatrixf(getInverseModelMatrix().transpose().m);
     DUMPONCE("glLoadMatrixf({"<<std::endl<<getInverseModelMatrix()<<"})");
}
