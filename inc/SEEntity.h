#ifndef __SEENTITY_H__
#define __SEENTITY_H__

#include <string>

#include "SEObject.h"
#include "SEComponent.h"
#include "SEMath.h"

class SEEntity : public SEObject
{
  public:
                         SEEntity()                     : SEObject()  { for (int i=0;i<SEComponent::NUM_COMPONENTS;i++) c_[i]=NULL; }
                         SEEntity(const std::string &n) : SEObject(n) { for (int i=0;i<SEComponent::NUM_COMPONENTS;i++) c_[i]=NULL; }
                        ~SEEntity() {}

    virtual void         update(double dt) {}

            bool         queryComponent(SEComponent::tComponent c) { if (c_[c]==NULL) return false; else return true; }

            void         registerComponent(SEComponent *c)         { c_[c->type()]=c; }
            SEComponent *getComponent(SEComponent::tComponent t)   { return c_[t]; }

  private:
            SEComponent *c_[SEComponent::NUM_COMPONENTS];
};

#endif // __SEENTITY_H__
