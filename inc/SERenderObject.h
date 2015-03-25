#ifndef __SERENDEROBJECT_H__
#define __SERENDEROBJECT_H__

#include "SEMath.h"

class SERenderService;
template <class T> class SERenderServiceInternals;

struct SEROType
{
    typedef enum {MODEL_RO, PRIMITIVE_RO, CAMERA_RO, LIGHT_RO, FONT_RO, NUM_ROS} tRenderObject;
};

template <class T> class SERenderObject
{
  friend class SERenderService;

  public:
    const   SEROType::tRenderObject &objectType;
    const   SEVec3<T>               &translation;
    const   SEQuaternion<T>         &rotation;
    const   T                       &scale;

            void            setTranslation(T x, T y, T z)                   { t_.vec(x,y,z); }
            void            setTranslation(const SEVec3<T> &t)              { t_=t; }
            void            setTranslation(const SEVec4<T> &t)              { setTranslation(t.x, t.y, t.z); }
            void            setTranslation(const SEMat4<T> &t)              { setTranslation(t[3],t[7],t[11]); }

            void            translateBy(T x, T y, T z)                      { t_[0]+=x; t_[1]+=y; t_[2]+=z; }
            void            translateBy(const SEVec3<T> &dt)                { t_+=dt; }
            void            translateBy(const SEVec4<T> &dt)                { translateBy(dt.x,dt.y,dt.z); }
            void            translateBy(const SEMat4<T> &dt)                { translateBy(dt[3],dt[7],dt[11]); }
            void            translateBy(const SEVec3<T> &dir, T len)        { translateBy(dir.normal()*len); }
            void            translateBy(T x, T y, T z, T len)               { translateBy(SEVec3<T>(x,y,z),len); }

            void            setRotation(const SEQuaternion<T> &r)           { r_=r; }
            void            rotateBy(const SEQuaternion<T> &r)              { setRotation(r_.rotate(r)); }
            void            rotateByDegrees(const SEVec3<T> &axis, T angle) { setRotation(r_.rotateByDegrees(angle, axis)); }
            void            rotateByDegrees(T x, T y, T z, T angle)         { setRotation(r_.rotateByDegrees(angle, SEVec3<T>(x,y,z))); }
            void            rotateByRadians(const SEVec3<T> &axis, T angle) { setRotation(r_.rotateLocally(angle, axis)); }
            void            rotateByRadians(T x, T y, T z, T angle)         { setRotation(r_.rotateLocally(angle, SEVec3<T>(x,y,z))); }

            void            setScale(T s)                                   { s_=s; }
            void            scaleBy(T ds)                                   { s_*=ds; }

            SEMat4<T>       getScaleMatrix()        const { return SEMat4<T>(s_,0,0,0,
                                                                             0,s_,0,0,
                                                                             0,0,s_,0,
                                                                             0,0,0, 1); }
            SEMat4<T>       getRotationMatrix()     const { return r_.mat4(); }
            SEMat4<T>       getTranslationMatrix()  const { return SEMat4<T>(1,0,0,t_.x,
                                                                             0,1,0,t_.y,
                                                                             0,0,1,t_.z,
                                                                             0,0,0,   1); }

            SEMat4<T>       getModelMatrix()        const { return getTranslationMatrix()*getRotationMatrix()*getScaleMatrix(); }
            SEMat4<T>       getInverseModelMatrix() const { return getModelMatrix().invert(); }

  protected:
    SERenderObject(SEROType::tRenderObject rt) : rt_(rt), t_(), r_(), s_(1), objectType(rt_), translation(t_), rotation(r_), scale(s_) {}
    virtual ~SERenderObject() {}

    virtual void            preRender() const {}
    virtual void            applyTransformation() const {}
    virtual void            applyLighting(const SERenderServiceInternals<T> &rs) const {}
    virtual void            applyMaterial() const {}
    virtual void            draw() const = 0;
    virtual void            clearMaterial() const {}
    virtual void            clearLighting(const SERenderServiceInternals<T> &rs) const {}
    virtual void            clearTransformation() const {}
    virtual void            postRender() const {}

    virtual void            render(const SERenderServiceInternals<T> &rs) const { this->preRender(); this->applyTransformation(); this->applyLighting(rs); this->applyMaterial(); this->draw(); this->clearMaterial(); this->clearLighting(rs); this->clearTransformation(); this->postRender(); }


  private:
    SEROType::tRenderObject rt_;

    SEVec3<T>               t_;
    SEQuaternion<T>         r_;
    T                       s_;

};

#endif // __SERENDEROBJECT_H__
