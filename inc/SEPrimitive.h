#ifndef __SEPRIMITIVE_H__
#define __SEPRIMITIVE_H__

struct SEPrimTypes
{
    typedef enum { LINE_PRIM, CUBE_PRIM, SPHERE_PRIM, CONE_PRIM, TORUS_PRIM, TEAPOT_PRIM, NUM_PRIMS } tPrimitive;
    typedef enum { SOLID_ST,  WIRE_ST,   NUM_ST }                                                     tState;
};

template <class T> class SEPrimitive
{
  public:
    const SEPrimTypes::tPrimitive &primType;
    const SEPrimTypes::tState     &state;
    const SEVec3<T>               &color;

          void toggleState()                   { int t = static_cast<int>(s_); ++t; t%=static_cast<int>(SEPrimTypes::NUM_ST); s_=static_cast<SEPrimTypes::tState>(t); }
          void setState(SEPrimTypes::tState s) { s_=s; }
          void setColor(const SEVec3<T> &c)    { c_=c; clampColor(); }
          void setColor(T r, T g, T b)         { c_.vec(r,g,b); clampColor(); }
          void setColori(int r, int g, int b)  { c_.vec((T)CLAMP(r,0,255)/255.0, (T)CLAMP(g,0,255)/255.0, (T)CLAMP(b,0,255)/255.0); }

  protected:
    SEPrimitive(SEPrimTypes::tPrimitive t)                        : primType(t_), state(s_), color(c_), t_(t), c_(1,1,1), s_(SEPrimTypes::SOLID_ST) {}
    SEPrimitive(SEPrimTypes::tPrimitive t, SEPrimTypes::tState s) : primType(t_), state(s_), color(c_), t_(t), c_(1,1,1), s_(s)                     {}
    virtual ~SEPrimitive() {}

  private:
    SEPrimTypes::tPrimitive  t_;
    SEPrimTypes::tState      s_;
    SEVec3<T>                c_;

    void  clampColor() { c_.vec(CLAMP(c_.x,0,1), CLAMP(c_.y,0,1), CLAMP(c_.z,0,1)); }
};

template <class T> class SESphere : public virtual SEPrimitive<T>, public virtual SERenderObject<T>
{
  public:
    const T   &radius;
    const int &slices;
    const int &stacks;


          void setSlices(int sl)              { sl_=sl; }
          void setStacks(int st)              { st_=st; }
          void setRadius(T r)                 { r_=r; }
          void setSize(T s)                   { setRadius(s/2); }


  protected:
    SESphere()                           : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::SPHERE_PRIM),    r_(1), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    SESphere(SEPrimTypes::tState s)      : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::SPHERE_PRIM, s), r_(1), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    SESphere(T r)                        : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::SPHERE_PRIM),    r_(r), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    SESphere(T r, SEPrimTypes::tState s) : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::SPHERE_PRIM, s), r_(r), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    virtual ~SESphere() {}

  private:
          T    r_;
          int  sl_;
          int  st_;
};

template <class T> class SECube : public virtual SEPrimitive<T>, public virtual SERenderObject<T>
{
  public:
    const T  &size;

          void setSize(T s) { s_=s; }

  protected:
    SECube()                             : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CUBE_PRIM),     s_(1),  size(s_) {}
    SECube(SEPrimTypes::tState st)       : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CUBE_PRIM, st), s_(1),  size(s_) {}
    SECube(T sz)                         : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CUBE_PRIM),     s_(sz), size(s_) {}
    SECube(T sz, SEPrimTypes::tState st) : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CUBE_PRIM, st), s_(sz), size(s_) {}
    virtual ~SECube() {}

  private:
          T   s_;
};

template <class T> class SECone : public virtual SEPrimitive<T>, public virtual SERenderObject<T>
{
  public:
    const T   &base;
    const T   &height;
    const int &slices;
    const int &stacks;

          void setSlices(int sl) { sl_=sl; }
          void setStacks(int st) { st_=st; }
          void setBase(T b)      { b_=b; }
          void setHeight(T h)    { h_=h; }

  protected:
    SECone()                                : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CONE_PRIM),    b_(1), h_(1), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    SECone(SEPrimTypes::tState s)           : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CONE_PRIM, s), b_(1), h_(1), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    SECone(T b, T h)                        : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CONE_PRIM),    b_(b), h_(h), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    SECone(T b, T h, SEPrimTypes::tState s) : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::CONE_PRIM, s), b_(b), h_(h), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    virtual ~SECone() {}

  private:
          T    b_;
          T    h_;
          int  sl_;
          int  st_;
};

template <class T> class SETorus : public virtual SEPrimitive<T>, public virtual SERenderObject<T>
{
  public:
    const T   &inner_radius;
    const T   &outer_radius;
    const int &sides;
    const int &rings;

          void setInnerR(T i)  { i_=i; }
          void setOuterR(T o)  { o_=o; }
          void setSides(int s) { s_=s; }
          void setRings(int r) { r_=r; }

  protected:
    SETorus()                                : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TORUS_PRIM),    i_(1), o_(2), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    SETorus(SEPrimTypes::tState s)           : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TORUS_PRIM, s), i_(1), o_(2), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    SETorus(T i, T o)                        : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TORUS_PRIM),    i_(i), o_(o), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    SETorus(T i, T o, SEPrimTypes::tState s) : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TORUS_PRIM, s), i_(i), o_(o), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    virtual ~SETorus() {}

  private:
          T    i_;
          T    o_;
          int  s_;
          int  r_;
};

template <class T> class SETeapot : public virtual SEPrimitive<T>, public virtual SERenderObject<T>
{
  public:
    const T         &size;

          void      setSize(T s) { s_=s; }

  protected:
    SETeapot()                             : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TEAPOT_PRIM),     s_(1),  size(s_) {}
    SETeapot(SEPrimTypes::tState st)       : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TEAPOT_PRIM, st), s_(1),  size(s_) {}
    SETeapot(T sz)                         : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TEAPOT_PRIM),     s_(sz), size(s_) {}
    SETeapot(T sz, SEPrimTypes::tState st) : SERenderObject<T>(SEROType::PRIMITIVE_RO), SEPrimitive<T>(SEPrimTypes::TEAPOT_PRIM, st), s_(sz), size(s_) {}
    virtual ~SETeapot() {}

  private:
          T         s_;
 };

#endif // __SEPRIMITIVE_H__
