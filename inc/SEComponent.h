#ifndef __SECOMPONENT_H__
#define __SECOMPONENT_H__

#include "SEObject.h"

class SEComponent : public SEObject {
  public:
    typedef enum {
        RENDER_COMPONENT,
        TIMER_COMPONENT,
        PHYSICS_COMPONENT,
        ANIMATION_COMPONENT,
        UI_COMPONENT,
        AUDIO_COMPONENT,
        CONTROL_COMPONENT,
        STATEMACHINE_COMPONENT,
        NUM_COMPONENTS
    } tComponent;

    virtual void       update(double dt) = 0;

    virtual tComponent type() = 0;

    ~SEComponent() {}
  protected:
    SEComponent(tComponent t) : t_(t) {}

    tComponent t_;
};
#endif // __SECOMPONENT_H__
