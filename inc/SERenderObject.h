#ifndef __SERENDEROBJECT_H__
#define __SERENDEROBJECT_H__

#include "SEMath.h"

template <class T> class SERenderObject
{
  public:
    typedef enum {MODEL_RO, PRIMITIVE_RO, CAMERA_RO, LIGHT_RO, FONT_RO, NUM_ROS} tRenderObject;

    const   tRenderObject   &type;

    ~SERenderObject() {}

    virtual void            setTranslation(SEMat4<T> t) = 0;
    virtual void            setRotation(SEQuaternion<T> q) = 0;

    virtual SEMat4<T>       getTranslation() = 0;
    virtual SEQuaternion<T> getRotation() = 0;

    virtual void            draw() = 0;

  protected:
    SERenderObject(tRenderObject t) : t_(t), type(t_) {}

  private:
    tRenderObject t_;

};

#endif // __SERENDEROBJECT_H__
