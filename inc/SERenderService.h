#ifndef __SERENDERSERVICE_H__
#define __SERENDERSERVICE_H__

#include "SERenderObject.h"

#include <string>
#include <vector>

class SEServiceLocator;
class SERenderComponent;

class SEMesh;
class SEPrimitive;

class SECamera;
class SELight;

class SERenderService
{
  friend class SEServiceLocator;

  public:
    typedef enum { OPENGL_RS, DIRECTX_RS, NULL_RS, NUM_RSS } tRenderService;

    const   tRenderService   &RStype;

    virtual int      startup() = 0;
    virtual int      shutdown() = 0;

    virtual void     renderFrame() = 0;

    virtual uint32_t pushComponent(SERenderComponent *c) = 0;
    virtual void     popComponent(uint32_t i) = 0;

    virtual void     setCamera(uint32_t c) = 0;
    virtual void     activateLight(uint32_t l) = 0;
    virtual void     deactivateLight(uint32_t l) = 0;

  protected:
    SERenderService(tRenderService t) : t_(t), RStype(t_) {}
    virtual ~SERenderService() {}

  private:
    tRenderService t_;
};

template <class T> class SERenderServiceInternals : public SERenderService
{
  public:
    virtual SERenderObject<T> *getObject(uint32_t o) = 0;


  protected:
    SERenderServiceInternals(tRenderService t) : SERenderService(t) {}
};

class SENullRenderService : public SERenderServiceInternals<void>
{
  friend class SEServiceLocator;

  protected:
    SENullRenderService() : SERenderServiceInternals<void>(NULL_RS) {}
    virtual ~SENullRenderService() {}

  public:
    virtual int      startup() {}
    virtual int      shutdown() {}

    virtual void     renderFrame() {}

    virtual uint32_t pushComponent(SERenderComponent *c) {}
    virtual void     popComponent(uint32_t i) {}

    virtual SERenderObject<void> *getObject(uint32_t o) { return NULL; }

    virtual void     setCamera(uint32_t c) {}
    virtual void     activateLight(uint32_t l) {}
    virtual void     deactivateLight(uint32_t l) {}
};

#endif
