#include "../inc/SEOpenGLRenderService.h"
#include "../inc/SEOpenGLRenderObject.h"
#include "../inc/SEOpenGLCamera.h"
#include "../inc/SEOpenGLLight.h"
#include "../inc/SEOpenGLPrimitive.h"

#include "../inc/SEMath.h"

#include <stdexcept>

#define DUMPONCE(x) if (dumpOnce) std::cout << x << std::endl

extern bool dumpOnce;

int SEOpenGLRenderService::startup()
{
    // Cria e configura a câmera padrão
    cc_ = createRO(SEROType::CAMERA_RO, SECameraType::STATIC_CAM);
    c_[cc_]->setTranslation(0,0,20);
    c_[cc_]->usePerspectiveProjection();

    // Cria e configura a luz ambiente
    int l = createRO(SEROType::LIGHT_RO, SELightTypes::AMBIENT);
    l_[l]->toggle();

    return(0);
}

int SEOpenGLRenderService::shutdown()
{
    l_.clear();
    c_.clear();

    for (tROVectorIt it=ro_.begin();it!=ro_.end();++it)
        delete(*it);

    ro_.clear();

    return(0);
}

void SEOpenGLRenderService::renderFrame() const
{
    startFrame();

    setupCamera();

    for (tROVector::const_iterator it = ro_.begin(); it != ro_.end(); ++it)
    {
        //std::cout << "Chamando render em objeto id:" << std::distance(ro_.begin(), it) << "; localizado em " << (*it)->translation << std::endl;
        (*it)->render(*this);
    }

    endFrame();

}

int SEOpenGLRenderService::createRO(SEROType::tRenderObject t, int t1, int t2, int t3)
{
    int ix=-1;

    switch (t)
    {
        case SEROType::CAMERA_RO:
            {
              SEOpenGLCamera *c;
              try {
                SECameraType::tCamera tc = static_cast<SECameraType::tCamera>(t1);
                c = new SEOpenGLCamera(tc);
              } catch (...) {
                c = new SEOpenGLCamera();
              }
              ix = ro_.size();
              ro_.push_back(c);
              c_[ix]=c;
              if (cc_ < 0) cc_ = ix;
            }
            break;
        case SEROType::PRIMITIVE_RO:
            {
                SEOpenGLRenderObject *p=NULL;
                try {
                    SEPrimitive::tPrimitive pt = static_cast<SEPrimitive::tPrimitive>(t1);

                    switch (pt)
                    {
                    case SEPrimitive::CONE_PRIM:
                        p = new SEOpenGLCone();
                        break;
                    case SEPrimitive::CUBE_PRIM:
                        p = new SEOpenGLCube();
                        break;
                    case SEPrimitive::SPHERE_PRIM:
                        p = new SEOpenGLSphere();
                        break;
                    case SEPrimitive::TORUS_PRIM:
                        p = new SEOpenGLTorus();
                        break;
                    case SEPrimitive::TEAPOT_PRIM:
                        p = new SEOpenGLTeapot();
                        break;
                    }
                    if (p!=NULL)
                    {
                        ix = ro_.size();
                        ro_.push_back(p);
                    }
                } catch (...) {
                }
            }
            break;
        case SEROType::LIGHT_RO:
            {
              SEOpenGLLight *l=NULL;
              try
              {
                  SELightTypes::tLight tli = static_cast<SELightTypes::tLight>(t1);

                  switch (tli)
                  {
                  case SELightTypes::AMBIENT:
                    l = new SEOpenGLAmbientLight();
                    break;
                  case SELightTypes::AREA:
                  case SELightTypes::DIRECTIONAL:
                  case SELightTypes::POINT:
                  case SELightTypes::SPOT:
                  default:
                    break;
                  }
                  if (l!=NULL)
                  {
                        ix = ro_.size();
                        ro_.push_back(l);
                        l_[ix]=l;
                  }
              } catch (...) {
              }

            }
            break;
        default:
            break;
    }

    return(ix);
}

void SEOpenGLRenderService::destroyRO(uint32_t i)
{

    if (c_.count(i) > 0)
    {
        c_[i]=NULL;
        if (cc_==i)
          cc_=-1;
    }

    if (l_.count(i) > 0)
      l_[i]=NULL;

    try {
      if (ro_.at(i) != NULL)
      {
        delete ro_[i];
        ro_[i]=NULL;
      }
    } catch (const std::out_of_range &oor) {
    }
}

void SEOpenGLRenderService::setCamera(uint32_t c)
{
    cc_=c;
}

void SEOpenGLRenderService::setupCamera() const
{

  if (cc_ >= 0)
  {
      tCamMap::const_iterator c = c_.find(cc_);
      (*c).second->setupFrame();
  }

}

void SEOpenGLRenderService::activateLight(uint32_t l)
{
    try {
        if (!l_[l]->isOn)
            l_[l]->toggle();
    } catch (...) {
    }
}

void SEOpenGLRenderService::deactivateLight(uint32_t l)
{
    try {
        if (l_[l]->isOn)
            l_[l]->toggle();
    } catch (...) {
    }
}

void SEOpenGLRenderService::enableLighting() const
{
    glEnable(GL_LIGHTING);
    DUMPONCE("glEnable(GL_LIGHTING)");

    for (tLightMap::const_iterator it=l_.begin();it!=l_.end();++it)
        if ((*it).second->isOn)
        {
            (*it).second->enable();
            (*it).second->configure();
        }

}

void SEOpenGLRenderService::disableLighting() const
{
    for (tLightMap::const_iterator it=l_.begin();it!=l_.end();++it)
        if ((*it).second->isOn)
        {
            (*it).second->disable();
        }

    glDisable(GL_LIGHTING);
    DUMPONCE("glDisable(GL_LIGHTING)");
}

const SERenderObject<GLfloat> * SEOpenGLRenderService::getObject(uint32_t o) const
{
  try {
      return ro_.at(o);
  } catch (const std::out_of_range &oor) {
      return NULL;
  }
}

const SECamera<GLfloat> * SEOpenGLRenderService::getCamera(uint32_t c) const
{
    try {
        tCamMap::const_iterator it = c_.find(c);
        if (it!=c_.end())
            return (*it).second;
        else
            return NULL;
    } catch (...) {
        return NULL;
    }

}

const SELight<GLfloat> * SEOpenGLRenderService::getLight(uint32_t l) const
{
    try {
        tLightMap::const_iterator it = l_.find(l);
        if (it!=l_.end())
            return (*it).second;
        else
            return NULL;
    } catch (...) {
        return NULL;
    }

}

SERenderObject<GLfloat> * SEOpenGLRenderService::getObject(uint32_t o)
{
  try {
      return ro_.at(o);
  } catch (const std::out_of_range &oor) {
      return NULL;
  }
}

SECamera<GLfloat> * SEOpenGLRenderService::getCamera(uint32_t c)
{
    try {
        tCamMapIt it = c_.find(c);
        if (it!=c_.end())
            return (*it).second;
        else
            return NULL;
    } catch (...) {
        return NULL;
    }


}

SELight<GLfloat> * SEOpenGLRenderService::getLight(uint32_t l)
{
    try {
        tLightMapIt it = l_.find(l);
        if (it!=l_.end())
            return (*it).second;
        else
            return NULL;
    } catch (...) {
        return NULL;
    }

}

void SEOpenGLRenderService::startFrame() const
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	DUMPONCE("glClearColor(0.0, 0.0, 0.0, 1.0)");
	glClearDepth(1.0);
	DUMPONCE("glClearDepth(1.0)");
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	DUMPONCE("glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT)");

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	DUMPONCE("glHint(GL_LINE_SMOOTH_HINT, GL_NICEST)");

	glDisable(GL_FOG);
	DUMPONCE("glDisable(GL_FOG)");

	glEnable(GL_CULL_FACE);
	DUMPONCE("glEnable(GL_CULL_FACE)");
	glCullFace(GL_BACK);
	DUMPONCE("glCullFace(GL_BACK)");

	glEnable(GL_DEPTH_TEST);
	DUMPONCE("glEnable(GL_DEPTH_TEST)");
    glDepthFunc(GL_LESS);
    DUMPONCE("glDepthFunc(GL_LESS)");
	glDepthMask(GL_TRUE);
	DUMPONCE("glDepthMask(GL_TRUE)");

	glShadeModel(GL_SMOOTH);
	DUMPONCE("glShadeModel(GL_SMOOTH)");
	glPolygonMode(GL_FRONT,GL_FILL);
	DUMPONCE("glPolygonMode(GL_FRONT,GL_FILL)");
	glPolygonMode(GL_BACK,GL_FILL);
	DUMPONCE("glPolygonMode(GL_BACK,GL_FILL)");

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    DUMPONCE("glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)");
	glEnable(GL_BLEND);
	DUMPONCE("glEnable(GL_BLEND)");
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	DUMPONCE("glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA)");
	glEnable(GL_ALPHA_TEST);
	DUMPONCE("glEnable(GL_ALPHA_TEST)");
	glAlphaFunc(GL_GREATER,0.5);
	DUMPONCE("glAlphaFunc(GL_GREATER,0.5)");

	glEnable(GL_LIGHTING);
    DUMPONCE("glEnable(GL_LIGHTING)");
	glShadeModel(GL_SMOOTH);
	DUMPONCE("glShadeModel(GL_SMOOTH)");

	glDisable(GL_TEXTURE_2D);
	DUMPONCE("glDisable(GL_TEXTURE_2D)");
	DUMPONCE("GL_LIGHT0="<<GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	DUMPONCE("glEnable(GL_COLOR_MATERIAL)");

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	DUMPONCE("glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT)");

}

void SEOpenGLRenderService::endFrame() const
{
    glFlush();
    DUMPONCE("glFlush()");
}
