#ifndef __SEPRIMITIVE_H__
#define __SEPRIMITIVE_H__

class SEPrimitive
{
  public:
    typedef enum { LINE_PRIM, CUBE_PRIM, SPHERE_PRIM, CONE_PRIM, TORUS_PRIM, TEAPOT_PRIM, NUM_PRIMS } tPrimitive;
    typedef enum { SOLID_ST,  WIRE_ST,   NUM_ST }                                                     tState;

    const   tPrimitive &primType;
    const   tState     &state;

            void        toggleState()      { int t = static_cast<int>(s_); ++t; t%=static_cast<int>(NUM_ST); s_=static_cast<tState>(t); }
            void        setState(tState s) { s_=s; }

  protected:
    SEPrimitive(tPrimitive t)           : t_(t), s_(SOLID_ST), primType(t_), state(s_) {}
    SEPrimitive(tPrimitive t, tState s) : t_(t), s_(s),        primType(t_), state(s_) {}
    ~SEPrimitive() {}

  private:
    tPrimitive  t_;
    tState      s_;
};

template <class T> class SESphere : public SEPrimitive
{
  public:
    const T   &radius;
    const int &slices;
    const int &stacks;

          void setSlices(int sl) { sl_=sl; }
          void setStacks(int st) { st_=st; }

  protected:
    SESphere()              : SEPrimitive(SPHERE_PRIM),    r_(1), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    SESphere(tState s)      : SEPrimitive(SPHERE_PRIM, s), r_(1), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    SESphere(T r)           : SEPrimitive(SPHERE_PRIM),    r_(r), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    SESphere(T r, tState s) : SEPrimitive(SPHERE_PRIM, s), r_(r), sl_(6), st_(4), radius(r_), slices(sl_), stacks(st_) {}
    ~SESphere() {}

  private:
          T    r_;
          int  sl_;
          int  st_;
};

template <class T> class SECube : public SEPrimitive
{
  public:
    const T    &size;

          void setSize(T s) { s_=s; }

  protected:
    SECube()                : SEPrimitive(CUBE_PRIM),     s_(1),  size(s_) {}
    SECube(tState st)       : SEPrimitive(CUBE_PRIM, st), s_(1),  size(s_) {}
    SECube(T sz)            : SEPrimitive(CUBE_PRIM),     s_(sz), size(s_) {}
    SECube(T sz, tState st) : SEPrimitive(CUBE_PRIM, st), s_(sz), size(s_) {}
    ~SECube() {}

  private:
          T   s_;
};

template <class T> class SECone : public SEPrimitive
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
    SECone()                   : SEPrimitive(CONE_PRIM),    b_(1), h_(1), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    SECone(tState s)           : SEPrimitive(CONE_PRIM, s), b_(1), h_(1), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    SECone(T b, T h)           : SEPrimitive(CONE_PRIM),    b_(b), h_(h), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    SECone(T b, T h, tState s) : SEPrimitive(CONE_PRIM, s), b_(b), h_(h), sl_(4), st_(4), base(b_), height(h_), slices(sl_), stacks(st_) {}
    ~SECone() {}

  private:
          T    b_;
          T    h_;
          int  sl_;
          int  st_;
};

template <class T> class SETorus : public SEPrimitive
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
    SETorus()                   : SEPrimitive(TORUS_PRIM),    i_(1), o_(2), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    SETorus(tState s)           : SEPrimitive(TORUS_PRIM, s), i_(1), o_(2), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    SETorus(T i, T o)           : SEPrimitive(TORUS_PRIM),    i_(i), o_(o), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    SETorus(T i, T o, tState s) : SEPrimitive(TORUS_PRIM, s), i_(i), o_(o), s_(4), r_(4), inner_radius(i_), outer_radius(o_), sides(s_), rings(r_) {}
    ~SETorus() {}

  private:
          T    i_;
          T    o_;
          int  s_;
          int  r_;
};

template <class T> class SETeapot : public SEPrimitive
{
  public:
    const T    &size;

          void setSize(T s) { s_=s; }

  protected:
    SETeapot()                : SEPrimitive(TEAPOT_PRIM),     s_(1),  size(s_) {}
    SETeapot(tState st)       : SEPrimitive(TEAPOT_PRIM, st), s_(1),  size(s_) {}
    SETeapot(T sz)            : SEPrimitive(TEAPOT_PRIM),     s_(sz), size(s_) {}
    SETeapot(T sz, tState st) : SEPrimitive(TEAPOT_PRIM, st), s_(sz), size(s_) {}
    ~SETeapot() {}

  private:
          T   s_;
};

#endif // __SEPRIMITIVE_H__
