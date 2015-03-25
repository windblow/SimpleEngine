#ifndef __SELIGHT_H__
#define __SELIGHT_H__

#include "SERenderObject.h"

#include "SEMath.h"

struct SELightTypes
{
    typedef enum {AMBIENT, POINT, SPOT, DIRECTIONAL, AREA, NUM_LIGHTTYPES} tLight;
};

template <class T> class SELight
{
  public:
    const   SELightTypes::tLight &lightType;
    const   SEVec3<T> &color;
    const   T         &r;
    const   T         &g;
    const   T         &b;
    const   T         &intensity;
    const   bool      &isOn;

    virtual void       setColor(const SEVec3<T> &c) { rgb_=c; clampColor(); this->configure(); }
    virtual void       setColor(T r, T g, T b)      { rgb_[0]=r; rgb_[1]=g; rgb_[2]=b; clampColor(); this->configure(); }

    virtual void       setIntensity(T i)            { i_ = CLAMP(i,0,1); this->configure(); }

    virtual void       toggle()                     { on_=!on_; if (on_) this->enable(); else this->disable(); }

    virtual void       configure()            const = 0;
    virtual void       enable()               const = 0;
    virtual void       disable()              const = 0;

  protected:
    SELight(SELightTypes::tLight t)                : t_(t), rgb_(1,1,1), i_(1), on_(false), lightType(t_), color(rgb_), r(rgb_[0]), g(rgb_[1]), b(rgb_[2]), intensity(i_), isOn(on_) {}
    SELight(SELightTypes::tLight t, T r, T g, T b) : t_(t), rgb_(r,g,b), i_(1), on_(false), lightType(t_), color(rgb_), r(rgb_[0]), g(rgb_[1]), b(rgb_[2]), intensity(i_), isOn(on_) { clampColor(); }
    virtual ~SELight() {}

  private:
    SELightTypes::tLight t_;
    SEVec3<T>            rgb_;
    T                    i_;
    bool                 on_;

    void                 clampColor() { rgb_.vec(CLAMP(rgb_.x,0,1), CLAMP(rgb_.y,0,1), CLAMP(rgb_.z,0,1)); }
};

template <class T> class SEAmbientLight : public virtual SELight<T>
{

  protected:
    SEAmbientLight() : SELight<T>(SELightTypes::AMBIENT) {}
    SEAmbientLight(T r, T g, T b) : SELight<T>(SELightTypes::AMBIENT, r, g, b) {}
    virtual ~SEAmbientLight() {}

};

#endif // __SELIGHT_H__
