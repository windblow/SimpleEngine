#ifndef __SESERVICELOCATOR_H__
#define __SESERVICELOCATOR_H__

#include <string>

#include "SEConfigurationLoader.h"
#include "SERenderService.h"
#include "SEWindowManager.h"
#include "SEFlowController.h"

class SEServiceLocator
{
  private:
    friend class SimpleEngine;

    SEWindowManager *wm_;
    SERenderService *rs_;
    SEFlowController *fc_;
  

    SEServiceLocator() : wm_(NULL), rs_(NULL), fc_(NULL) {}
    ~SEServiceLocator() { delete(wm_); delete(rs_); delete(fc_); }

  public:
    void configRenderService(SERenderService::tRenderService s);
    void configWindowManager(SEWindowManager::tWindowManager s, int argc, char **argv);
    void configFlowController(SEFlowController::tFlowController s);
    
    SERenderService  *getRenderService();
    SEWindowManager  *getWindowManager();
    SEFlowController *getFlowController();
    
    void destroyRenderService() { delete(rs_); rs_=NULL; }
    void destroyWindowManager() { delete(wm_); wm_=NULL; }
    void destroyFlowController() { delete(fc_); fc_=NULL; }
};

#endif
