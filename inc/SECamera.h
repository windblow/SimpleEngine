#ifndef __SECAMERA_H__
#define __SECAMERA_H__

#include "SERenderObject.h"

template <class T> class SERenderServiceInternals;

struct SECameraType
{
    typedef enum { STATIC_CAM, ORBIT_CAM, FOLLOW_CAM, TRAIL_CAM, FREE_CAM, NUM_CAMS } tCamera;
};

struct SEFrustumType
{
    typedef enum { ORTHO, PERSPECTIVE } tFrustum;
};

template <class T> class SECamera : public virtual SERenderObject<T>
{
  public:
    const SEMat4<T>               &projection;
    const SEFrustumType::tFrustum &frustumType;
    const SECameraType::tCamera   &camType;

    void  useOrthoProjection() { f_=SEFrustumType::ORTHO; p_=defaultOrthoFrustum; }
    void  usePerspectiveProjection() { f_=SEFrustumType::PERSPECTIVE; p_=defaultPerspectiveFrustum; }

    SECamera<T> &translateRelativeBy(T x, T y, T z)      { SEVec3<T> tt(x,y,z); tt*=SERenderObject<T>::rotation; SERenderObject<T>::translateBy(tt); return(*this); }
    SECamera<T> &translateRelativeBy(const SEVec3<T> &t) { return translateRelativeBy(t.x,t.y,t.z); }
    SECamera<T> &translateRelativeBy(const SEVec4<T> &t) { return translateRelativeBy(t.x,t.y,t.z); }

    SECamera<T> &pan(T r)                                { SEVec3<T> u(defaultUpVec); u*=SERenderObject<T>::rotation; SERenderObject<T>::rotateByRadians(u,r); return(*this); }
    SECamera<T> &panLeft(T r)                            { return pan(r); }
    SECamera<T> &panRight(T r)                           { return pan(-r); }

    SECamera<T> &panByDegrees(T d)                       { SEVec3<T> u(defaultUpVec); u*=SERenderObject<T>::rotation; SERenderObject<T>::rotateByDegrees(u,d); return(*this); }
    SECamera<T> &panLeftByDegrees(T d)                   { return panByDegrees(d); }
    SECamera<T> &panRightByDegrees(T d)                  { return panByDegrees(-d); }

    SECamera<T> &tilt(T r)                               { SEVec3<T> l(defaultLeftVec); l*=SERenderObject<T>::rotation; SERenderObject<T>::rotateByRadians(l,r); return(*this); }
    SECamera<T> &tiltUp(T r)                             { return tilt(r); }
    SECamera<T> &tiltDown(T r)                           { return tilt(-r); }

    SECamera<T> &tiltByDegrees(T d)                      { SEVec3<T> l(defaultLeftVec); l*=SERenderObject<T>::rotation; SERenderObject<T>::rotateByDegrees(l,d); return(*this); }
    SECamera<T> &tiltUpByDegrees(T d)                    { return tiltByDegrees(d); }
    SECamera<T> &tiltDownByDegrees(T d)                  { return tiltByDegrees(-d); }

    SECamera<T> &zoom(T z)                               { return(*this); }
    SECamera<T> &zoomIn(T z)                             { return zoom(z); }
    SECamera<T> &zoomOut(T z)                            { return zoom(-z); }

    SECamera<T> &pedestal(T d)                           { return translateRelativeBy(0,d,0); }
    SECamera<T> &pedestalUp(T d)                         { return pedestal(d); }
    SECamera<T> &pedestalDown(T d)                       { return pedestal(-d); }

    SECamera<T> &dolly(T d)                              { return translateRelativeBy(0,0,-d); }
    SECamera<T> &dollyFront(T d)                         { return dolly(d); }
    SECamera<T> &dollyBack(T d)                          { return dolly(-d); }

    SECamera<T> &truck(T d)                              { return translateRelativeBy(d,0,0); }
    SECamera<T> &truckRight(T d)                         { return truck(d); }
    SECamera<T> &truckLeft(T d)                          { return truck(-d); }

    virtual void render(const SERenderServiceInternals<T> &rs) const {} // sobrecarrega para não renderizar nada

    virtual void setupFrame() const = 0;

  protected:
    SECamera() : SERenderObject<T>(SEROType::CAMERA_RO), t_(SECameraType::STATIC_CAM), f_(SEFrustumType::PERSPECTIVE),
                 p_(defaultPerspectiveFrustum), camType(t_), frustumType(f_), projection(p_)
    {}
    SECamera(SECameraType::tCamera t) : SERenderObject<T>(SEROType::CAMERA_RO), t_(t), f_(SEFrustumType::PERSPECTIVE),
                                        p_(defaultPerspectiveFrustum), camType(t_), frustumType(f_), projection(p_)
    {}
    virtual ~SECamera() {}

  private:
    SECameraType::tCamera   t_;
    SEFrustumType::tFrustum f_;
    SEMat4<T>               p_;

    static SEMat4<T>  defaultPerspectiveFrustum;
    static SEMat4<T>  defaultOrthoFrustum;

    static SEVec3<T>  defaultForwardVec;
    static SEVec3<T>  defaultLeftVec;
    static SEVec3<T>  defaultUpVec;

    // inicializadores de instâncias estáticas
    static SEMat4<T>  getDefaultPerspectiveFrustum() { SEMat4<T> f; f[0]=1; f[5]=(T)(4/3); f[10]=(T)(-13/12); f[11]=(T)(-25/6); f[14]=-1; f[15]=0; return f; }
    static SEMat4<T>  getDefaultOrthoFrustum() { SEMat4<T> f; f[0]=(T)0.5; f[5]=(T)0.75; f[10]=(T)(-1/24); f[11]=(T)(-13/12); return f; }
};

template <class T> SEVec3<T> SECamera<T>::defaultForwardVec = SEVec3<T>((T)0,(T)0,(T)-1);
template <class T> SEVec3<T> SECamera<T>::defaultLeftVec = SEVec3<T>((T)1,(T)0,(T)0);
template <class T> SEVec3<T> SECamera<T>::defaultUpVec = SEVec3<T>((T)0,(T)1,(T)0);

template <class T> SEMat4<T> SECamera<T>::defaultPerspectiveFrustum = SECamera<T>::getDefaultPerspectiveFrustum();
template <class T> SEMat4<T> SECamera<T>::defaultOrthoFrustum = SECamera<T>::getDefaultOrthoFrustum();

#endif // __SECAMERA_H__
