#ifndef __SERENDERCOMPONENT_H__
#define __SERENDERCOMPONENT_H__

#include <list>
#include <string>

#include "SEComponent.h"
#include "SERenderService.h"
#include "SimpleEngine.h"


class SERenderComponent : public SEComponent {
  friend class SERenderService;

  public:
    typedef std::list<SERenderComponent*> tRCList;
    typedef std::list<SERenderComponent*>::iterator tRCListI;

    ~SERenderComponent() { children_.clear(); popFromRenderService(); }

  protected:
    SERenderComponent()                     : SEComponent(RENDER_COMPONENT), parent_(NULL), serverId_(0) { children_=new tRCList(); pushToRenderService(); }
    SERenderComponent(SERenderComponent *p) : SEComponent(RENDER_COMPONENT), parent_(p),    serverId_(0) { children_=new tRCList(); pushToRenderService(); }

    virtual void pushToRenderService(SERenderService *rs) { rs->pushComponent(this); }
    virtual void pushToRenderService() { pushToRenderService(SimpleEngine::rs()); }

    virtual void popFromRenderService(SERenderService *rs) { rs->popComponent(serverId_); }
    virtual void popFromRenderService() { popFromRenderService(SimpleEngine::rs()); }

    void setParent(SERenderComponent *p)   { parent_=p; }
    void attachChild(SERenderComponent *c) { c->setParent(this); children_.push_front(c); }

    void detachChild(SERenderComponent *c) { for (tRCListI it=children_.begin(); it!=children_.end(); ++it) if (*it==c) { (*it)->detachFromParent(); children_.erase(it); } }
    void detachFromParent() { parent_=NULL; }

  private:
    SERenderComponent *parent_;
    tRCList            children_;

    uint32_t           serverId_;
};
#endif // __SERENDERCOMPONENT_H__
