#include "../inc/SEMesh.h"
#include "../inc/SEObject.h"

template <class T> bool SEMesh<T>::loadMesh(std::string f)
{
    if (l_)
        return false;

    uint32_t b_ = SEObjectName::nameToCode(f);

    if (vb_.count(b_) > 0)
    {
        vb_[b_].addRef();
        l_=true;
    }
    else
    {
        l_ = this->loadBufferFromFile(f, b_);
    }

    return(l_);
}

template <class T> void SEMesh<T>::clearVertexBuffers()
{
    // Quando chamada, apaga da mem�ria os vertex buffers que n�o t�m mais refer�ncias para si (garbage collection)
    for (tVertexBufferMapIt it=vb_.begin(); it!=vb_.end(); ++it)
        if (it->second.refCount==0)
            vb_.erase(it);
}
