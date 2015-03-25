#ifndef __SEOPENGLRENDEROBJECT_H__
#define __SEOPENGLRENDEROBJECT_H__

#include <GL/gl.h>

#include "SERenderObject.h"
#include "SERenderService.h"

class SEOpenGLRenderObject : public virtual SERenderObject<GLfloat>
{
  friend class SEOpenGLRenderService;

  protected:
    SEOpenGLRenderObject(SEROType::tRenderObject t) : SERenderObject<GLfloat>(t) {}
    virtual ~SEOpenGLRenderObject() {}

    virtual void            applyTransformation() const;
    virtual void            applyLighting(const SERenderServiceInternals<GLfloat> &rs) const;
    virtual void            clearLighting(const SERenderServiceInternals<GLfloat> &rs) const;
    virtual void            clearTransformation() const;

};

#endif // __SEOPENGLRENDEROBJECT_H__
