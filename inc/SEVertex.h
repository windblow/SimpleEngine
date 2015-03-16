#ifndef __SEVERTEX_H__
#define __SEVERTEX_H__

#include "SEMath.h"

template <class T> class SEVertex
{
  public:
    T   vec[8]; // array de valores altamente comprimidos
    int l;      // luminância do vértice

    T*   &p;    // coordenada do vértice
    T*   &n;    // normal do vértice
    T    &s;    // coordenada s da textura
    T    &t;    // coordenada y da textura

    SEVertex()                     : p(vec), n(vec+3), s(vec[6]), t(vec[7]), l(0)   { zerofill(); }
    SEVertex(const SEVertex<T> &x) : p(vec), n(vec+3), s(vec[6]), t(vec[7]), l(x.l) { for (int i=0;i<8;++i) vec[i]=x.vec[i]; }
    ~SEVertex() {}

    T   &operator[](std::size_t i)       { return vec[i]; }
    T    operator[](std::size_t i) const { return vec[i]; }

  private:
    void zerofill() { for (int i=0;i<8;++i) vec[i]=(T)0; }
};

#endif // __SEVERTEX_H__
