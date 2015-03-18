#ifndef __SEOPENGLRENDEROBJECT_H__
#define __SEOPENGLRENDEROBJECT_H__

#include <GL/gl.h>

#include "SERenderObject.h"

class SEOpenGLRenderObject : public SERenderObject<GLfloat>
{
  public:
    ~SEOpenGLRenderObject() {}

    virtual void            draw() = 0;

  protected:
    SEOpenGLRenderObject(SEROType::tRenderObject rt) : SERenderObject<GLfloat>(rt) {}

    virtual void            applyTransformation() { glMatrixMode(GL_MODELVIEW); glPushMatrix(); glMultMatrixf(getTransformationMatrix().transposed().m); }

};

#endif // __SEOPENGLRENDEROBJECT_H__
