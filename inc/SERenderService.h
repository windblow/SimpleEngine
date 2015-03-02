#ifndef __SERENDERSERVICE_H__
#define __SERENDERSERVICE_H__

#include <string>

class SEServiceLocator;

class SERenderService
{
  public:
    typedef enum { OPENGL_RS, DIRECTX_RS, NULL_RS, NUM_RSS } tRenderService;
    
  protected:
    tRenderService t_;
    
    SERenderService(tRenderService t) : t_(t) {}

  public:
    ~SERenderService() {}
    
    virtual int startup() = 0;
    virtual int shutdown() = 0;
    
    virtual void startFrame() {}
    virtual void endFrame() {}
    
    
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
};

#endif
