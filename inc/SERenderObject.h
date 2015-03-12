#ifndef __SERENDEROBJECT_H__
#define __SERENDEROBJECT_H__

#include "SEMath.h"

template <class T> class SERenderObject
{
  public:
    ~SERenderObject() {}

    virtual void            setTranslation(SEMat4<T> t) = 0;
    virtual void            setRotation(SEQuaternion<T> q) = 0;

    virtual SEMat4<T>       getTranslation() = 0;
    virtual SEQuaternion<T> getRotation() = 0;

  protected:
    SERenderObject() {}

};

#endif // __SERENDEROBJECT_H__
