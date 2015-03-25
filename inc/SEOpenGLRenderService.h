#ifndef __SEOPENGLRENDERSERVICE_H__
#define __SEOPENGLRENDERSERVICE_H__

#include <string>
#include <vector>
#include <map>

#include <GL/gl.h>

#include "SERenderService.h"

struct SEROType;
struct SELightTypes;

class SEOpenGLRenderObject;
class SEOpenGLCamera;
class SEOpenGLLight;

class SEOpenGLRenderService : public SERenderServiceInternals<GLfloat>
{
  friend class SEServiceLocator;

  public:
    const   int      &currentCamera;

    typedef typename std::vector<SEOpenGLRenderObject*>            tROVector;
    typedef typename std::vector<SEOpenGLRenderObject*>::iterator  tROVectorIt;

    typedef typename std::map<uint32_t, SEOpenGLCamera*>           tCamMap;
    typedef typename std::map<uint32_t, SEOpenGLCamera*>::iterator tCamMapIt;

    typedef typename std::map<uint32_t, SEOpenGLLight*>            tLightMap;
    typedef typename std::map<uint32_t, SEOpenGLLight*>::iterator  tLightMapIt;

    virtual int      startup();
    virtual int      shutdown();

    virtual void     renderFrame() const;

    virtual int      createRO(SEROType::tRenderObject t, int t1=-1, int t2=-1, int t3=-1);
    virtual void     destroyRO(uint32_t i);

    virtual void     setCamera(uint32_t c);
    virtual void     activateLight(uint32_t l);
    virtual void     deactivateLight(uint32_t l);

    virtual void     enableLighting() const;
    virtual void     disableLighting() const;

    virtual const SERenderObject<GLfloat> *getObject(uint32_t o) const;
    virtual const SECamera<GLfloat>       *getCamera(uint32_t c) const;
    virtual const SELight<GLfloat>        *getLight(uint32_t l) const;

    virtual SERenderObject<GLfloat> *getObject(uint32_t o);
    virtual SECamera<GLfloat>       *getCamera(uint32_t c);
    virtual SELight<GLfloat>        *getLight(uint32_t l);

  protected:
    SEOpenGLRenderService() : SERenderServiceInternals<GLfloat>(OPENGL_RS), ro_(), c_(), l_(), cc_(-1), currentCamera(cc_) { startup(); }
    virtual ~SEOpenGLRenderService() { shutdown(); }

  private:
            void         startFrame() const;
            void         setupCamera() const;
            void         endFrame() const;

            tROVector ro_;
            tCamMap   c_;
            tLightMap l_;

            int       cc_;
};

#endif
