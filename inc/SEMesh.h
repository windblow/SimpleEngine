#ifndef __SEMESH_H__
#define __SEMESH_H__

#include "SEMath.h"
#include "SERenderObject.h"
#include "SEVertexBuffer.h"

#include <map>
#include <string>



template <class T> class SEMesh : public virtual SERenderObject<T>
{
  public:
    typedef typename std::map<uint32_t, SEVertexBuffer<T> >           tVertexBufferMap;
    typedef typename std::map<uint32_t, SEVertexBuffer<T> >::iterator tVertexBufferMapIt;

    const   std::string      &filename;
    const   uint32_t         &buffer;

    SEMesh()                     : n_(), b_(0), l_(false), filename(n_), buffer(b_) {}
    SEMesh(std::string filename) : n_(), b_(0), l_(false), filename(n_), buffer(b_) { loadMesh(filename); }
    ~SEMesh() { if (isLoaded()) vb_[b_].subRef(); }

            bool             isLoaded() { return l_; }

            bool             loadMesh(std::string f);
    virtual bool             loadBufferFromFile(std::string f, uint32_t i) = 0;

    static  void             clearVertexBuffers();

  protected:
            std::string      n_;
            uint32_t         b_;
            bool             l_;

    static  tVertexBufferMap vb_;
    static  tVertexBufferMap newVertexBufferMap() { tVertexBufferMap r; return r; } // inicializador estático do map

};

// movido para o arquivo header porque inicialização de membros estáticos em classes template não podem estar em arquivos compilados
template <class T> typename SEMesh<T>::tVertexBufferMap SEMesh<T>::vb_(SEMesh<T>::newVertexBufferMap());

#endif // __SEMESH_H__
