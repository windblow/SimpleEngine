#include "../inc/SEMath.h"

template <class T> const SEVec3<T>       SEMathUtil<T>::UNIT_X_3      = SEVec3<T>(1,0,0);
template <class T> const SEVec3<T>       SEMathUtil<T>::UNIT_Y_3      = SEVec3<T>(0,1,0);
template <class T> const SEVec3<T>       SEMathUtil<T>::UNIT_Z_3      = SEVec3<T>(0,0,1);

template <class T> const SEVec4<T>       SEMathUtil<T>::UNIT_X_4      = SEVec4<T>(1,0,0,0);
template <class T> const SEVec4<T>       SEMathUtil<T>::UNIT_Y_4      = SEVec4<T>(0,1,0,0);
template <class T> const SEVec4<T>       SEMathUtil<T>::UNIT_Z_4      = SEVec4<T>(0,0,1,0);
template <class T> const SEVec4<T>       SEMathUtil<T>::UNIT_W_4      = SEVec4<T>(0,0,0,1);

template <class T> const SEQuaternion<T> SEMathUtil<T>::IDENTITY_QUAT = SEQuaternion<T>();
template <class T> const SEQuaternion<T> SEMathUtil<T>::R90X          = SEQuaternion<T>(PIOVER4,1,0,0);
template <class T> const SEQuaternion<T> SEMathUtil<T>::R90Y          = SEQuaternion<T>(PIOVER4,0,1,0);
template <class T> const SEQuaternion<T> SEMathUtil<T>::R90Z          = SEQuaternion<T>(PIOVER4,0,0,1);
template <class T> const SEQuaternion<T> SEMathUtil<T>::R180X         = SEQuaternion<T>(PIOVER2,1,0,0);
template <class T> const SEQuaternion<T> SEMathUtil<T>::R180Y         = SEQuaternion<T>(PIOVER2,0,1,0);
template <class T> const SEQuaternion<T> SEMathUtil<T>::R180Z         = SEQuaternion<T>(PIOVER2,0,0,1);

template <class T> const SEMat3<T>       SEMathUtil<T>::IDENTITY_3    = SEMat3<T> (1, 0, 0,
                                                                                   0, 1, 0,
                                                                                   0, 0, 1);

template <class T> const SEMat4<T>       SEMathUtil<T>::IDENTITY_4    = SEMat4<T> (1, 0, 0, 0,
                                                                                   0, 1, 0, 0,
                                                                                   0, 0, 1, 0,
                                                                                   0, 0, 0, 1);
