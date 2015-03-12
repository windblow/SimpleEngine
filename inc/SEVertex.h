#ifndef __SEVERTEX_H__
#define __SEVERTEX_H__

#include "SEMath.h"

template <class T> class SEVertex
{
  public:
    T   vec[9]; // array de valores altamente comprimidos
    int l;      // lumin�ncia do v�rtice

    T   &v;     // coordenada do v�rtice
    T   &n;     // normal do v�rtice
    T   &c;     // cor do v�rtice

    SEVertex()                     : v(vec), n(vec+3), c(vec+6), l(0)   { zerofill(); }
    SEVertex(const SEVertex<T> &x) : v(vec), n(vec+3), c(vec+6), l(x.l) { for (int i=0;i<9;++i) vec[i]=x.vec[i]; }
    ~SEVertex() {}

    T   &operator[](std::size_t i)       { return vec[i]; }
    T    operator[](std::size_t i) const { return vec[i]; }

  private:
    void zerofill() { for (int i=0;i<9;++i) vec[i]=(T)0; }
};

#endif // __SEVERTEX_H__
