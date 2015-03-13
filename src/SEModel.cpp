#include "../inc/../inc/SEModel.h"

template <class T> SEModel<T>::~SEModel()
{
    if (mesh_!=NULL) delete mesh_;
    if (skel_!=NULL) delete skel_;
    if (mat_ !=NULL) delete mat_;
    if (anim_!=NULL) delete anim_;
}
