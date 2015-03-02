#ifndef __SEOPENGLRENDERSERVICE_H__
#define __SEOPENGLRENDERSERVICE_H__

#include <string>
#include <GL/gl.h>

#include "SERenderService.h"

class SEOpenGLRenderService : public SERenderService
{
  friend class SEServiceLocator;
  
  protected:
    SEOpenGLRenderService() : SERenderService(OPENGL_RS) {}
    ~SEOpenGLRenderService() {}
  
  public:
    int startup();
    int shutdown();
    
    void startFrame();
    void endFrame();
};

#endif
