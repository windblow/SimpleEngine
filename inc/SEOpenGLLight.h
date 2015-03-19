#ifndef __SEOPENGLLIGHT_H__
#define __SEOPENGLLIGHT_H__

#include "SEOpenGLRenderObject.h"
#include "SELight.h"

class SEOpenGLLight : public SELight<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLLight(SELightTypes::tLight t) : SELight<GLfloat>(t), SEOpenGLRenderObject(SEROType::LIGHT_RO), SERenderObject<GLfloat>(SEROType::LIGHT_RO) {}
    virtual ~SEOpenGLLight() {}
};

#endif // __SEOPENGLLIGHT_H__
