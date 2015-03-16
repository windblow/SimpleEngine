#ifndef __SEMODEL_H__
#define __SEMODEL_H__

#include "SERenderObject.h"
#include "SEMath.h"
#include "SEMesh.h"
#include "SEMaterial.h"

template <class T> class SESkeleton;
class                    SEAnimation;


template <class T>
class SEModel : public SERenderObject<T>
{
  public:
    const   bool           &loaded;
    const   SEMesh<T>*     &mesh;
    const   SESkeleton<T>* &skel;
    const   SEMaterial*    &mat;
    const   SEAnimation*   &anim;

    ~SEModel();

    virtual void           draw() = 0;

    virtual void           loadFile(std::string filename) = 0;

    virtual void           loadMesh(SEMesh<T> *m) = 0;
    virtual void           loadSkeleton(SESkeleton<T> *s) = 0;
    virtual void           loadMaterial(SEMaterial *m) = 0;
    virtual void           loadAnimation(SEAnimation *a) = 0;

  protected:
            SEMesh<T>      *mesh_;
            SESkeleton<T>  *skel_;
            SEMaterial     *mat_;
            SEAnimation    *anim_;

            bool           loaded_;


    SEModel() :
        SERenderObject<T>(SERenderObject<T>::MODEL_RO),
        mesh_(NULL),
        skel_(NULL),
        mat_(NULL),
        anim_(NULL),
        mesh(mesh_),
        skel(skel_),
        mat(mat_),
        anim(anim_),
        loaded_(false)
    {}
};

#endif // __SEMODEL_H__
