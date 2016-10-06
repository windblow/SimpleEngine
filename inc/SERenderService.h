#ifndef __SERENDERSERVICE_H__
#define __SERENDERSERVICE_H__

#include "SERenderObject.h"
#include "SECamera.h"
#include "SELight.h"

#include <string>
#include <vector>

class SEServiceLocator;
class SERenderComponent;

class SERenderService
{
  friend class SEServiceLocator;

  public:
    typedef enum { OPENGL_RS, DIRECTX_RS, NULL_RS, NUM_RSS } tRenderService;

    const   tRenderService   &RStype;
    const   bool             &isLightingEnabled;
    const   bool             &isTexturingEnabled;
    const   int              &currentCamera;

    virtual int  startup()  = 0;
    virtual int  shutdown() = 0;

    virtual void renderFrame() const = 0;

    virtual int  createRO(SEROType::tRenderObject t, int t1=-1, int t2=-1, int t3=-1) = 0;
    virtual void destroyRO(uint32_t i) = 0;

    virtual void activateLight(uint32_t l) = 0;
    virtual void deactivateLight(uint32_t l) = 0;

            void setCamera(uint32_t c)    const { if (this->cameraExists(c)) cc_=c; else cc_=-1; }

            void enableLighting()         const { if (!l_) { l_=true; } }
            void disableLighting()        const { if (l_) { l_=false; } }

            void enableTexturing()        const { if (!tx_) { tx_=true; } }
            void disableTexturing()       const { if (tx_) { tx_=false; } }

    virtual void configureLighting()      const = 0;

    virtual void configureTexturing()     const = 0;

    virtual bool objectExists(uint32_t o) const = 0;
    virtual bool cameraExists(uint32_t c) const = 0;
    virtual bool lightExists(uint32_t l)  const = 0;

  protected:
    SERenderService(tRenderService t) : t_(t), l_(true), tx_(false), cc_(-1), RStype(t_), isLightingEnabled(l_), isTexturingEnabled(tx_), currentCamera(cc_) {}
    virtual ~SERenderService() {}

  private:
            tRenderService t_;
    mutable bool           l_;
    mutable bool           tx_;
    mutable int            cc_;
};

template <class T> class SERenderServiceInternals : public SERenderService
{
  public:
    virtual const SERenderObject<T> *getObject(uint32_t o) const = 0;
    virtual const SECamera<T>       *getCamera(uint32_t c) const = 0;
    virtual const SELight<T>        *getLight(uint32_t l)  const = 0;

    virtual       SERenderObject<T> *getObject(uint32_t o) = 0;
    virtual       SECamera<T>       *getCamera(uint32_t c) = 0;
    virtual       SELight<T>        *getLight(uint32_t l)  = 0;

    virtual       void               setGlobalAmbientLight(T r, T g, T b, T a) const = 0;
    virtual       void               setGlobalAmbientLighti(int r, int g, int b, int a) const = 0;
  protected:
    SERenderServiceInternals(tRenderService t) : SERenderService(t) {}
    virtual ~SERenderServiceInternals() {}
};

class SENullRenderService : public SERenderServiceInternals<int>
{
  friend class SEServiceLocator;

  public:
    virtual int   startup() { return(0); }
    virtual int   shutdown() { return(0); }

    virtual void  renderFrame() const {}

    virtual int   createRO(SEROType::tRenderObject t, int t1=-1, int t2=-1, int t3=-1) { return(-1); }
    virtual void  destroyRO(uint32_t i) {}

    virtual const SERenderObject<int>  *getObject(uint32_t o) const { return NULL; }
    virtual const SECamera<int>        *getCamera(uint32_t c) const { return NULL; }
    virtual const SELight<int>         *getLight(uint32_t l)  const { return NULL; }

    virtual       SERenderObject<int>  *getObject(uint32_t o)       { return NULL; }
    virtual       SECamera<int>        *getCamera(uint32_t c)       { return NULL; }
    virtual       SELight<int>         *getLight(uint32_t l)        { return NULL; }

    virtual       void                  setGlobalAmbientLight(int r, int g, int b, int a) const {}
    virtual       void                  setGlobalAmbientLighti(int r, int g, int b, int a) const {}

    virtual       void                  activateLight(uint32_t l) {}
    virtual       void                  deactivateLight(uint32_t l) {}

  protected:
    SENullRenderService() : SERenderServiceInternals<int>(NULL_RS) {}
    virtual ~SENullRenderService() {}

    virtual void configureLighting()      const {}

    virtual void configureTexturing()     const {}

    virtual bool objectExists(uint32_t o) const { return false; }
    virtual bool cameraExists(uint32_t c) const { return false; }
    virtual bool lightExists(uint32_t l)  const { return false; }

};

#endif
