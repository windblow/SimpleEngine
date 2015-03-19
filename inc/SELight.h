#ifndef __SELIGHT_H__
#define __SELIGHT_H__

#include "SERenderObject.h"

struct SELightTypes
{
    typedef enum {AMBENT, POINT, SPOT, DIRECTIONAL, AREA, NUM_LIGHTTYPES} tLight;
};

template <class T> class SELight : public virtual SERenderObject<T>
{
  public:
    const SELightTypes::tLight &lightType;

    SELight(SELightTypes::tLight t) : SERenderObject<T>(SEROType::LIGHT_RO), t_(t), lightType(t_) {}
    virtual ~SELight() {}

  private:
    SELightTypes::tLight t_;
};

#endif // __SELIGHT_H__
