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

    virtual int  startup() = 0;
    virtual int  shutdown() = 0;

    virtual void renderFrame() const = 0;

    virtual int  createRO(SEROType::tRenderObject t, int t1=-1, int t2=-1, int t3=-1) = 0;
    virtual void destroyRO(uint32_t i) = 0;

    virtual void setCamera(uint32_t c) = 0;
    virtual void activateLight(uint32_t l) = 0;
    virtual void deactivateLight(uint32_t l) = 0;

    virtual void enableLighting() const = 0;
    virtual void disableLighting() const = 0;

  protected:
    SERenderService(tRenderService t) : t_(t), RStype(t_) {}
    virtual ~SERenderService() {}

  private:
    tRenderService t_;
};

template <class T> class SERenderServiceInternals : public SERenderService
{
  public:
    virtual const SERenderObject<T> *getObject(uint32_t o) const = 0;
    virtual const SECamera<T>       *getCamera(uint32_t c) const = 0;
    virtual const SELight<T>        *getLight(uint32_t l) const = 0;

    virtual SERenderObject<T> *getObject(uint32_t o) = 0;
    virtual SECamera<T>       *getCamera(uint32_t c) = 0;
    virtual SELight<T>        *getLight(uint32_t l) = 0;

  protected:
    SERenderServiceInternals(tRenderService t) : SERenderService(t) {}
    virtual ~SERenderServiceInternals() {}
};

class SENullRenderService : public SERenderServiceInternals<void>
{
  friend class SEServiceLocator;

  protected:
    SENullRenderService() : SERenderServiceInternals<void>(NULL_RS) {}
    virtual ~SENullRenderService() {}

  public:
    virtual int  startup() { return(0); }
    virtual int  shutdown() { return(0); }

    virtual void renderFrame() const {}

    virtual int  createRO(SEROType::tRenderObject t, int t1=-1, int t2=-1, int t3=-1) { return(-1); }
    virtual void destroyRO(uint32_t i) {}

    virtual const SERenderObject<void> *getObject(uint32_t o) const { return NULL; }
    virtual const SECamera<void>       *getCamera(uint32_t c) const { return NULL; }
    virtual const SELight<void>        *getLight(uint32_t l) const { return NULL; }

    virtual SERenderObject<void> *getObject(uint32_t o) { return NULL; }
    virtual SECamera<void>       *getCamera(uint32_t c) { return NULL; }
    virtual SELight<void>        *getLight(uint32_t l) { return NULL; }

    virtual void     setCamera(uint32_t c) {}
    virtual void     activateLight(uint32_t l) {}
    virtual void     deactivateLight(uint32_t l) {}

    virtual void enableLighting() const {}
    virtual void disableLighting() const {}
};

#endif
