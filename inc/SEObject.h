#ifndef __SEOBJECT_H__
#define __SEOBJECT_H__

class SEObject {
  public:
    typedef enum {RENDER_COMPONENT, TIMER_COMPONENT, PHYSICS_COMPONENT, ANIMATION_COMPONENT, UI_COMPONENT, AUDIO_COMPONENT, CONTROL_COMPONENT, STATEMACHINE_COMPONENT, NUM_COMPONENTS} tComponent;

    bool   queryComponent(tComponent c) { return c_[c]; }
    
    virtual void   updateComponent(tComponent c, double dt)=0;
    virtual void   updateComponent(tComponent c, double dt, const SEObject &o)=0;

  protected:
    SEObject() { for (int i=0;i<NUM_COMPONENTS;i++) c_[i]=false; }
    ~SEObject() {}
    
    void registerComponent(tComponent c) { c_[c]=true; }

  private:
    bool c_[NUM_COMPONENTS];
};

#endif
