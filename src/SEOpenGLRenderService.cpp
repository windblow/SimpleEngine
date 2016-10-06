#include "../inc/SEOpenGLRenderService.h"
#include "../inc/SEOpenGLRenderObject.h"
#include "../inc/SEOpenGLCamera.h"
#include "../inc/SEOpenGLLight.h"
#include "../inc/SEOpenGLPrimitive.h"
#include "../inc/SEDebugTools.h"

#include "../inc/SEMath.h"

#include <stdexcept>

USEDUMPFLAG;

int SEOpenGLRenderService::startup()
{
    DUMPFLAG(true);
    DUMPONCE("==========BEGIN_STARTUP_DUMP==========");

    // Configurações perenes da máquina de estado do OpenGL
    configureOpenGL();

    // Cria e configura a câmera padrão
    int c = createRO(SEROType::CAMERA_RO, SECameraType::STATIC_CAM);
    c_[c]->setTranslation(0,0,20);
    c_[c]->usePerspectiveProjection();

    DUMPONCE("===========END_STARTUP_DUMP==========="<<std::endl<<std::endl);
    //DUMPFLAG(false);

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

    configureLighting();

    configureTexturing();

    for (tROVector::const_iterator it = ro_.begin(); it != ro_.end(); ++it)
    {
        if ((*it)!=NULL) (*it)->render(*this);
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
              if (currentCamera < 0) setCamera(ix);
            }
            break;
        case SEROType::PRIMITIVE_RO:
            {
                SEOpenGLRenderObject *p=NULL;
                try {
                    SEPrimTypes::tPrimitive pt = static_cast<SEPrimTypes::tPrimitive>(t1);

                    switch (pt)
                    {
                    case SEPrimTypes::CONE_PRIM:
                        p = new SEOpenGLCone();
                        break;
                    case SEPrimTypes::CUBE_PRIM:
                        p = new SEOpenGLCube();
                        break;
                    case SEPrimTypes::SPHERE_PRIM:
                        p = new SEOpenGLSphere();
                        break;
                    case SEPrimTypes::TORUS_PRIM:
                        p = new SEOpenGLTorus();
                        break;
                    case SEPrimTypes::TEAPOT_PRIM:
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
                      break;
                  case SELightTypes::DIRECTIONAL:
                      l = new SEOpenGLDirectionalLight();
                      break;
                  case SELightTypes::POINT:
                      l = new SEOpenGLPointLight();
                      break;
                  case SELightTypes::SPOT:
                      l = new SEOpenGLSpotLight();
                      break;
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
        if (currentCamera==i)
          setCamera(-1);
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

void SEOpenGLRenderService::setGlobalAmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
    DUMPONCE("===SEOpenGLRenderService::setGlobalAmbientLight("<<r<<","<<g<<","<<b<<","<<a<<")===");
    SEVec4<GLfloat> c(CLAMP(r,0,1), CLAMP(g,0,1), CLAMP(b,0,1), CLAMP(a,0,1));
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, c.v);
    DUMPONCE("glLightModelfv(GL_LIGHT_MODEL_AMBIENT, "<<c<<")");
}

void SEOpenGLRenderService::setGlobalAmbientLighti(int r, int g, int b, int a) const
{
    DUMPONCE("===SEOpenGLRenderService::setGlobalAmbientLighti("<<r<<","<<g<<","<<b<<","<<a<<")===");
    SEVec4<GLfloat> c(CLAMP(r,0,255), CLAMP(g,0,255), CLAMP(b,0,255), CLAMP(a,0,255));
    c/=255.0;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, c.v);
    DUMPONCE("glLightModelfv(GL_LIGHT_MODEL_AMBIENT, "<<c<<")");
}

void SEOpenGLRenderService::configureLighting() const
{
    DUMPONCE("===SEOpenGLRenderService::configureLighting()===");

    if (isLightingEnabled)
    {
        glEnable(GL_LIGHTING);
        DUMPONCE("glEnable(GL_LIGHTING)");
        glShadeModel(GL_SMOOTH);
        DUMPONCE("glShadeModel(GL_SMOOTH)");

        for (tLightMap::const_iterator it=l_.begin();it!=l_.end();++it)
            if ((*it).second->isOn)
            {
                (*it).second->enable();
                (*it).second->configure();
            }
    }
    else
    {
        for (tLightMap::const_iterator it=l_.begin();it!=l_.end();++it)
            if ((*it).second->isOn)
            {
                (*it).second->disable();
            }
            glDisable(GL_LIGHTING);
            DUMPONCE("glDisable(GL_LIGHTING)");
    }
}

void SEOpenGLRenderService::configureTexturing() const
{
    DUMPONCE("===SEOpenGLRenderService::configureTexturing()===");
    if (isTexturingEnabled)
    {
        glEnable(GL_TEXTURE_2D);
        DUMPONCE("glEnable(GL_TEXTURE_2D)");
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
        DUMPONCE("glDisable(GL_TEXTURE_2D)");
    }
}

bool SEOpenGLRenderService::objectExists(uint32_t o) const
{
    if (o < ro_.size())
        return false;

    if (ro_[o]!=NULL)
        return true;

    return false;
}

bool SEOpenGLRenderService::cameraExists(uint32_t c) const
{
    if (c_.find(c)!=c_.end())
        return true;

    return false;
}

bool SEOpenGLRenderService::lightExists(uint32_t l)  const
{
    if (l_.find(l)!=l_.end())
        return true;

    return false;
}

void SEOpenGLRenderService::startFrame() const
{
    DUMPONCE("==============BEGIN_FRAME_DUMP==============");
    DUMPONCE("===SEOpenGLRenderService::startFrame()===");

	glEnable(GL_DEPTH_TEST);
	DUMPONCE("glEnable(GL_DEPTH_TEST)");

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	DUMPONCE("glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT)");
}

void SEOpenGLRenderService::endFrame() const
{
    DUMPONCE("===SEOpenGLRenderService::endFrame()===");

    glFlush();
    DUMPONCE("glFlush()");

    DUMPONCE("===============END_FRAME_DUMP==============="<<std::endl<<std::endl);
    DUMPFLAG(false);
}

void SEOpenGLRenderService::configureOpenGL() const
{
    DUMPONCE("===SEOpenGLRenderService::configureOpengl()===");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	DUMPONCE("glClearColor(0.0, 0.0, 0.0, 0.0)");
	glClearDepth(1.0);
	DUMPONCE("glClearDepth(1.0)");

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

	glPolygonMode(GL_FRONT,GL_FILL);
	DUMPONCE("glPolygonMode(GL_FRONT,GL_FILL)");
	glPolygonMode(GL_BACK,GL_FILL);
	DUMPONCE("glPolygonMode(GL_BACK,GL_FILL)");

	setupTexturing();

	setupLighting();
}

void SEOpenGLRenderService::setupCamera() const
{

  tCamMap::const_iterator it = c_.find(currentCamera);

  if (it != c_.end())
    (*it).second->setupFrame();

}

void SEOpenGLRenderService::setupLighting() const
{
    DUMPONCE("===SEOpenGLRenderService::setupLighting()===");
    glShadeModel(GL_SMOOTH);
	DUMPONCE("glShadeModel(GL_SMOOTH)");
	// Desabilita luz ambiente global por padrão
	const GLfloat al[] = {0.0, 0.0, 0.0, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, al);
    DUMPONCE("glLightModelfv(GL_LIGHT_MODEL_AMBIENT,{0.0, 0.0, 0.0, 1.0})");

}

void SEOpenGLRenderService::setupTexturing() const
{
    DUMPONCE("===SEOpenGLRenderService::setupTexturing()===");
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
}

