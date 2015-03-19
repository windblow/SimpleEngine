#include "../inc/SEOpenGLRenderService.h"
#include "../inc/SEOpenGLRenderObject.h"
#include "../inc/SEOpenGLCamera.h"
#include "../inc/SEOpenGLLight.h"
#include "../inc/SEOpenGLPrimitive.h"

#include "../inc/SEMath.h"

#include <stdexcept>

int SEOpenGLRenderService::startup()
{
    // Cria a câmera padrão
    cc_ = createRO(SEROType::CAMERA_RO);

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

void SEOpenGLRenderService::renderFrame()
{
    startFrame();

    setupCamera();

    for (tROVectorIt it = ro_.begin(); it != ro_.end(); ++it)
    {
        (*it)->render();
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
        default:
            break;
    }

    return(ix);
}

void SEOpenGLRenderService::destroyRO(uint32_t i)
{
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

void SEOpenGLRenderService::setupCamera()
{

  if (cc_ >= 0)
  {
      c_[cc_]->setupFrame();
  }

}

void SEOpenGLRenderService::activateLight(uint32_t l)
{

}

void SEOpenGLRenderService::deactivateLight(uint32_t l)
{

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
        return c_.at(c);
    } catch (const std::out_of_range &oor) {
        return NULL;
    }

}

SELight<GLfloat> * SEOpenGLRenderService::getLight(uint32_t l)
{
    try {
        return l_.at(l);
    } catch (const std::out_of_range &oor) {
        return NULL;
    }

}

void SEOpenGLRenderService::startFrame()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0);

	glLineWidth(1);
	glPointSize(1);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDisable(GL_FOG);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glDisable(GL_TEXTURE_2D);
}

void SEOpenGLRenderService::endFrame()
{
    glFlush();
}
