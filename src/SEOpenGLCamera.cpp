#include "../inc/SEOpenGLCamera.h"

void SEOpenGLCamera::setupFrame()
{
     glMatrixMode(GL_PROJECTION);
     glLoadMatrixf(projection.transposed().m);

     glMatrixMode(GL_MODELVIEW);
     glLoadMatrixf(getInverseModelMatrix().transpose().m);
}
