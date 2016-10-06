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
    const   SEColor<T> &color;
    const   T          &r;
    const   T          &g;
    const   T          &b;
    const   T          &a;
    const   T          &intensity;
    const   bool       &isOn;

    virtual SELight<T> &setColor(T r, T g, T b, T a)          { rgba_.set(r,g,b,a);          /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColor(T r, T g, T b)               { rgba_.set(r,g,b);            /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColor(const T *f)                  { rgba_.set(f);                /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColor(const SEColor<T> &c)         { rgba_.set(c);                /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColor(const SEVec4<T> &c)          { rgba_.set(c);                /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColor(const SEVec3<T> &c)          { rgba_.set(c);                /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColori(int r, int g, int b, int a) { rgba_.setIntValues(r,g,b,a); /*this->configure();*/ return(*this); }
    virtual SELight<T> &setColori(int r, int g, int b)        { rgba_.setIntValues(r,g,b);   /*this->configure();*/ return(*this); }

    virtual SELight<T> &setIntensity(T i)                     { i_ = CLAMP(i,0,1); /*this->configure();*/ return(*this); }

    virtual SELight<T> &toggle()                              { on_=!on_; if (on_) this->enable(); else this->disable(); return(*this); }

    virtual void        configure()            const = 0;
    virtual void        enable()               const = 0;
    virtual void        disable()              const = 0;

  protected:
    SELight(SELightTypes::tLight t)                         : t_(t), rgba_(1,1,1,1),     i_(1), on_(false), lightType(t_), color(rgba_), r(rgba_.r), g(rgba_.g), b(rgba_.b), a(rgba_.a), intensity(i_), isOn(on_) {}
    SELight(SELightTypes::tLight t, T rr, T gg, T bb, T aa) : t_(t), rgba_(rr,gg,bb,aa), i_(1), on_(false), lightType(t_), color(rgba_), r(rgba_.r), g(rgba_.g), b(rgba_.b), a(rgba_.a), intensity(i_), isOn(on_) {}
    virtual ~SELight() {}

  private:
    SELightTypes::tLight t_;
    SEColor<T>           rgba_;
    T                    i_;
    bool                 on_;
};

template <class T> class SEAmbientLight : public virtual SELight<T>
{

  protected:
    SEAmbientLight()                   : SELight<T>(SELightTypes::AMBIENT)             {}
    SEAmbientLight(T r, T g, T b, T a) : SELight<T>(SELightTypes::AMBIENT, r, g, b, a) {}
    virtual ~SEAmbientLight() {}

};

template <class T> class SESpotLight : public virtual SELight<T>
{
  public:
    const   SEVec4<T>      &direction;
    const   T              &cutoff;

    virtual SESpotLight<T> &setDirection(SEVec3<T> d)   { dir_=d.normalize(); return(*this); }
    virtual SESpotLight<T> &setDirection(T x, T y, T z) { dir_=SEVec3<T>(x,y,z).normalize(); return(*this); }
    virtual SESpotLight<T> &setCutoff(T ang)            { cut_=ang; return(*this); }

  protected:
    SESpotLight()                        : SELight<T>(SELightTypes::SPOT),             dir_(0,-1,0), cut_(45.0), direction(dir_), cutoff(cut_) {}
    SESpotLight(T r, T g, T b, T a)      : SELight<T>(SELightTypes::SPOT, r, g, b, a), dir_(0,-1,0), cut_(45.0), direction(dir_), cutoff(cut_) {}
    SESpotLight(T r, T g, T b, T a, T c) : SELight<T>(SELightTypes::SPOT, r, g, b, a), dir_(0,-1,0), cut_(c),    direction(dir_), cutoff(cut_) {}
    virtual ~SESpotLight() {}

  private:
    SEVec4<T>              dir_;
    T                      cut_;
};



template <class T> class SEPointLight : public virtual SELight<T>
{
  protected:
    SEPointLight()                   : SELight<T>(SELightTypes::POINT)             {}
    SEPointLight(T r, T g, T b, T a) : SELight<T>(SELightTypes::POINT, r, g, b, a) {}
    virtual ~SEPointLight() {}

};

template <class T> class SEDirectionalLight : public virtual SELight<T>
{
  public:
    const   SEVec4<T>             &direction;

    virtual SEDirectionalLight<T> &setDirection(SEVec3<T> d)   { dir_=d.normalize(); dir_.w=0; return(*this); }
    virtual SEDirectionalLight<T> &setDirection(T x, T y, T z) { dir_=SEVec3<T>(x,y,z).normalize(); dir_.w=0; return(*this); }

  protected:
    SEDirectionalLight()                   : dir_(0,0,-1), direction(dir_), SELight<T>(SELightTypes::DIRECTIONAL)             {}
    SEDirectionalLight(T r, T g, T b, T a) : dir_(0,0,-1), direction(dir_), SELight<T>(SELightTypes::DIRECTIONAL, r, g, b, a) {}
    virtual ~SEDirectionalLight() {}

  private:
    SEVec4<T>                      dir_;
};

#endif // __SELIGHT_H__
