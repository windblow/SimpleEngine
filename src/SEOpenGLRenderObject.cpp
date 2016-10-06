#include "../inc/SEOpenGLRenderObject.h"
#include "../inc/SEDebugTools.h"

#include <iostream>

USEDUMPFLAG;

void SEOpenGLRenderObject::applyTransformation(const SERenderServiceInternals<GLfloat> &rs) const
{
    DUMPONCE("===SEOpenGLRenderObject::applyTransformation()===");
    //glMatrixMode(GL_MODELVIEW);
    //DUMPONCE("glMatrixMode(GL_MODELVIEW)");
    glPushMatrix();
    DUMPONCE("glPushMatrix()");
    glMultMatrixf(getModelMatrix().transposed().m);
    DUMPONCE("glMultMatrixf({"<<std::endl<<getModelMatrix()<<" })");

}

void SEOpenGLRenderObject::clearTransformation(const SERenderServiceInternals<GLfloat> &rs) const
{
    DUMPONCE("===SEOpenGLRenderObject::clearTransformation()===");
    glPopMatrix();
    DUMPONCE("glPopMatrix()");
}
