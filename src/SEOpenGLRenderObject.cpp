#include "../inc/SEOpenGLRenderObject.h"

#include <iostream>

#define DUMPONCE(x) if (dumpOnce) std::cout << x << std::endl

extern bool dumpOnce;

void SEOpenGLRenderObject::applyTransformation() const
{
    glPushMatrix();
    DUMPONCE("glPushMatrix()");
    glMatrixMode(GL_MODELVIEW);
    DUMPONCE("glMatrixMode(GL_MODELVIEW)");
    glPushMatrix();
    DUMPONCE("glPushMatrix()");
    glMultMatrixf(getModelMatrix().transposed().m);
    DUMPONCE("glMultMatrixf({"<<std::endl<<getModelMatrix()<<" })");
}

void SEOpenGLRenderObject::applyLighting(const SERenderServiceInternals<GLfloat> &rs) const
{
    rs.enableLighting();
}

void SEOpenGLRenderObject::clearLighting(const SERenderServiceInternals<GLfloat> &rs) const
{
    rs.disableLighting();
}

void SEOpenGLRenderObject::clearTransformation() const
{
    glPopMatrix();
    DUMPONCE("glPopMatrix()");
}
