#ifndef __SEOPENGLCAMERA_H__
#define __SEOPENGLCAMERA_H__

#include "SEOpenGLRenderObject.h"
#include "SECamera.h"

class SEOpenGLCamera : public SECamera<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLCamera() : SERenderObject<GLfloat>(SEROType::CAMERA_RO), SECamera<GLfloat>(), SEOpenGLRenderObject(SEROType::CAMERA_RO) {}
    SEOpenGLCamera(SECameraType::tCamera t) : SERenderObject<GLfloat>(SEROType::CAMERA_RO), SECamera<GLfloat>(t), SEOpenGLRenderObject(SEROType::CAMERA_RO) {}
    virtual ~SEOpenGLCamera() {}

    virtual void setupFrame() const;

    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const {}
};

#endif // __SEOPENGLCAMERA_H__
