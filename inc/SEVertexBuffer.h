#ifndef __SEVERTEXBUFFER_H__
#define __SEVERTEXBUFFER_H__

#include "SEVertex.h"

#include <vector>

template <class T> class SEVertexBuffer
{
  public:
    const uint32_t &refCount;

    SEVertexBuffer() : v_(), r_(1), refCount(r_) {}
    ~SEVertexBuffer() {}

    SEVertex<T> &operator[](std::size_t i)       { return v_[i]; }
    SEVertex<T>  operator[](std::size_t i) const { return v_[i]; }

    void     addRef() { ++r_; }
    void     subRef() { --r_; }

    void     append(SEVertex<T> v) { v_.push_back(v); }

  private:
    std::vector<SEVertex<T> > v_;
    uint32_t                  r_;
};

#endif // __SEVERTEXBUFFER_H__
