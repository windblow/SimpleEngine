#ifndef __SERENDEROBJECT_H__
#define __SERENDEROBJECT_H__

#include "SEMath.h"

struct SEROType
{
    typedef enum {MODEL_RO, PRIMITIVE_RO, CAMERA_RO, LIGHT_RO, FONT_RO, NUM_ROS} tRenderObject;
};

template <class T> class SERenderObject
{
  public:
    const   SEROType::tRenderObject &ROtype;
    const   SEMat4<T>               &translation;
    const   SEQuaternion<T>         &rotation;

    ~SERenderObject() {}

            void            setTranslation(const SEMat4<T> &t)              { t_=t; }
            void            translateBy(const SEMat4<T> &dt)                { setTranslation(t_+dt); }
            void            translateBy(const SEVec3<T> &dir, const T len)  { setTranslation(t_+(dir.normal()*len).mat4()); }
            void            translateBy(T x, T y, T z, T len)               { setTranslation(t_+(SEVec3<T>(x,y,z).normal()*len).mat4()); }

            void            setRotation(const SEQuaternion<T> &r)           { r_=r; }
            void            rotateBy(const SEQuaternion<T> &r)              { setRotation(r_.rotate(r)); }
            void            rotateByDegrees(const SEVec3<T> &axis, T angle) { setRotation(r_.rotateByDegrees(angle, axis)); }
            void            rotateByDegrees(T x, T y, T z, T angle)         { setRotation(r_.rotateByDegrees(angle, SEVec3<T>(x,y,z))); }
            void            rotateByRadians(const SEVec3<T> &axis, T angle) { setRotation(r_.rotateLocally(angle, axis)); }
            void            rotateByRadians(T x, T y, T z, T angle)         { setRotation(r_.rotateLocally(angle, SEVec3<T>(x,y,z))); }


            void            render() const { this->preRender(); this->applyTransformation(); this->applyMaterial(); this->draw(); this->postRender(); }

    virtual void            draw() const = 0;

  protected:
    SERenderObject(SEROType::tRenderObject rt) : rt_(rt), t_(), r_(), ROtype(rt_), translation(t_), rotation(r_) {}

            SEMat4<T>       getTransformationMatrix() const { return t_*r_.mat4(); }

    virtual void            preRender() const {}
    virtual void            applyTransformation() const {}
    virtual void            applyMaterial() const {}
    virtual void            postRender() const {}



  private:
    SEROType::tRenderObject rt_;

    SEMat4<T>               t_;
    SEQuaternion<T>         r_;

};

#endif // __SERENDEROBJECT_H__
