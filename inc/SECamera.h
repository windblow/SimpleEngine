#ifndef __SECAMERA_H__
#define __SECAMERA_H__

#include "SERenderObject.h"

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

    // inicializadores de instâncias estáticas
    static SEMat4<T>  getDefaultPerspectiveFrustum() { SEMat4<T> f; f[0]=1; f[5]=(T)(4/3); f[10]=(T)(-13/12); f[11]=(T)(-25/6); f[14]=-1; f[15]=0; return f; }
    static SEMat4<T>  getDefaultOrthoFrustum() { SEMat4<T> f; f[0]=(T)0.5; f[5]=(T)0.75; f[10]=(T)(-1/24); f[11]=(T)(-13/12); return f; }
};

template <class T> SEMat4<T> SECamera<T>::defaultPerspectiveFrustum = SECamera<T>::getDefaultPerspectiveFrustum();
template <class T> SEMat4<T> SECamera<T>::defaultOrthoFrustum = SECamera<T>::getDefaultOrthoFrustum();

#endif // __SECAMERA_H__
