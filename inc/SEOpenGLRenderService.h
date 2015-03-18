#ifndef __SEOPENGLRENDERSERVICE_H__
#define __SEOPENGLRENDERSERVICE_H__

#include "SERenderService.h"

#include <string>
#include <GL/gl.h>

#include <vector>

class SEOpenGLRenderService : public SERenderServiceInternals<GLfloat>
{
  friend class SEServiceLocator;

  public:
    typedef typename std::vector<SERenderObject<GLfloat>*>           tROVector;
    typedef typename std::vector<SERenderObject<GLfloat>*>::iterator tROVectorIt;

    typedef std::vector<SECamera*>                                   tCamVector;
    typedef std::vector<SECamera*>::iterator                         tCamVectorIt;

    typedef std::vector<SELight*>                                    tLightVector;
    typedef std::vector<SELight*>::iterator                          tLightVectorIt;

    virtual int      startup();
    virtual int      shutdown();

    virtual void     renderFrame();

    virtual uint32_t pushComponent(SERenderComponent *c);
    virtual void     popComponent(uint32_t i);

    virtual void     setCamera(uint32_t c);
    virtual void     activateLight(uint32_t l);
    virtual void     deactivateLight(uint32_t l);

    virtual SERenderObject<GLfloat> *getObject(uint32_t o);
  protected:
    SEOpenGLRenderService() : SERenderServiceInternals<GLfloat>(OPENGL_RS), ro_(), c_(), l_(), cc_(-1) {}
    virtual ~SEOpenGLRenderService() {}

  private:
            void         startFrame();
            void         endFrame();

            tROVector    ro_;
            tCamVector   c_;
            tLightVector l_;

            int          cc_;
};

#endif
