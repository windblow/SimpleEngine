#ifndef __SEMATH_H__
#define __SEMATH_H__

#include <cmath>
#include <cassert>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
//#include <random>
//#include <chrono>

/** Macros que definem comparações entre tipos genéricos **/
// produto escalar entre dois vetores representados por arrays
#define VECDOT(v1,v2) ((v1)[0]*(v2)[0]+(v1)[1]*(v2)[1]+(v1)[2]*(v2)[2])

// limita valor a um intervalo
#define CLAMP(x,a,b) (x < a ? a : (x > b ? b : x))

// Pi (para ser utilizado em construtores de objetos const no escopo global, a ordem de inicialização de SEMath pode interferir na linkagem)
#define PI_ 3.14159265359f

// valor absoluto
#define ABS(a) (a > 0 ? a : -a)

// mínimo entre 2 valores
#define MIN2(a,b) ((a<b)?a:b)
// mínimo entre 3 valores
#define MIN3(a,b,c) MIN2(MIN2(a,b),c)

// máximo entre 2 valores
#define MAX2(a,b) ((a)>(b)?(a):(b))
// máximo entre 3 valores
#define MAX3(a,b,c) MAX2(MAX2(a,b),c)

/** Forward declarations **/
template <class T> class SEMathUtil;
template <class T> class SEVec3;
template <class T> class SEVec4;
template <class T> class SEQuaternion;
template <class T> class SEMat3;
template <class T> class SEMat4;
template <class T> class SERay;
template <class T> class SEPlane;
template <class T> class SEChronometer;
template <class T> class SETimer;
template <class T> class SERandomNumberGenerator;

/** Type definitions **/
typedef SEMathUtil<int>                 SEMathUtili;
typedef SEMathUtil<float>               SEMathUtilf;
typedef SEMathUtil<double>              SEMathUtild;

typedef SEVec3<int>                     SEVec3i;
typedef SEVec3<float>                   SEVec3f;
typedef SEVec3<double>                  SEVec3d;

typedef SEVec4<int>                     SEVec4i;
typedef SEVec4<float>                   SEVec4f;
typedef SEVec4<double>                  SEVec4d;

typedef SEQuaternion<float>             SEQuaternionf;
typedef SEQuaternion<double>            SEQuaterniond;

typedef SEMat3<int>                     SEMat3i;
typedef SEMat3<float>                   SEMat3f;
typedef SEMat3<double>                  SEMat3d;

typedef SEMat4<int>                     SEMat4i;
typedef SEMat4<float>                   SEMat4f;
typedef SEMat4<double>                  SEMat4d;

typedef SERay<int>                      SERayi;
typedef SERay<float>                    SERayf;
typedef SERay<double>                   SERayd;

typedef SEPlane<int>                    SEPlanei;
typedef SEPlane<float>                  SEPlanef;
typedef SEPlane<double>                 SEPlaned;

typedef SEChronometer<int>              SEChronometeri;
typedef SEChronometer<float>            SEChronometerf;
typedef SEChronometer<double>           SEChronometerd;

typedef SETimer<int>                    SETimeri;
typedef SETimer<float>                  SETimerf;
typedef SETimer<double>                 SETimerd;

typedef SERandomNumberGenerator<int>    SERandomNumberGeneratori;
typedef SERandomNumberGenerator<float>  SERandomNumberGeneratorf;
typedef SERandomNumberGenerator<double> SERandomNumberGeneratord;

/*
 * Classe: SEMathUtil
 *
 *   Classe template estática com valores precalculados e unidades padrão
 *
*/

template <class T> class SEMathUtil
{
  public:
    static const T               SMALL         = (T)1.0e-4f; //! limite mínimo para detecção de underflow
    static const T               BIG           = (T)1.0e+10f; //! limite máximo para detecção de overflow

    static const T               TWOPI         = (T)6.28318530718f; // 2*pi
    static const T               PI            = (T)3.14159265359f; // pi
    static const T               EPSILON       = (T)0.001f; // epsilon
    static const T               PIOVER2       = (T)1.57079632679f; // pi/2
    static const T               PIOVER4       = (T)0.78539816340f; // pi/4
    static const T               PIOVER180     = (T)1.74532925199433E-002f; // pi/180
    static const T               PIUNDER180    = (T)5.72957795130823E+001f; // 180/pi
    static const T               COS45         = (T)0.7071067811865475244f; // cosin(45)
    static const T               SQRT3         = (T)1.7320508075688772935f; // sqrt(3)
    static const T               INVSQRT3      = (T)0.5773502691896257645f; // 1/sqrt(3)

    static const SEVec3<T>       UNIT_X_3,
                                 UNIT_Y_3,
                                 UNIT_Z_3;

    static const SEVec4<T>       UNIT_X_4,
                                 UNIT_Y_4,
                                 UNIT_Z_4,
                                 UNIT_W_4;

    static const SEQuaternion<T> IDENTITY_QUAT,
                                 R90X,
                                 R90Y,
                                 R90Z,
                                 R180X,
                                 R180Y,
                                 R180Z;

    static const SEMat3<T>       IDENTITY_3;

    static const SEMat4<T>       IDENTITY_4;

    // Verifica se variável é zero dentro da margem aceita
    static       bool            ISZERO(const T &a)               { return (a>-SMALL && a<SMALL); }

    // Inverte dois valores
    static       void            SWAP(T &a, T &b)                 { register T t=a; a=b; b=t; }

    // Converte ângulos para radianos e vice-versa
    static       T               toRadians(const T &a)            { return rad(a); }
    static       T               rad(const T &a)                  { return (a * PIOVER180); }
    static       SEVec3<T>       toRadians(const SEVec3<T> &e)    { return rad(e); }
    static       SEVec3<T>       rad(const SEVec3<T> &e)          { return (e * PIOVER180); }
    static       T               toEulerAngle(const T &r)         { return ang(r); }
    static       T               ang(const T &r)                  { return (r * PIUNDER180); }
    static       SEVec3<T>       toEulerAngle(const SEVec3<T> &r) { return ang(r); }
    static       SEVec3<T>       ang(const SEVec3<T> &r)          { return (r * PIUNDER180); }
};

/*
 * Classe: SEVec3<T>
 *
 *   Coordenadas (X, Y, Z) com sobrecarga de operadores para facilitar manuseio
 *
*/

template <class T> class SEVec3
{
  public:
             T             x, y, z;

    // default constructor
                           SEVec3()                                       : x(0),    y(0),    z(0)    {}
    // copy constructor
                           SEVec3(const SEVec3<T> &c)                     : x(c.x),  y(c.y),  z(c.z)  {}

    explicit               SEVec3(T f)                                    : x(f),    y(f),    z(f)    {}
                           SEVec3(T nx, T ny)                             : x(nx),   y(ny),   z(1)    {}
                           SEVec3(T nx, T ny, T nz)                       : x(nx),   y(ny),   z(nz)   {}
    explicit               SEVec3(const T *v)                             : x(v[0]), y(v[1]), z(v[2]) {}
    explicit               SEVec3(const SEVec4<T> &v)                     : x(v.x),  y(v.y),  z(v.z)  {}
    // constrói a partir do eixo de rotação do quaternion
    explicit               SEVec3(const SEQuaternion<T> &q)               { vec(q.axis()); }
    // constrói a patir do cross-product entre v1 e v2
                           SEVec3(const SEVec3<T> &u, const SEVec3<T> &v) : x(u.y*v.z-u.z*v.y), y(u.z*v.x-u.x*v.z), z(u.x*v.y-u.y*v.x) {}

    // destructor
                          ~SEVec3() {}

             SEVec3<T>    &null()                                      { x=y=z=0; return(*this); } // função nulificadora

             SEVec3<T>    &operator =(const SEVec3<T> &in)             { if (this!=(&in)) { return vec(in); } return(*this); }
             SEVec3<T>    &operator =(const SEVec4<T> &in)             { return vec(in); }
             SEVec3<T>    &operator =(const SEQuaternion<T> &in)       { return vec(in); }
             SEVec3<T>    &operator =(const T &v)                      { return vec(v); }
             SEVec3<T>     operator -()                          const { return SEVec3<T>(-x,-y,-z); }

             SEVec3<T>    &operator +=(const SEVec3<T> &v)             { x+=v.x; y+=v.y; z+=v.z; return(*this); }
             SEVec3<T>    &operator -=(const SEVec3<T> &v)             { x-=v.x; y-=v.y; z-=v.z; return(*this); }
             SEVec3<T>    &operator *=(const T &a)                     { x*=a; y*=a; z*=a; return(*this); }
             SEVec3<T>    &operator *=(const SEVec3<T> &v)             { return cross(v); }
             SEVec3<T>    &operator /=(const T &a)                     { T inv_a = (T)1.0/a; x*=inv_a; y*=inv_a; z*=inv_a; return(*this); }
    // multiplicacao por quaternion
             SEVec3<T>    &operator *=(const SEQuaternion<T> &q)       { return (*this)=q.quickmult(*this); } //return (*this)*=q.mat3(); }
    // multiplicacao por matriz
             SEVec3<T>    &operator *=(const SEMat3<T> &n)             { return vec( x*n[0]+y*n[3]+z*n[6],
                                                                                     x*n[1]+y*n[4]+z*n[7],
                                                                                     x*n[2]+y*n[5]+z*n[8] ); }

    friend   SEVec3<T>     operator +(SEVec3<T>              lhs, SEVec3<T>       const &rhs) { return lhs += rhs; }
    friend   SEVec3<T>     operator -(SEVec3<T>              lhs, SEVec3<T>       const &rhs) { return lhs -= rhs; }
    friend   SEVec3<T>     operator *(SEVec3<T>              lhs, T               const &rhs) { return lhs *= rhs; }
    friend   SEVec3<T>     operator *(T               const &lhs, SEVec3<T>              rhs) { return rhs *= lhs; }
    friend   SEVec3<T>     operator *(SEVec3<T>              lhs, SEVec3<T>       const &rhs) { return lhs *= rhs; }
    friend   SEVec3<T>     operator *(SEVec3<T>              lhs, SEQuaternion<T> const &rhs) { return lhs *= rhs; }
    friend   SEVec3<T>     operator *(SEVec3<T>              lhs, SEMat3<T>       const &rhs) { return lhs *= rhs; }
    friend   SEVec3<T>     operator /(SEVec3<T>              lhs, T               const &rhs) { return lhs /= rhs; }

             T            &operator [](std::size_t i)                          { return (&x)[i]; }
             T             operator [](std::size_t i)                    const { return (&x)[i]; }

             bool          operator ==(const SEVec3<T> &v)               const { if (SEMathUtil<T>::ISZERO(ABS(x)-ABS(v.x)) && SEMathUtil<T>::ISZERO(ABS(y)-ABS(v.y)) && SEMathUtil<T>::ISZERO(ABS(z)-ABS(v.z))) return true; return false; }
             bool          operator !=(const SEVec3<T> &v)               const { return (!(*this)==v); }

    friend   std::ostream &operator <<(std::ostream &os, const SEVec3<T> &v)   { os<<"("<<v.x<<", "<<v.y<<", "<<v.z<<")"; return os; }

             SEVec3<T>    &vec(const T &f)                                     { x=y=z=f; return(*this); }
             SEVec3<T>    &vec(const T &nx, const T &ny, const T &nz)          { x=nx; y=ny; z=nz; return(*this); }
             SEVec3<T>    &vec(const T &nx, const T &ny)                       { x=nx; y=ny; z=1; return(*this); } // Coloca valor z=1 por padrão nas conversões de vetores de 2 posições para satisfazer o sistema de coordenadas homogêneas
             SEVec3<T>    &vec(const T *v)                                     { x=v[0]; y=v[1]; z=v[2]; return(*this); }
             SEVec3<T>    &vec(const SEVec3<T> &v)                             { x=v.x;y=v.y;z=v.z; return(*this); }
             SEVec3<T>    &vec(const SEVec4<T> &v)                             { x=v.x;y=v.y;z=v.z; return(*this); } // trunca o vetor de 4 posições e assume seus 3 valores principais
             SEVec3<T>    &vec(const SEQuaternion<T> &q)                       { return (*this)=q.axis(); } // inicializa o vetor com o eixo do quaternion passado como parâmetro

             T             dot(const SEVec3<T> &a)                       const { return (x*a.x + y*a.y + z*a.z); }
             T             angdif(const SEVec3<T> &v)                    const { return (T)arccos(dot(v)/(len()*v.len())); } // angulo entre o vetor informado e este vetor
             T             angularDifference(const SEVec3<T> &v)         const { return angdif(v); }

             SEVec3<T>     cross(const SEVec3<T> &v)                     const { return SEVec3<T>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
             SEVec3<T>    &cross(const SEVec3<T> &u, const SEVec3<T> &v)       { x=u.y*v.z-u.z*v.y; y=u.z*v.x-u.x*v.z; z=u.x*v.y-u.y*v.x; return(*this); }
             SEVec3<T>    &cross(const SEVec3<T> &v)                           { return cross((*this),v); }

             T             len2()                                        const { return (x*x + y*y + z*z); } // Quadrado do comprimento do vetor (0,0,0)->(x,y,z)
             T             len()                                         const { return (T)(sqrt(len2())); } // Comprimento do vetor (0,0,0)->(x,y,z)

             SEVec3<T>     normal()                                      const { return SEVec3<T>(*this).normalize(); } // Retorna o vetor normalizado
             SEVec3<T>     inverse()                                     const { return -(*this); } // retorna o vetor inverso

             SEVec3<T>    &negate()                                            { x=-x;y=-y;z=-z; return(*this); } // Inverte o vetor de (0,0,0)->(x,y,z) para (x,y,z)->(0,0,0)
             SEVec3<T>    &negate(const SEVec3<T> &v)                          { x=-v.x;y=-v.y;z=-v.z; return(*this); }
             SEVec3<T>    &normalize()                                         { T inv_l = (T)1.0/len(); x*=inv_l; y*=inv_l; z*=inv_l; return(*this); }// Normaliza o vetor (0,0,0)->(x,y,z) (reduz a comprimento 1)
             SEVec3<T>    &normalize(const SEVec3<T> &v)                       { T inv_l = (T)1.0/v.len(); x=v.x*inv_l; y=v.y*inv_l; z=v.z*inv_l; return(*this); }
             SEVec3<T>    &normalise()                                         { return normalize(); }
             SEVec3<T>    &normalise(const SEVec3<T> &v)                       { return normalize(v); }

             SEVec3<T>    &translate(const T &nx, const T &ny, const T &nz)    { x+=nx;y+=ny;z+=nz; return(*this); }
             SEVec3<T>    &translate(const T &nx, const T &ny)                 { x+=nx;y+=ny; return(*this); }
             SEVec3<T>    &translate(const SEVec3<T> &t)                       { x+=t.x;y+=t.y;z+=t.z; return(*this); }

             SEVec3<T>     eulerToRadians()                              const { return cetor(*this); }
             SEVec3<T>     cetor()                                       const { return SEMathUtil<T>::rad(*this); }
             SEVec3<T>    &eulerToRadians()                                    { return etor(*this); }
             SEVec3<T>    &etor()                                              { return etor(*this); }
             SEVec3<T>    &eulerToRadians(const SEVec3<T> &e)                  { return etor(e); }
             SEVec3<T>    &etor(const SEVec3<T> &e)                            { return (*this)=SEMathUtil<T>::rad(e); }

             SEVec3<T>     radiansToEuler()                              const { return crtoe(*this); }
             SEVec3<T>     crtoe()                                       const { return SEMathUtil<T>::ang(*this); }
             SEVec3<T>    &radiansToEuler()                                    { return rtoe(*this); }
             SEVec3<T>    &rtoe()                                              { return rtoe(*this); }
             SEVec3<T>    &radiansToEuler(const SEVec3<T> &e)                  { return rtoe(e); }
             SEVec3<T>    &rtoe(const SEVec3<T> &e)                            { return (*this)=SEMathUtil<T>::ang(e); }

             SEMat4<T>     toTransformationMatrix()                      const { return mat4(); }
             SEMat4<T>     mat4()                                        const { return SEMat4<T>(1,0,0,x,
                                                                                                  0,1,0,y,
                                                                                                  0,0,1,z,
                                                                                                  0,0,0,1); }

};


template <class T> class SEVec4
{
  public:
             T             x, y, z, w;

    // default constructor
                           SEVec4()                         : x(0),    y(0),    z(0),    w(0)    {}
    // copy constructor
                           SEVec4(const SEVec4<T> &c)       : x(c.x),  y(c.y),  z(c.z),  w(c.w)  {}

    explicit               SEVec4(T f)                      : x(f),    y(f),    z(f),    w(f)    {}
                           SEVec4(T nx, T ny, T nz)         : x(nx),   y(ny),   z(nz),   w(1)    {}
                           SEVec4(T nx, T ny, T nz, T nw)   : x(nx),   y(ny),   z(nz),   w(nw)   {}
    explicit               SEVec4(const T *v)               : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}
                           SEVec4(const SEVec3<T> &v)       : x(v.x),  y(v.y),  z(v.z),  w(1)    {} // Aceita conversão implícita
    explicit               SEVec4(const SEQuaternion<T> &q) : x(q.x),  y(q.y),  z(q.z),  w(q.w)  {}

    // destructor
                          ~SEVec4() {}

             SEVec4<T>    &null() { x=y=z=w=0; return(*this); } // função nulificadora

             SEVec4<T>    &operator =(const SEVec4<T> &in)             { if (this!=(&in)) { return vec(in); } return(*this); }
             SEVec4<T>    &operator =(const SEVec3<T> &in)             { return vec(in); }
             SEVec4<T>    &operator =(const SEQuaternion<T> &in)       { return vec(in); }
             SEVec4<T>     operator -()                          const { return SEVec4<T>(-x,-y,-z,-w); }

             SEVec4<T>    &operator +=(const SEVec4<T> &v)             { x+=v.x; y+=v.y; z+=v.z; w+=v.w; return(*this); }
             SEVec4<T>    &operator +=(const SEVec3<T> &v)             { x+=v.x; y+=v.y; z+=v.z; return(*this); }
             SEVec4<T>    &operator -=(const SEVec4<T> &v)             { x-=v.x; y-=v.y; z-=v.z; w-=v.w; return(*this); }
             SEVec4<T>    &operator -=(const SEVec3<T> &v)             { x-=v.x; y-=v.y; z-=v.z; return(*this); }
             SEVec4<T>    &operator *=(const T &a)                     { x*=a; y*=a; z*=a; w*=a; return(*this); }
             SEVec4<T>    &operator /=(const T &a)                     { T inv_a = (T)1.0/a; x*=inv_a; y*=inv_a; z*=inv_a; w*=inv_a; return(*this); }
    // multiplicacao por quaternion
             SEVec4<T>    &operator *=(const SEQuaternion<T> &q)       { return (*this)=(-q).quickmult(*this); }//return (*this)*=q.mat4(); }
    // multiplicação por matriz
             SEVec4<T>    &operator *=(const SEMat4<T> &n)             { return vec( x* n[0]+y* n[4]+z* n[8]+w*n[12],
                                                                                     x* n[1]+y* n[5]+z* n[9]+w*n[13],
                                                                                     x* n[2]+y* n[6]+z*n[10]+w*n[14],
                                                                                     x* n[3]+y* n[7]+z*n[11]+w*n[15] ); }

    friend   SEVec4<T>     operator +(SEVec4<T>              lhs, SEVec4<T>       const &rhs) { return lhs += rhs; }
    friend   SEVec4<T>     operator +(SEVec4<T>              lhs, SEVec3<T>       const &rhs) { return lhs += rhs; }
    friend   SEVec4<T>     operator +(SEVec3<T>       const &lhs, SEVec4<T>              rhs) { return rhs += lhs; }
    friend   SEVec4<T>     operator -(SEVec4<T>              lhs, SEVec4<T>       const &rhs) { return lhs -= rhs; }
    friend   SEVec4<T>     operator -(SEVec4<T>              lhs, SEVec3<T>       const &rhs) { return lhs -= rhs; }
    friend   SEVec4<T>     operator -(SEVec3<T>       const &lhs, SEVec4<T>              rhs) { return -rhs += lhs; }
    friend   SEVec4<T>     operator *(SEVec4<T>              lhs, T               const &rhs) { return lhs *= rhs; }
    friend   SEVec4<T>     operator *(T               const &lhs, SEVec4<T>              rhs) { return rhs *= lhs; }
    friend   SEVec4<T>     operator *(SEVec4<T>              lhs, SEQuaternion<T> const &rhs) { return lhs *= rhs; }
    friend   SEVec4<T>     operator *(SEVec4<T>              lhs, SEMat4<T>       const &rhs) { return lhs *= rhs; }
    friend   SEVec4<T>     operator /(SEVec4<T>              lhs, T               const &rhs) { return lhs /= rhs; }

             T            &operator [](std::size_t i)                              { return (&x)[i]; }
             T             operator [](std::size_t i)                        const { return (&x)[i]; }

             bool          operator ==(const SEVec4<T> &v)                   const { if (SEMathUtil<T>::ISZERO(ABS(x)-ABS(v.x)) && SEMathUtil<T>::ISZERO(ABS(y)-ABS(v.y)) && SEMathUtil<T>::ISZERO(ABS(z)-ABS(v.z)) && SEMathUtil<T>::ISZERO(ABS(w)-ABS(v.w))) return true; return false; }
             bool          operator !=(const SEVec4<T> &v)                   const { return !((*this)==v); }

    friend   std::ostream &operator <<(std::ostream &os, const SEVec4<T> &v)       { os<<"("<<v.x<<", "<<v.y<<", "<<v.z<<", "<<v.w<<")"; return os; }

             SEVec4<T>    &vec(const T &f)                                         { x=y=z=w=f; return(*this); }
             SEVec4<T>    &vec(const T &nx, const T &ny, const T &nz, const T &nw) { x=nx; y=ny; z=nz; w=nw; return(*this); }
             SEVec4<T>    &vec(const T &nx, const T &ny, const T &nz)              { x=nx; y=ny; z=nz; w=1; return(*this); }
             SEVec4<T>    &vec(const T *v)                                         { x=v[0];y=v[1];z=v[2];w=v[3]; return(*this); }
             SEVec4<T>    &vec(const SEVec3<T> &v)                                 { x=v.x; y=v.y; z=v.z; w=1; return(*this); } // Coloca valor w=1 por padrão nas conversões de vetores de 3 posições para satisfazer o sistema de coordenadas homogêneas
             SEVec4<T>    &vec(const SEVec4<T> &v)                                 { x=v.x; y=v.y; z=v.z; w=v.w; return(*this); }
             SEVec4<T>    &vec(const SEQuaternion<T> &q)                           { x=q.x; y=q.y; z=q.z; w=q.w; return(*this); }

             T             dot(const SEVec4<T> &a)                           const { return (x*a.x + y*a.y + z*a.z + w*a.w); }

             T             len2()                                            const { return (x*x + y*y + z*z + w*w); } // Quadrado do comprimento do vetor (0,0,0,0)->(x,y,z,w)
             T             len()                                             const { return (T)(sqrt(len2())); }  // Comprimento do vetor (0,0,0,0)->(x,y,z,w)

             SEVec4<T>     normal()                                          const { return SEVec4<T>(*this).normalize(); } // Retorna o vetor normalizado
             SEVec4<T>     inverse()                                         const { return -(*this); } // retorna o vetor inverso

             SEVec4<T>    &negate()                                                { x=-x;y=-y;z=-z;w=-w; return(*this); } // Inverte o vetor
             SEVec4<T>    &negate(const SEVec4<T> &v)                              { x=-v.x;y=-v.y;z=-v.z;w=-v.w; return(*this); }
             SEVec4<T>    &normalize()                                             { T inv_l = (T)1.0/len(); x*=inv_l; y*=inv_l; z*=inv_l; w*=inv_l; return(*this); }
             SEVec4<T>    &normalise()                                             { return normalize(); }
             SEVec4<T>    &normalize(const SEVec4<T> &v)                           { T inv_l = (T)1.0/v.len(); x=v.x*inv_l; y=v.y*inv_l; z=v.z*inv_l; w=v.w*inv_l; return(*this); }
             SEVec4<T>    &normalise(const SEVec4<T> &v)                           { return normalize(v); }

//             std::string   toString()                                        const { std::string s; s<<"("<<x<<", "<<y<<", "<<z<<", "<<w<<")"; return(s); }
};


template <class T> class SEQuaternion
{
  public:
             T                x, y, z, w;

    // default constructor
                              SEQuaternion()                                                                  : x(0),   y(0),   z(0),   w(1)   {}
    // copy constructor
                              SEQuaternion(const SEQuaternion<T> &c)                                          : x(c.x), y(c.y), z(c.z), w(c.w) {}

    // constrói o quaternion a partir de três ângulos de Euler
                              SEQuaternion(const T &euler_x, const T &euler_y, const T &euler_z)              { vec(euler_x, euler_y, euler_z); }
                              SEQuaternion(const T *e)                                                        { vec(e[0], e[1], e[2]); }
    explicit                  SEQuaternion(const SEVec3<T> &e)                                                { vec(e); }
    // constrói o quaternion a partir de um ângulo de rotação e um eixo
                              SEQuaternion(const T &angle, const T &axis_x, const T &axis_y, const T &axis_z) { vec(angle, axis_x, axis_y, axis_z); }
                              SEQuaternion(const T &angle, const SEVec3<T> &axis)                             { vec(angle, axis); }
    // constrói o quaternion a partir de uma matriz de transformação
    explicit                  SEQuaternion(const SEMat4<T> &m)                                                { vec(m); }
    // constrói um quaternion representando a rotação de um vetor v0 até o vetor v1
                              SEQuaternion(const SEVec3<T> &v0, const SEVec3<T> &v1)                          { rotto(v0, v1); }

    // destructor
                             ~SEQuaternion() {}

             SEQuaternion<T> &null()                                      { x=y=z=0;w=1; return(*this); } // função nulificadora
             SEQuaternion<T> &operator =(const SEQuaternion<T> &in)       { if (this!=(&in)) { return vec(in); } return(*this); }
             SEQuaternion<T> &operator =(const SEVec3<T> &e)              { return vec(e); }
             SEQuaternion<T>  operator -()                          const { return conjugate(); }

             SEQuaternion<T> &operator +=(const SEQuaternion<T> &v)       { x+=v.x; y+=v.y; z+=v.z; w+=v.w; return(*this); }
             SEQuaternion<T> &operator +=(const SEVec3<T> &e)             { return rotate(e); }
             SEQuaternion<T> &operator -=(const SEQuaternion<T> &v)       { x-=v.x; y-=v.y; z-=v.z; w-=v.w; return(*this); }
             SEQuaternion<T> &operator -=(const SEVec3<T> &e)             { return rotate(-e); }
             SEQuaternion<T> &operator *=(const T &a)                     { x*=a; y*=a; z*=a; w*=a; return(*this); }
             SEQuaternion<T> &operator /=(const T &a)                     { T inv_a = (T)1.0/a; x*=inv_a; y*=inv_a; z*=inv_a; w*=inv_a; return(*this); }
    // produto de Hamilton
             SEQuaternion<T> &operator *=(const SEQuaternion<T> &q)       { T tx = w*q.x + x*q.w + y*q.z - z*q.y,
                                                                              ty = w*q.y + y*q.w + z*q.x - x*q.z,
                                                                              tz = w*q.z + z*q.w + x*q.y - y*q.x,
                                                                              tw = w*q.w - x*q.x - y*q.y - z*q.z;

                                                                              x=tx; y=ty; z=tz; w=tw; return (*this); }

    friend   SEQuaternion<T>  operator +(SEQuaternion<T>        lhs, SEQuaternion<T> const &rhs) { return lhs += rhs; }
    friend   SEQuaternion<T>  operator +(SEQuaternion<T>        lhs, SEVec3<T>       const &rhs) { return lhs += rhs; }
    friend   SEQuaternion<T>  operator +(SEVec3<T>       const &lhs, SEQuaternion<T>        rhs) { return rhs += lhs; }
    friend   SEQuaternion<T>  operator -(SEQuaternion<T>        lhs, SEQuaternion<T> const &rhs) { return lhs -= rhs; }
    friend   SEQuaternion<T>  operator -(SEQuaternion<T>        lhs, SEVec3<T>       const &rhs) { return lhs -= rhs; }
    friend   SEQuaternion<T>  operator -(SEVec3<T>       const &lhs, SEQuaternion<T>        rhs) { return -rhs += lhs; }
    friend   SEQuaternion<T>  operator *(SEQuaternion<T>        lhs, T               const &rhs) { return lhs *= rhs; }
    friend   SEQuaternion<T>  operator *(T               const &lhs, SEQuaternion<T>        rhs) { return rhs *= lhs; }
    friend   SEVec3<T>        operator *(SEQuaternion<T> const &lhs, SEVec3<T>       const &rhs) { return lhs.quickmult(rhs); }
    friend   SEVec4<T>        operator *(SEQuaternion<T> const &lhs, SEVec4<T>       const &rhs) { return lhs.quickmult(rhs); }
    friend   SEQuaternion<T>  operator *(SEQuaternion<T>        lhs, SEQuaternion<T> const &rhs) { return lhs *= rhs; }
    friend   SEQuaternion<T>  operator /(SEQuaternion<T>        lhs, T               const &rhs) { return lhs /= rhs; }

             T               &operator [](std::size_t i)                                             { return (&x)[i]; }
             T                operator [](std::size_t i)                                       const { return (&x)[i]; }

             bool             operator ==(const SEQuaternion<T> &v)                            const { if (SEMathUtil<T>::ISZERO(ABS(x)-ABS(v.x)) && SEMathUtil<T>::ISZERO(ABS(y)-ABS(v.y)) && SEMathUtil<T>::ISZERO(ABS(z)-ABS(v.z)) && SEMathUtil<T>::ISZERO(ABS(w)-ABS(v.w))) return true; return false; }
             bool             operator !=(const SEQuaternion<T> &v)                            const { return (!(*this)==v); }

    friend   std::ostream    &operator<<(std::ostream &os, const SEQuaternion<T> &v)                 { os<<"("<<v.x<<", "<<v.y<<", "<<v.z<<", "<<v.w<<")"; return os; }

             SEQuaternion<T> &vec(const SEQuaternion<T> &q)                                          { x=q.x; y=q.y; z=q.z; w=q.w; return (*this); }
    // quaternion a partir de matriz de transformação
             SEQuaternion<T> &vec(const SEMat4<T> &m)                                                { return vec(m.toQuaternion()); }
    // quaternion a partir de ângulos de euler (em radianos)
             SEQuaternion<T> &vec(const SEVec3<T> &v)                                                { return vec(v.x, v.y, v.z); }
             SEQuaternion<T> &vec(const T &euler_x, const T &euler_y, const T &euler_z)              { T angle=euler_x*0.5; T sx=(T)sin(angle), cx=(T)cos(angle);
                                                                                                         angle=euler_y*0.5; T sy=(T)sin(angle), cy=(T)cos(angle);
                                                                                                         angle=euler_z*0.5; T sz=(T)sin(angle), cz=(T)cos(angle);

                                                                                                       T cycz=cy*cz, sycz=sy*cz, cysz=cy*sz, sysz=sy*sz;

                                                                                                         x = sx*cycz - cx*sysz; y = cx*sycz + sx*cysz;
                                                                                                         z = cx*cysz - sx*sycz; w = cx*cycz + sx*sysz;

                                                                                                         return normalize(); }
    // quaternion a partir de um eixo e um ângulo
             SEQuaternion<T> &vec(const T &angle, const T &axis_x, const T &axis_y, const T &axis_z) { return vec(angle, SEVec3<T>(axis_x, axis_y, axis_z)); }
             SEQuaternion<T> &vec(const T &angle, SEVec3<T> axis)                                    { T a=angle*0.5, s=(T)sin(a); axis.normalize();
                                                                                                         x=axis.x*s; y=axis.y*s; z=axis.z*s; w=(T)cos(a);
                                                                                                         return (*this); }

             T                dot(const SEQuaternion<T> &q)                                    const { return (x*q.x + y*q.y + z*q.z + w*q.w); } // Produto escalar entre Quaternions

             T                angdif(const SEQuaternion<T> &q)                                 const { return (T)arccos(dot(q)/(norm()*q.norm())); } // Diferença angular entre Quaternions
             T                angularDifference(const SEQuaternion<T> &q)                      const { return angdif(q); }

             SEQuaternion<T>  exp()                                                            const { T a=(T)sqrt(x*x + y*y + z*z), s=(T)sin(a), c=(T)cos(a), coef=1; int i;
                                                                                                         if (ABS(s)>=SEMathUtil<T>::EPSILON) coef=s/a;
                                                                                                         return SEQuaternion<T>(coef*x, coef*y, coef*z, c); }

             SEQuaternion<T>  log()                                                            const { T coef=1;
                                                                                                         if (ABS(w)<1.0) {
                                                                                                            T a=(T)acos(w), s=(T)sin(a);
                                                                                                            if (ABS(s)>=SEMathUtil<T>::EPSILON) coef=a/s;
                                                                                                         }
                                                                                                         return SEQuaternion<T>(coef*x, coef*y, coef*z, 0); }

             T                norm2()                                                          const { return (x*x+y*y+z*z+w*w); } // Quadrado da norma do Quaternion
             T                len2()                                                           const { return norm2(); }
             T                norm()                                                           const { return (T)(sqrt(norm2())); }  // Norma do Quaternion
             T                len()                                                            const { return norm(); }

             T                angle()                                                          const { return (anglerad()*SEMathUtil<T>::PIUNDER180); } // Ângulo de rotação do quaternion
             T                anglerad()                                                       const { return ((T)acos(w)*2); } // Ângulo de rotação do quaternion (em radianos)
             T                rotationAngle()                                                  const { return angle(); }
             T                rotationAngleInRadians()                                         const { return anglerad(); }
             T                getRotationAngle()                                               const { return angle(); }
             T                getRotationAngleInRadians()                                      const { return anglerad(); }

             SEVec3<T>        axis()                                                           const { T inv_a = (T)(1/sin(acos(w))); return SEVec3<T>(x*inv_a,y*inv_a,z*inv_a); } // Eixo de rotação do quaternion
             SEVec3<T>        rotationAxis()                                                   const { return axis(); }
             SEVec3<T>        getRotationAxis()                                                const { return axis(); }

             SEQuaternion<T>  normal()                                                         const { return SEQuaternion<T>(*this).normalize(); } // Quaternion normalizado
             SEQuaternion<T>  inverse()                                                        const { return conjugate()/norm2(); } // Quaternion inverso
             SEQuaternion<T>  conjugate()                                                      const { return SEQuaternion<T>(-x, -y, -z, w); } // Conjugado do Quaternion

             SEQuaternion<T> &negate()                                                               { return (*this)=conjugate(); }
             SEQuaternion<T> &negate(const SEQuaternion<T> &q)                                       { return (*this)=q.conjugate(); }
             SEQuaternion<T> &invert()                                                               { return (*this)=inverse(); }
             SEQuaternion<T> &invert(const SEQuaternion<T> &q)                                       { return (*this)=q.inverse(); }
             SEQuaternion<T> &normalize()                                                            { T inv_n = (T)1/norm(); x*=inv_n; y*=inv_n; z*=inv_n; w*=inv_n; return(*this); }
             SEQuaternion<T> &normalise()                                                            { return normalize(); }
             SEQuaternion<T> &normalize(const SEQuaternion<T> &q)                                    { T inv_n = (T)1/q.norm(); x=q.x*inv_n; y=q.y*inv_n; z=q.z*inv_n; w=q.w*inv_n; return(*this); }
             SEQuaternion<T> &normalise(const SEQuaternion<T> &q)                                    { return normalize(q); }
             // rotação de v0 a v1
             SEQuaternion<T> &rotationFromTo(const SEVec3<T> &v0, const SEVec3<T> &v1)               { return rotto(v0,v1); }
             SEQuaternion<T> &rotto(const SEVec3<T> &v0, const SEVec3<T> &v1)                        { SEVec3<T> from(v0.normal()), to(v1.normal);
                                                                                                       T         d = CLAMP(from.dot(to),-1,1);
                                                                                                       if (SEMathUtil<T>::ISZERO(d-1)) // vetores são iguais
                                                                                                         return null();
                                                                                                       else if (SEMathUtil<T>::ISZERO(d+1)) { // vetores são opostos
                                                                                                         SEVec3<T> a(1,0,0); a.cross(from);
                                                                                                         if (SEMathUtil<T>::ISZERO(a.len())) { // vetores são paralelos ao eixo unitário X, usa o eixo Y no lugar
                                                                                                           a.vec(0,1,0); a.cross(from);
                                                                                                         }
                                                                                                         x=a.x; y=a.y; z=a.z; w=0; return normalize();
                                                                                                       }
                                                                                                       T         s = (T)sqrt((1+d)*2), inv_s = 1 / s;
                                                                                                       SEVec3<T> c = from.cross(to)*inv_s;
                                                                                                       x=c.x; y=c.y; z=c.z; w=s*0.5; return normalize(); }

             SEMat3<T>        toMatrix3()                                                      const { return mat3(); }
             SEMat3<T>        toRotationMatrix()                                               const { return mat3(); }
             SEMat3<T>        mat3()                                                           const { T xx = x*x, xy = x*y, xz = x*z, xw = x*w,
                                                                                                         yy = y*y, yz = y*z, yw = y*w,
                                                                                                         zz = z*z, zw = z*w;

                                                                                                         return SEMat3<T>(1 - 2*(yy+zz),     2*(xy-zw),     2*(xz+yw),
                                                                                                                              2*(xy+zw), 1 - 2*(xx+zz),     2*(yz-xw),
                                                                                                                              2*(xz-yw),     2*(yz+xw), 1 - 2*(xx+yy)); }

             SEMat4<T>        toMatrix()                                                       const { return mat4(); }
             SEMat4<T>        toMatrix4()                                                      const { return mat4(); }
             SEMat4<T>        toTransformMatrix()                                              const { return mat4(); }
             SEMat4<T>        mat4()                                                           const { T xx = x*x, xy = x*y, xz = x*z, xw = x*w,
                                                                                                         yy = y*y, yz = y*z, yw = y*w,
                                                                                                         zz = z*z, zw = z*w;

                                                                                                         return SEMat4<T>(1 - 2*(yy+zz),     2*(xy-zw),     2*(xz+yw), 0,
                                                                                                                              2*(xy+zw), 1 - 2*(xx+zz),     2*(yz-xw), 0,
                                                                                                                              2*(xz-yw),     2*(yz+xw), 1 - 2*(xx+yy), 0,
                                                                                                                                      0,             0,             0, 1); }

             SEQuaternion<T> &rotateGloballyByDegrees(const T &angle, const T &axisX, const T &axisY, const T &axisZ) { return grotate(SEMathUtil<T>::rad(angle), SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &rotateGloballyByDegrees(const T &angle, const SEVec3<T> &axis)                          { return grotate(SEQuaternion<T>(SEMathUtil<T>::rad(angle), axis)); }
             SEQuaternion<T> &rotateGlobally(const T &angle, const T &axisX, const T &axisY, const T &axisZ)          { return grotate(angle, SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &rotateGlobally(const T &angle, const SEVec3<T> &axis)                                   { return grotate(SEQuaternion<T>(angle, axis)); }
             SEQuaternion<T> &rotateGlobally(const SEQuaternion<T> q)                                                 { return grotate(q); }
             SEQuaternion<T> &grotateByDegrees(const T &angle, const T &axisX, const T &axisY, const T &axisZ)        { return grotate(SEMathUtil<T>::rad(angle), SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &grotateByDegrees(const T &angle, const SEVec3<T> &axis)                                 { return grotate(SEQuaternion<T>(SEMathUtil<T>::rad(angle), axis)); }
             SEQuaternion<T> &grotate(const T &angle, const T &axisX, const T &axisY, const T &axisZ)                 { return grotate(angle, SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &grotate(const T &angle, const SEVec3<T> &axis)                                          { return grotate(SEQuaternion<T>(angle, axis)); }
    // rotação no espaço de referência global
             SEQuaternion<T> &grotate(const SEQuaternion<T> q)                                                        { (*this) = q*(*this);
                                                                                                                        if (!SEMathUtil<T>::ISZERO(norm2()-1))
                                                                                                                          normalize();
                                                                                                                        return(*this); }

             SEQuaternion<T> &rotateLocallyByDegrees(const T &angle, const T &axisX, const T &axisY, const T &axisZ)  { return rotate(SEMathUtil<T>::rad(angle), SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &rotateLocallyByDegrees(const T &angle, const SEVec3<T> &axis)                           { return rotate(SEQuaternion<T>(SEMathUtil<T>::rad(angle), axis)); }
             SEQuaternion<T> &rotateLocally(const T &angle, const T &axisX, const T &axisY, const T &axisZ)           { return rotate(angle, SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &rotateLocally(const T &angle, const SEVec3<T> &axis)                                    { return rotate(SEQuaternion<T>(angle, axis)); }
             SEQuaternion<T> &rotateLocally(const SEQuaternion<T> q)                                                  { return rotate(q); }
             SEQuaternion<T> &rotateByDegrees(const T &angle, const T &axisX, const T &axisY, const T &axisZ)         { return rotate(SEMathUtil<T>::rad(angle), SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &rotateByDegrees(const T &angle, const SEVec3<T> &axis)                                  { return rotate(SEQuaternion<T>(SEMathUtil<T>::rad(angle), axis)); }
             SEQuaternion<T> &rotate(const T &angle, const T &axisX, const T &axisY, const T &axisZ)                  { return rotate(angle, SEVec3<T>(axisX,axisY,axisZ)); }
             SEQuaternion<T> &rotate(const T &angle, const SEVec3<T> &axis)                                           { return rotate(SEQuaternion<T>(angle, axis)); }
    // rotação no espaço de referência local
             SEQuaternion<T> &rotate(const SEQuaternion<T> q)                                                         { (*this)*=q;
                                                                                                                        if (!SEMathUtil<T>::ISZERO(norm2()-1))
                                                                                                                          normalize();
                                                                                                                        return(*this); }


    // atalhos para rotacionar quaternion por um ângulo
             SEQuaternion<T> &rotateGloballyByDegreesInX(const T &angle)                                              { return grotate(SEMathUtil<T>::rad(angle), 1, 0, 0); }
             SEQuaternion<T> &rotateGloballyByDegreesInY(const T &angle)                                              { return grotate(SEMathUtil<T>::rad(angle), 0, 1, 0); }
             SEQuaternion<T> &rotateGloballyByDegreesInZ(const T &angle)                                              { return grotate(SEMathUtil<T>::rad(angle), 0, 0, 1); }
             SEQuaternion<T> &grotateByDegreesInX(const T &angle)                                                     { return grotate(SEMathUtil<T>::rad(angle), 1, 0, 0); }
             SEQuaternion<T> &grotateByDegreesInY(const T &angle)                                                     { return grotate(SEMathUtil<T>::rad(angle), 0, 1, 0); }
             SEQuaternion<T> &grotateByDegreesInZ(const T &angle)                                                     { return grotate(SEMathUtil<T>::rad(angle), 0, 0, 1); }

             SEQuaternion<T> &rotateGloballyInX(const T &angle)                                                       { return grotate(angle, 1, 0, 0); }
             SEQuaternion<T> &rotateGloballyInY(const T &angle)                                                       { return grotate(angle, 0, 1, 0); }
             SEQuaternion<T> &rotateGloballyInZ(const T &angle)                                                       { return grotate(angle, 0, 0, 1); }
             SEQuaternion<T> &grotateInX(const T &angle)                                                              { return grotate(angle, 1, 0, 0); }
             SEQuaternion<T> &grotateInY(const T &angle)                                                              { return grotate(angle, 0, 1, 0); }
             SEQuaternion<T> &grotateInZ(const T &angle)                                                              { return grotate(angle, 0, 0, 1); }
             SEQuaternion<T> &grotatex(const T &angle)                                                                { return grotate(angle, 1, 0, 0); }
             SEQuaternion<T> &grotatey(const T &angle)                                                                { return grotate(angle, 0, 1, 0); }
             SEQuaternion<T> &grotatez(const T &angle)                                                                { return grotate(angle, 0, 0, 1); }

             SEQuaternion<T> &rotateLocallyByDegreesInX(const T &angle)                                               { return rotate(SEMathUtil<T>::rad(angle), 1, 0, 0); }
             SEQuaternion<T> &rotateLocallyByDegreesInY(const T &angle)                                               { return rotate(SEMathUtil<T>::rad(angle), 0, 1, 0); }
             SEQuaternion<T> &rotateLocallyByDegreesInZ(const T &angle)                                               { return rotate(SEMathUtil<T>::rad(angle), 0, 0, 1); }
             SEQuaternion<T> &rotateByDegreesInX(const T &angle)                                                      { return rotate(SEMathUtil<T>::rad(angle), 1, 0, 0); }
             SEQuaternion<T> &rotateByDegreesInY(const T &angle)                                                      { return rotate(SEMathUtil<T>::rad(angle), 0, 1, 0); }
             SEQuaternion<T> &rotateByDegreesInZ(const T &angle)                                                      { return rotate(SEMathUtil<T>::rad(angle), 0, 0, 1); }

             SEQuaternion<T> &rotateLocallyInX(const T &angle)                                                        { return rotate(angle, 1, 0, 0); }
             SEQuaternion<T> &rotateLocallyInY(const T &angle)                                                        { return rotate(angle, 0, 1, 0); }
             SEQuaternion<T> &rotateLocallyInZ(const T &angle)                                                        { return rotate(angle, 0, 0, 1); }
             SEQuaternion<T> &rotateInX(const T &angle)                                                               { return rotate(angle, 1, 0, 0); }
             SEQuaternion<T> &rotateInY(const T &angle)                                                               { return rotate(angle, 0, 1, 0); }
             SEQuaternion<T> &rotateInZ(const T &angle)                                                               { return rotate(angle, 0, 0, 1); }
             SEQuaternion<T> &rotatex(const T &angle)                                                                 { return rotate(angle, 1, 0, 0); }
             SEQuaternion<T> &rotatey(const T &angle)                                                                 { return rotate(angle, 0, 1, 0); }
             SEQuaternion<T> &rotatez(const T &angle)                                                                 { return rotate(angle, 0, 0, 1); }

             SEQuaternion<T> lerp(const SEQuaternion<T> &q0, const SEQuaternion<T> &q1, T t)                          { T compl_t = 1.0-t;
                                                                                                                        return ((q0*compl_t) + (q1*t)); }

             SEQuaternion<T> slerp(const SEQuaternion<T> &q0, const SEQuaternion<T> &q1, T t)                         { T c = CLAMP(q0.dot(q1),-1,1);
                                                                                                                        if (SEMathUtil<T>::ISZERO(ABS(c)-1.0))
                                                                                                                          return SEQuaternion<T>(q0);

                                                                                                                        T a = (T)acos(c), s = (T)sqrt(1.0 - c*c);
                                                                                                                        if (SEMathUtil<T>::ISZERO(ABS(s)))
                                                                                                                          return ((q0+q1)*0.5);

                                                                                                                        return (q0*(T)(sin((1-t) * a) / s))+(q1*(T)(sin(t * a) / s)); }

             SEQuaternion<T> nlerp(const SEQuaternion<T> &q0, const SEQuaternion<T> &q1, T t)                         { T c = CLAMP(q0.dot(q1),-1,1);
                                                                                                                        if (SEMathUtil<T>::ISZERO(ABS(c)-1.0))
                                                                                                                          return SEQuaternion<T>(q0 + t*(q1-q0)).normalize();

                                                                                                                        T a0 = (T)acos(c), a = a0*t;

                                                                                                                        return (q0*(T)cos(a) + (q1-q0*c).normal()*(T)sin(a)); }
    // Multiplicação rápida de quaternion por vetores
             SEVec3<T>       leftMultiplyAsMatrix(const SEVec3<T> &ve)                                          const { return lmatmult(ve); }
             SEVec3<T>       lmatmult(const SEVec3<T> &ve)                                                      const { return ve*(mat3().transpose()); }
             SEVec3<T>       rightMultiplyAsMatrix(const SEVec3<T> &ve)                                         const { return rmatmult(ve); }
             SEVec3<T>       rmatmult(const SEVec3<T> &ve)                                                      const { return ve*mat3(); }

             SEVec4<T>       leftMultiplyAsMatrix(const SEVec4<T> &ve)                                          const { return lmatmult(ve); }
             SEVec4<T>       lmatmult(const SEVec4<T> &ve)                                                      const { return ve*(mat4().transpose()); }
             SEVec4<T>       rightMultiplyAsMatrix(const SEVec4<T> &ve)                                         const { return rmatmult(ve); }
             SEVec4<T>       rmatmult(const SEVec4<T> &ve)                                                      const { return ve*mat4(); }

             SEVec3<T>       quickMultiply(const SEVec3<T> &ve)                                                 const { return quickmult(ve); }
             SEVec3<T>       quickmult(const SEVec3<T> &ve)                                                     const { T tx = x + w*ve.x + y*ve.z - z*ve.y,
                                                                                                                          ty = y + w*ve.y + z*ve.x - x*ve.z,
                                                                                                                          tz = z + w*ve.z + x*ve.y - y*ve.x,
                                                                                                                          tw = w - x*ve.x - y*ve.y - z*ve.z;

                                                                                                                        return SEVec3<T>( tx*w - tw*x - ty*z + tz*y,
                                                                                                                                          ty*w - tw*y - tz*x + tx*z,
                                                                                                                                          tz*w - tw*z - tx*y + ty*x); }

             SEVec3<T>       quickVectorMultiply(const SEVec3<T> &ve)                                           const { return quickvmult(ve); }
             SEVec3<T>       quickvmult(const SEVec3<T> &ve)                                                    const { T tx =  w*ve.x + y*ve.z - z*ve.y,
                                                                                                                          ty =  w*ve.y + z*ve.x - x*ve.z,
                                                                                                                          tz =  w*ve.z + x*ve.y - y*ve.x,
                                                                                                                          tw = -x*ve.x - y*ve.y - z*ve.z;

                                                                                                                        return SEVec3<T>( tx*w - tw*x - ty*z + tz*y,
                                                                                                                                          ty*w - tw*y - tz*x + tx*z,
                                                                                                                                          tz*w - tw*z - tx*y + ty*x); }

             SEVec4<T>       quickMultiply(const SEVec4<T> &ve)                                                 const { return quickmult(ve); }
             SEVec4<T>       quickmult(const SEVec4<T> &ve)                                                     const { T tx = w*ve.x + x*ve.w + y*ve.z - z*ve.y,
                                                                                                                          ty = w*ve.y + y*ve.w + z*ve.x - x*ve.z,
                                                                                                                          tz = w*ve.z + z*ve.w + x*ve.y - y*ve.x,
                                                                                                                          tw = w*ve.w - x*ve.x - y*ve.y - z*ve.z;

                                                                                                                        return SEVec4<T>(tx*w - tw*x - ty*z + tz*y,
                                                                                                                                         ty*w - tw*y - tz*x + tx*z,
                                                                                                                                         tz*w - tw*z - tx*y + ty*x,
                                                                                                                                         tw*w + tx*x + ty*y + tz*z); }
};


template <class T> class SEMat3
{
  public:
             T               m[9];

    // Referências diretas para os elementos
             T              &m00,
                            &m01,
                            &m02,
                            &m10,
                            &m11,
                            &m12,
                            &m20,
                            &m21,
                            &m22,
    // Referências diretas para as linhas
                            *r1,
                            *r2,
                            *r3;

                             SEMat3()
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { null(); }

    explicit                 SEMat3(const T &v)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { set(v); }

    explicit                 SEMat3(const SEVec3<T> &v)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { set(v); }

    explicit                 SEMat3(const T *c)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { set(c); }

    explicit                 SEMat3(const T **v)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             {  set(v); }

                             SEMat3(const SEVec3<T> &v1, const SEVec3<T> &v2, const SEVec3<T> &v3)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { set(v1, v2, v3); }

                             SEMat3(const T &n00, const T &n01, const T &n02,
                                    const T &n10, const T &n11, const T &n12,
                                    const T &n20, const T &n21, const T &n22)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { set(n00,n01,n02,n10,n11,n12,n20,n21,n22); }
    // copy constructor
                             SEMat3(const SEMat3<T> &n)
                               : m00(m[0]), m01(m[1]), m02(m[2]),
                                 m10(m[3]), m11(m[4]), m12(m[5]),
                                 m20(m[6]), m21(m[7]), m22(m[8]),
                                 r1(m), r2(m+3), r3(m+6)
                             { set(n); }
    // destructor
                            ~SEMat3() {}

             SEMat3<T>      &operator =(const SEMat3<T> &n)       { if (this!=(&n)) { return set(n); } return(*this); }
             SEMat3<T>       operator -()                   const { return SEMat3<T>(-m[0],-m[1],-m[2],-m[3],-m[4],-m[5],-m[6],-m[7],-m[8]); }

             SEMat3<T>      &operator +=(const SEMat3<T> &n)      { for (int i=0;i<9;i++) m[i]+=n[i]; return(*this); }
             SEMat3<T>      &operator -=(const SEMat3<T> &n)      { for (int i=0;i<9;i++) m[i]-=n[i]; return(*this); }
             SEMat3<T>      &operator *=(const T &a)              { for (int i=0;i<9;i++) m[i]*=a; return(*this); }
             SEMat3<T>      &operator /=(const T &a)              { for (int i=0;i<9;i++) m[i]/=a; return(*this); }

             SEMat3<T>      &operator *=(const SEMat3<T> &n)      { return set(m[0]*n[0]+m[1]*n[3]+m[2]*n[6] , m[0]*n[1]+m[1]*n[4]+m[2]*n[7] , m[0]*n[2]+m[1]*n[5]+m[2]*n[8],
                                                                               m[3]*n[0]+m[4]*n[3]+m[5]*n[6] , m[3]*n[1]+m[4]*n[4]+m[5]*n[7] , m[3]*n[2]+m[4]*n[5]+m[5]*n[8],
                                                                               m[6]*n[0]+m[7]*n[3]+m[8]*n[6] , m[6]*n[1]+m[7]*n[4]+m[8]*n[7] , m[6]*n[2]+m[7]*n[5]+m[8]*n[8]); }

    friend   SEMat3<T>       operator +(SEMat3<T>        lhs, SEMat3<T> const &rhs) { return lhs += rhs; }
    friend   SEMat3<T>       operator -(SEMat3<T>        lhs, SEMat3<T> const &rhs) { return lhs -= rhs; }
    friend   SEMat3<T>       operator *(SEMat3<T>        lhs, T         const &rhs) { return lhs *= rhs; }
    friend   SEMat3<T>       operator *(T         const &lhs, SEMat3<T>        rhs) { return rhs *= lhs; }
    friend   SEMat3<T>       operator *(SEMat3<T>        lhs, SEMat3<T> const &rhs) { return lhs *= rhs; }
    friend   SEMat3<T>       operator /(SEMat3<T>        lhs, T         const &rhs) { return lhs /= rhs; }
    friend   SEVec3<T>       operator *(SEMat3<T> const &lhs, SEVec3<T> const &rhs) { return rhs *  lhs.transpose(); } // como a multiplicação só está definida para row-major, transpõe a matriz para simular multiplicação column-major

             T              &operator [](std::size_t i)                                         { return m[i]; }
             T               operator [](std::size_t i)                                   const { return m[i]; }

             bool            operator ==(const SEMat3<T> &n)                              const { for (int i=0;i<9;++i) if (m[i]!=n[i]) return false; return true; }
             bool            operator !=(const SEMat3<T> &n)                              const { return (!(*this)==n); }

    friend   std::ostream   &operator <<(std::ostream &os, const SEMat3<T> &m)                  { os<<"|"<<m.m00<<"\t"<<m.m01<<"\t"<<m.m02<<"|\n|"<<m.m10<<"\t"<<m.m11<<"\t"<<m.m12<<"|\n|"<<m.m20<<"\t"<<m.m21<<"\t"<<m.m22<<"|"; return os; }

             T               trace()                                                      const { return (m00+m11+m22); }

             SEMat3<T>       transposed()                                                 const { return SEMat3<T>(*this).transpose(); }

             SEMat3<T>      &null()                                                             { for (int i=0;i<9;++i) m[i]=0; return(*this); } //função nulificadora
             SEMat3<T>      &identity()                                                         { null(); m00=m11=m22=1; return(*this); }
             SEMat3<T>      &transpose()                                                        { SEMathUtil<T>::SWAP(m01,m10); SEMathUtil<T>::SWAP(m02,m20); SEMathUtil<T>::SWAP(m12,m21); return(*this); }
             SEMat3<T>      &transpose(const SEMat3<T> &m)                                      { (*this)=m; return(transpose()); }


             SEMat3<T>      &set(const T &f)                                                    { null(); m00=m11=m22=f; return(*this); }
             SEMat3<T>      &set(const SEVec3<T> &v)                                            { null(); m00=v.x;m11=v.y;m22=v.z; return(*this); }
             SEMat3<T>      &set(const SEVec3<T> &v1, const SEVec3<T> &v2, const SEVec3<T> &v3) { for (int i=0;i<3;++i) { r1[i]=v1[i];r2[i]=v2[i];r3[i]=v3[i]; } return(*this); }
             SEMat3<T>      &set(const T *c)                                                    { for (int i=0;i<9;++i) m[i]=c[i]; return(*this); }
             SEMat3<T>      &set(const T **v)                                                   { for (int i=0;i<3;++i) { r1[i]=v[0][i];r2[i]=v[1][i];r3[i]=v[2][i]; } return(*this); }
             SEMat3<T>      &set(const SEMat3<T> &n)                                            { for (int i=0;i<9;++i) m[i]=n[i]; return(*this); }
             SEMat3<T>      &set(const T &n00, const T &n01, const T &n02,
                                 const T &n10, const T &n11, const T &n12,
                                 const T &n20, const T &n21, const T &n22)                      { m00=n00; m01=n01; m02=n02; m10=n10; m11=n11; m12=n12; m20=n20; m21=n21; m22=n22; return(*this); }

};


template <class T> class SEMat4
{
  public:
             T                m[16];

    // Referências diretas para os elementos
             T               &m00,
                             &m01,
                             &m02,
                             &m03,
                             &m10,
                             &m11,
                             &m12,
                             &m13,
                             &m20,
                             &m21,
                             &m22,
                             &m23,
                             &m30,
                             &m31,
                             &m32,
                             &m33,
    // Referências diretas para as linhas
                             *r1,
                             *r2,
                             *r3,
                             *r4;

                              SEMat4()
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { null(); }

    explicit                  SEMat4(const T &v)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(v); }

    explicit                  SEMat4(const SEVec3<T> &v)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(v); }

    explicit                  SEMat4(const SEVec4<T> &v)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(v); }

    explicit                  SEMat4(const SEQuaternion<T> &v)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(v); }

    explicit                  SEMat4(const T *c)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(c); }

    explicit                  SEMat4(const T **v)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(v); }

                              SEMat4(const SEVec4<T> &v1, const SEVec4<T> &v2, const SEVec4<T> &v3, const SEVec4<T> &v4)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { for (int i=0;i<4;++i) { r1[i]=v1[i];r2[i]=v2[i];r3[i]=v3[i];r4[i]=v4[i]; } }

                              SEMat4(const T &n00, const T &n01, const T &n02, const T &n03,
                                     const T &n10, const T &n11, const T &n12, const T &n13,
                                     const T &n20, const T &n21, const T &n22, const T &n23,
                                     const T &n30, const T &n31, const T &n32, const T &n33)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(n00,n01,n02,n03,n10,n11,n12,n13,n20,n21,n22,n23,n30,n31,n32,n33); }
    // copy constructor
                              SEMat4(const SEMat4<T> &n)
                                : m00(m[0]),  m01(m[1]),  m02(m[2]),  m03(m[3]),
                                  m10(m[4]),  m11(m[5]),  m12(m[6]),  m13(m[7]),
                                  m20(m[8]),  m21(m[9]),  m22(m[10]), m23(m[11]),
                                  m30(m[12]), m31(m[13]), m32(m[14]), m33(m[15]),
                                  r1(m), r2(m+4), r3(m+8), r4(m+12)
                              { set(n); }
    // destructor
                             ~SEMat4() {}

             SEMat4<T>       &operator =(const SEMat4<T> &n)       { if (this!=(&n)) return set(n); return(*this); }
             SEMat4<T>        operator -()                   const { SEMat4<T> r; for (int i=0;i<16;i++) r[i]=-m[i]; return(r); }

             SEMat4<T>       &operator +=(const SEMat4<T> &n)      { for (int i=0;i<16;i++) m[i]+=n[i]; return(*this); }
             SEMat4<T>       &operator -=(const SEMat4<T> &n)      { for (int i=0;i<16;i++) m[i]-=n[i]; return(*this); }
             SEMat4<T>       &operator *=(const T &a)              { for (int i=0;i<16;i++) m[i]*=a; return(*this); }
             SEMat4<T>       &operator *=(const SEMat4<T> &n)      { (*this)=SEMat4<T>(m[0]*n[0]  + m[1]*n[4]  + m[2]*n[8]   + m[3]*n[12] , m[0]*n[1]  + m[1]*n[5]  + m[2]*n[9]   + m[3]*n[13] , m[0]*n[2]  + m[1]*n[6]  + m[2]*n[10]  + m[3]*n[14] , m[0]*n[3]  + m[1]*n[7]  + m[2]*n[11]  + m[3]*n[15] ,
                                                                                       m[4]*n[0]  + m[5]*n[4]  + m[6]*n[8]   + m[7]*n[12] , m[4]*n[1]  + m[5]*n[5]  + m[6]*n[9]   + m[7]*n[13] , m[4]*n[2]  + m[5]*n[6]  + m[6]*n[10]  + m[7]*n[14] , m[4]*n[3]  + m[5]*n[7]  + m[6]*n[11]  + m[7]*n[15] ,
                                                                                       m[8]*n[0]  + m[9]*n[4]  + m[10]*n[8]  + m[11]*n[12], m[8]*n[1]  + m[9]*n[5]  + m[10]*n[9]  + m[11]*n[13], m[8]*n[2]  + m[9]*n[6]  + m[10]*n[10] + m[11]*n[14], m[8]*n[3]  + m[9]*n[7]  + m[10]*n[11] + m[11]*n[15],
                                                                                       m[12]*n[0] + m[13]*n[4] + m[14]*n[8]  + m[15]*n[12], m[12]*n[1] + m[13]*n[5] + m[14]*n[9]  + m[15]*n[13], m[12]*n[2] + m[13]*n[6] + m[14]*n[10] + m[15]*n[14], m[12]*n[3] + m[13]*n[7] + m[14]*n[11] + m[15]*n[15]);
                                                                     return (*this); }
             SEMat4<T>       &operator /=(const T &a)              { for (int i=0;i<16;i++) m[i]/=a; return(*this); }

    friend   SEMat4<T>        operator +(SEMat4<T>        lhs, SEMat4<T> const &rhs) { return lhs += rhs; }
    friend   SEMat4<T>        operator -(SEMat4<T>        lhs, SEMat4<T> const &rhs) { return lhs -= rhs; }
    friend   SEMat4<T>        operator *(SEMat4<T>        lhs, T         const &rhs) { return lhs *= rhs; }
    friend   SEMat4<T>        operator *(T         const &lhs, SEMat4<T>        rhs) { return rhs *= lhs; }
    friend   SEMat4<T>        operator *(SEMat4<T>        lhs, SEMat4<T> const &rhs) { return lhs *= rhs; }
    friend   SEMat4<T>        operator /(SEMat4<T>        lhs, T         const &rhs) { return lhs /= rhs; }
    friend   SEVec4<T>        operator *(SEMat4<T> const &lhs, SEVec4<T> const &rhs) { return rhs *  lhs.transpose(); } // como a multiplicação só está definida para row-major, transpõe a matriz para simular multiplicação column-major

             T               &operator [](std::size_t i)                                  { return m[i]; }
             T                operator [](std::size_t i)                            const { return m[i]; }

             bool             operator ==(const SEMat4<T> &n)                       const { for (int i=0;i<16;++i) if (m[i]!=n[i]) return false; return true; }
             bool             operator !=(const SEMat4<T> &n)                       const { return (!(*this)==n); }

    friend   std::ostream    &operator <<(std::ostream &os, const SEMat4<T> &m)           { os<<"|"<<m.m00<<"\t"<<m.m01<<"\t"<<m.m02<<"\t"<<m.m03<<"|\n|"<<m.m10<<"\t"<<m.m11<<"\t"<<m.m12<<"\t"<<m.m13<<"|\n|"<<m.m20<<"\t"<<m.m21<<"\t"<<m.m22<<"\t"<<m.m23<<"|\n|"<<m.m30<<"\t"<<m.m31<<"\t"<<m.m32<<"\t"<<m.m33<<"|"; return os; }

             T                trace()                                               const { return (m00+m11+m22+m33); }

             SEMat4<T>        transposed()                                          const { SEMat4 t(*this); return(t.transpose()); }

             SEMat4<T>       &null()                                                      { for (int i=0;i<16;++i) m[i]=0; return(*this); } //função nulificadora
             SEMat4<T>       &identity()                                                  { null(); m00=m11=m22=m33=1; return(*this); }
             SEMat4<T>       &transpose()                                                 { SEMathUtil<T>::SWAP(m01,m10); SEMathUtil<T>::SWAP(m02,m20); SEMathUtil<T>::SWAP(m03,m30); SEMathUtil<T>::SWAP(m12,m21); SEMathUtil<T>::SWAP(m13,m31); SEMathUtil<T>::SWAP(m23,m32); return(*this); }
             SEMat4<T>       &transpose(const SEMat4<T> &m)                               { (*this)=m; return(transpose()); }

             SEMat4<T>       &set(const T &f)                                             { null(); m00=m11=m22=m33=f; return(*this); }
             SEMat4<T>       &set(const SEVec3<T> &v)                                     { return (*this)=v.mat(); }
             SEMat4<T>       &set(const SEVec4<T> &v)                                     { null(); m00=v.x;m11=v.y;m22=v.z;m33=v.w; return(*this); }
             SEMat4<T>       &set(const SEQuaternion<T> &v)                               { (*this)=v.toMatrix(); return(*this); }
             SEMat4<T>       &set(const T *c)                                             { for (int i=0;i<16;++i) m[i]=c[i]; return(*this); }
             SEMat4<T>       &set(const T **v)                                            { for (int i=0;i<4;++i) { r1[i]=v[0][i];r2[i]=v[1][i];r3[i]=v[2][i];r4[i]=v[3][i]; } return(*this); }
             SEMat4<T>       &set(const SEMat4<T> &n)                                     { for (int i=0;i<16;++i) m[i]=n[i]; return(*this); }
             SEMat4<T>       &set(const T &n00, const T &n01, const T &n02, const T &n03,
                                  const T &n10, const T &n11, const T &n12, const T &n13,
                                  const T &n20, const T &n21, const T &n22, const T &n23,
                                  const T &n30, const T &n31, const T &n32, const T &n33) { m00=n00; m01=n01; m02=n02; m03=n03;
                                                                                            m10=n10; m11=n11; m12=n12; m13=n13;
                                                                                            m20=n20; m21=n21; m22=n22; m23=n23;
                                                                                            m30=n30; m31=n31; m32=n32; m33=n33;
                                                                                            return(*this); }


             SEQuaternion<T>  toQuaternion() { T tr = trace();
                                               SEQuaternion<T> r;
                                                 if( tr > 0 ) {
                                                   T s = 0.5 / (T)sqrt(tr + 1);
                                                   r.x=(m21-m12)*s; r.y=(m02-m20)*s; r.z=(m10-m01)*s; r.w=0.25/s;
                                                 } else if (m00 > m11 && m00 > m22) {
                                                   T s = 2 * (T)sqrt(1 + m00 - m11 - m22);
                                                   r.x=0.25*s; r.y=(m01+m10)/s; r.z=(m02+m20)/s; r.w=(m21-m12)/s;
                                                 } else if (m11 > m22) {
                                                   T s = 2 * (T)sqrt(1 + m11 - m00 - m22);
                                                   r.x=(m01+m10)/s; r.y=0.25*s; r.z=(m12+m21)/s; r.w=(m02-m20)/s;
                                                 } else {
                                                   T s = 2 * (T)sqrt(1 + m22 - m00 - m11);
                                                   r.x=(m02+m20)/s; r.y=(m12+m21)/s; r.z=0.25*s; r.w=(m10-m01)/s;
                                                 }
                                                 return (r); }

};

template <class T> class SERay
{
  private:
            SEVec3<T>          o_,
                               d_;

  public:
    const   SEVec3<T>         &o,
                              &d;

                               SERay()                                           : o(o_), d(d_) { setOrigin(0,0,0); setDirection(1,0,0); }
                               SERay(const SEVec3<T> &dir)                       : o(o_), d(d_) { setOrigin(0,0,0); setDirection(dir); }
                               SERay(const SEVec3<T> &org, const SEVec3<T> &dir) : o(o_), d(d_) { setOrigin(org); setDirection(dir); }
                               SERay(const SERay<T> &r)                          : o(o_), d(d_) { setOrigin(r.o); setDirection(r.d); }
                               SERay(T x, T y, T z, T r, T s, T t)               : o(o_), d(d_) { setOrigin(x,y,z); setDirection(r,s,t); }

                              ~SERay() {}

            SERay<T>          &setOrigin(T x, T y, T z)           { o_.x=x; o_.y=y; o_.z=z; return(this); }
            SERay<T>          &setOrigin(const SEVec3<T> &org)    { return setOrigin(org.x, org.y, org.z); }
            SERay<T>          &setOrigin(const SEVec4<T> &org)    { return setOrigin(org.x, org.y, org.z); }

            SERay<T>          &setDirection(T x, T y, T z)        { d_.x=x; d_.y=y; d_.z=z; d_.normalize(); return(this); }
            SERay<T>          &setDirection(const SEVec3<T> &dir) { return setDirection(dir.x, dir.y, dir.z); }
            SERay<T>          &setDirection(const SEVec4<T> &dir) { return setDirection(dir.x, dir.y, dir.z); }

            bool               intersectWith(const SEPlane<T> &p, T &l, SEVec3<T> &pt) const { return p.intersectWith(*this, l, pt); }


};

template <class T> class SEPlane
{
            SEVec3<T>          p_,
                               n_;

  public:
    const   SEVec3<T>         &p,
                              &n;

                               SEPlane()                                          : p(p_), n(n_) { setPoint(0,0,0); setNormal(1,0,0); }
                               SEPlane(const SEVec3<T> &nor)                      : p(p_), n(n_) { setPoint(0,0,0); setNormal(nor); }
                               SEPlane(const SEVec3<T> &pt, const SEVec3<T> &nor) : p(p_), n(n_) { setPoint(pt); setNormal(nor); }
                               SEPlane(const SEPlane<T> &p)                       : p(p_), n(n_) { setPoint(p.p); setNormal(p.n); }
                               SEPlane(T x, T y, T z, T r, T s, T t)              : p(p_), n(n_) { setPoint(x,y,z); setNormal(r,s,t); }

                              ~SEPlane() {}

            SEPlane<T>        &setPoint(T x, T y, T z)         { p_.x=x; p_.y=y; p_.z=z; return(this); }
            SEPlane<T>        &setPoint(const SEVec3<T> &pt)   { return setPoint(pt.x, pt.y, pt.z); }
            SEPlane<T>        &setPoint(const SEVec4<T> &pt)   { return setPoint(pt.x, pt.y, pt.z); }

            SEPlane<T>        &setNormal(T x, T y, T z)        { n_.x=x; n_.y=y; n_.z=z; n_.normalize(); return(this); }
            SEPlane<T>        &setNormal(const SEVec3<T> &nor) { return setNormal(nor.x, nor.y, nor.z); }
            SEPlane<T>        &setNormal(const SEVec4<T> &nor) { return setNormal(nor.x, nor.y, nor.z); }

            // Calcula intersecção com o raio r, retorna (lambda) e normal (nor) no ponto de colisão
            bool               intersectWith(const SERay<T> &r, T &lambda, SEVec3<T> &nor) const { T dp = r.d.dot(n_);       if (SEMathUtil<T>::ISZERO(dp)) return false;
                                                                                                   T l2 = n_.dot(p_-r.o)/dp; if (SEMathUtil<T>::ISZERO(l2+ABS(l2))) return false;

                                                                                                   nor=n; lambda=l2; return true; }

};

template <class T> class SEChronometer
{
  public:
    typedef enum               { CS_STOPPED, CS_PAUSED, CS_RUNNING, NUM_CSS }   tChronometerState;

                               SEChronometer() : t0_(0), t_(0), s_(CS_STOPPED) {}
                               ~SEChronometer() {}

            void               start()     { switch (s_) { case CS_STOPPED: t_=0;
                                                           case CS_PAUSED:  t0_=clock();
                                                                            s_=CS_RUNNING;
                                                           default:         break; } }

            void               pause()     { switch (s_) { case CS_RUNNING: t_+=(clock()-t0_);
                                                                            s_=CS_PAUSED;
                                                           default:         break; } }

            void               stop()      { switch (s_) { case CS_RUNNING: t_+=(clock()-t0_);
                                                           case CS_PAUSED:  s_=CS_STOPPED;
                                                           default:         break; } }

            void               reset()     { t0_=t_=0; s_=CS_STOPPED; }

            T                  read()      { return (T)(t_/(CLOCKS_PER_SEC*0.001)); }

  private:
            clock_t            t0_, t_;
            tChronometerState  s_;

};

template <class T> class SETimer
{
  public:
                               SETimer()    : last_(0) {}
                               SETimer(T i) : last_(i) {}
                              ~SETimer() {}

            T                  get()         { last_=(T)clock(); return(last_); }
            T                  getLast()     { return(last_); }
            T                  getInterval() { return((T)clock()-last_); }

            void               reset()       { last_=(T)clock(); }
  private:
            T                  last_;
};

template <class T> class SERandomNumberGenerator
{
  private:
    T         r_min_,
              r_max_,
              range_;

  public:
    SERandomNumberGenerator()                 : r_min_(0), r_max_(1), range_(r_max_-r_min_) { srand(time(NULL)); }
    SERandomNumberGenerator(T l, T r)         : r_min_(l), r_max_(r), range_(r_max_-r_min_) { srand(time(NULL)); }
    SERandomNumberGenerator(T l, T r, T seed) : r_min_(l), r_max_(r), range_(r_max_-r_min_) { srand(seed); }

    ~SERandomNumberGenerator() {}

    T         next()         const { return r_min_ + ((T)rand()/(T)RAND_MAX) * range_; }
    T         next(T l, T r) const { return l + ((T)rand()/(T)RAND_MAX) * (r-l); }

    void      resetSeed()    const { srand(1); } // reinicia o mesmo seed informado no construtor

};


/* Classe dependente de compilador setado para padrão C++11
template <class T> class SERandomNumberGenerator
{
  private:
    typedef    minstd_rand                             engine;
    typedef    uniform_real_distribution<T>            distribution;
    typedef    variate_generator<engine, distribution> generator;

    generator* _g;

    void       init(T l, T r, T seed) { _g = new generator( engine(seed), distribution(l, r) ); }

  public:
    SERandomNumberGenerator()                 { init(-SEMathUtil<T>::BIG, SEMathUtil<T>::BIG, std::chrono::system_time::now().time_since_epoch().count()); }
    SERandomNumberGenerator(T l, T r)         { init(l,r,std::chrono::system_time::now().time_since_epoch().count()); }
    SERandomNumberGenerator(T l, T r, T seed) { init(l,r,seed); }

    ~SERandomNumberGenerator() { delete _g; }

    T next() { return (*_g)(); }
};
*/
#endif
