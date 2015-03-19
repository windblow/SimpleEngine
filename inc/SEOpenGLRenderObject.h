#ifndef __SEOPENGLRENDEROBJECT_H__
#define __SEOPENGLRENDEROBJECT_H__

#include <GL/gl.h>

#include "SERenderObject.h"

class SEOpenGLRenderService;

class SEOpenGLRenderObject : public virtual SERenderObject<GLfloat>
{
  friend class SEOpenGLRenderService;

  public:
    class Builder;

    virtual void draw() const =0;

  protected:
    SEOpenGLRenderObject(SEROType::tRenderObject t) : SERenderObject<GLfloat>(t) {}
    virtual ~SEOpenGLRenderObject() {}

    virtual void applyTransformation() { glMatrixMode(GL_MODELVIEW); glPushMatrix(); glMultMatrixf(getModelMatrix().transposed().m); }

};

class SEOpenGLRenderObject::Builder : public SERenderObject<GLfloat>::Builder
{
  public:
    virtual SERenderObject<GLfloat> *build() = 0;
};

#endif // __SEOPENGLRENDEROBJECT_H__
