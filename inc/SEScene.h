#ifndef __SESCENE_H__
#define __SESCENE_H__

#include "SESceneGraph.h"

class SEScene
{
  protected:
    bool          initialized_;

    SESceneGraph sg_[3],
                 &preSG_,
                 &mainSG_,
                 &postSG_;

    SEScene() : initialized_(false), preSG_(sg_[0]), mainSG_(sg_[1]), postSG_(sg_[2]) {}
    virtual ~SEScene() { if (initialized_) this->finish(); }

  public:
    virtual void init()=0;
    virtual void reset()=0;
    virtual void finish()=0;

    virtual void update(double dt)=0;

    bool isInitialized() const { return initialized_; }
};

#endif
