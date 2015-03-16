#ifndef __SESERVICELOCATOR_H__
#define __SESERVICELOCATOR_H__

#include <string>

#include "SEConfigurationLoader.h"
#include "SERenderService.h"
#include "SEWindowManager.h"
#include "SEFlowController.h"

class SEServiceLocator
{
  friend class SimpleEngine;

  public:
    void configRenderService(SERenderService::tRenderService s);
    void configWindowManager(SEWindowManager::tWindowManager s, int argc, char **argv);
    void configFlowController(SEFlowController::tFlowController t);

    SERenderService  *getRenderService();
    SEWindowManager  *getWindowManager();
    SEFlowController *getFlowController();

    void destroyRenderService()  { delete(rs_); rs_=NULL; }
    void destroyWindowManager()  { delete(wm_); wm_=NULL; }
    void destroyFlowController() { delete(fc_); fc_=NULL; }

  private:
    SERenderService  *rs_;
    SEWindowManager  *wm_;
    SEFlowController *fc_;


    SEServiceLocator() : wm_(NULL), rs_(NULL), fc_(NULL) {}
    ~SEServiceLocator() { delete(fc_); delete(wm_); delete(rs_); }

};

#endif
