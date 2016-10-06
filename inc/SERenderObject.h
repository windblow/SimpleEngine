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
    const   SEVec4<T>               &translation;
    const   SEQuaternion<T>         &rotation;
    const   T                       &scale;

            SERenderObject<T> &setTranslation(T x, T y, T z)                   { t_.vec(x,y,z,(T)1); return(*this); }
            SERenderObject<T> &setTranslation(const SEVec3<T> &t)              { t_=t; return(*this); }
            SERenderObject<T> &setTranslation(const SEVec4<T> &t)              { t_=t; return(*this); }
            SERenderObject<T> &setTranslation(const SEMat4<T> &t)              { return setTranslation(t[3],t[7],t[11],(T)1); }

            SERenderObject<T> &setPosition(T x, T y, T z)                      { return setTranslation(x,y,z); }
            SERenderObject<T> &setPosition(const SEVec3<T> &t)                 { return setTranslation(t); }
            SERenderObject<T> &setPosition(const SEVec4<T> &t)                 { return setTranslation(t); }
            SERenderObject<T> &setPosition(const SEMat4<T> &t)                 { return setTranslation(t); }

            SERenderObject<T> &setPos(T x, T y, T z)                           { return setTranslation(x,y,z); }
            SERenderObject<T> &setPos(const SEVec3<T> &t)                      { return setTranslation(t); }
            SERenderObject<T> &setPos(const SEVec4<T> &t)                      { return setTranslation(t); }
            SERenderObject<T> &setPos(const SEMat4<T> &t)                      { return setTranslation(t); }

            SERenderObject<T> &setX(T x)                                       { t_.x=x; return(*this); }
            SERenderObject<T> &setY(T y)                                       { t_.y=y; return(*this); }
            SERenderObject<T> &setZ(T z)                                       { t_.z=z; return(*this); }

            SERenderObject<T> &setPosX(T x)                                    { t_.x=x; return(*this); }
            SERenderObject<T> &setPosY(T y)                                    { t_.y=y; return(*this); }
            SERenderObject<T> &setPosZ(T z)                                    { t_.z=z; return(*this); }

            SERenderObject<T> &translateBy(T x, T y, T z)                      { t_[0]+=x; t_[1]+=y; t_[2]+=z; return(*this); }
            SERenderObject<T> &translateBy(const SEVec3<T> &dt)                { t_+=dt; return(*this); }
            SERenderObject<T> &translateBy(const SEVec4<T> &dt)                { t_+=dt; return(*this); }
            SERenderObject<T> &translateBy(const SEMat4<T> &dt)                { return translateBy(dt[3],dt[7],dt[11]); }
            SERenderObject<T> &translateBy(const SEVec3<T> &dir, T len)        { return translateBy(dir.normal()*len); }

            SERenderObject<T> &setRotation(const SEQuaternion<T> &r)           { r_=r; return(*this); }
            SERenderObject<T> &rotateBy(const SEQuaternion<T> &r)              { return setRotation(r_.rotate(r)); }
            SERenderObject<T> &rotateByDegrees(const SEVec3<T> &axis, T angle) { return setRotation(r_.rotateByDegrees(angle, axis)); }
            SERenderObject<T> &rotateByDegrees(T x, T y, T z, T angle)         { return setRotation(r_.rotateByDegrees(angle, SEVec3<T>(x,y,z))); }
            SERenderObject<T> &rotateByRadians(const SEVec3<T> &axis, T angle) { return setRotation(r_.rotateLocally(angle, axis)); }
            SERenderObject<T> &rotateByRadians(T x, T y, T z, T angle)         { return setRotation(r_.rotateLocally(angle, SEVec3<T>(x,y,z))); }

            SERenderObject<T> &setScale(T s)                                   { s_=s; return(*this); }
            SERenderObject<T> &scaleBy(T ds)                                   { s_*=ds; return(*this); }

            SERenderObject<T> &orbit(const SEVec4<T> &f, const SEVec3<T> &u, T a)                 { t_.orbit(f,u,a); return(*this); }
            SERenderObject<T> &rotateAround(const SEVec4<T> &f, const SEVec3<T> &u, T a)          { t_.rotateAround(f,u,a); return(*this); }
            SERenderObject<T> &orbitByDegrees(const SEVec4<T> &f, const SEVec3<T> &u, T a)        { t_.orbitByDegrees(f,u,a); return(*this); }
            SERenderObject<T> &rotateAroundByDegrees(const SEVec4<T> &f, const SEVec3<T> &u, T a) { t_.rotateAroundByDegrees(f,u,a); return(*this); }

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

    virtual void            preRender(const SERenderServiceInternals<T> &rs) const {}
    virtual void            applyTransformation(const SERenderServiceInternals<T> &rs) const {}
    virtual void            applyMaterial(const SERenderServiceInternals<T> &rs) const {}
    virtual void            draw(const SERenderServiceInternals<T> &rs) const = 0;
    virtual void            clearMaterial(const SERenderServiceInternals<T> &rs) const {}
    virtual void            clearTransformation(const SERenderServiceInternals<T> &rs) const {}
    virtual void            postRender(const SERenderServiceInternals<T> &rs) const {}

    virtual void            render(const SERenderServiceInternals<T> &rs) const { this->preRender(rs); this->applyTransformation(rs); this->applyMaterial(rs); this->draw(rs); this->clearMaterial(rs); this->clearTransformation(rs); this->postRender(rs); }


  private:
    SEROType::tRenderObject rt_;

    SEVec4<T>               t_;
    SEQuaternion<T>         r_;
    T                       s_;

};

#endif // __SERENDEROBJECT_H__
