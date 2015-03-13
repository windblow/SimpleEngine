#ifndef __SEOPENGLRENDERSERVICE_H__
#define __SEOPENGLRENDERSERVICE_H__

#include <string>
#include <GL/gl.h>

#include "SERenderService.h"

class SEOpenGLRenderService : public SERenderService
{
  friend class SEServiceLocator;

  public:
    virtual int      startup();
    virtual int      shutdown();

    virtual void     startFrame();
    virtual void     endFrame();

    virtual uint32_t pushComponent(SERenderComponent *c);
    virtual void     popComponent(uint32_t i);


  protected:
    SEOpenGLRenderService() : SERenderService(OPENGL_RS) {}
    ~SEOpenGLRenderService() {}
};

#endif
