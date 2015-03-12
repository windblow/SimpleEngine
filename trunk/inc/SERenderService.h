#ifndef __SERENDERSERVICE_H__
#define __SERENDERSERVICE_H__

#include <string>

class SEServiceLocator;
class SERenderComponent;

class SERenderService
{
  public:
    typedef enum { OPENGL_RS, DIRECTX_RS, NULL_RS, NUM_RSS } tRenderService;

    ~SERenderService() {}

    virtual int startup() = 0;
    virtual int shutdown() = 0;

    virtual void startFrame() {}
    virtual void endFrame() {}

    virtual uint32_t pushComponent(SERenderComponent *c) = 0;
    virtual void     popComponent(uint32_t i) = 0;

  protected:
    tRenderService t_;

    SERenderService(tRenderService t) : t_(t) {}

};

class SENullRenderService : public SERenderService
{
  friend class SEServiceLocator;

  protected:
    SENullRenderService() : SERenderService(NULL_RS) {}
    ~SENullRenderService() {}

  public:
    virtual int startup() {}
    virtual int shutdown() {}

    virtual uint32_t pushComponent(SERenderComponent *c) {}
    virtual void     popComponent(uint32_t i) {}


};

#endif
