#ifndef __SEOPENGLLIGHT_H__
#define __SEOPENGLLIGHT_H__

#include <map>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "SELight.h"
#include "SEOpenGLRenderObject.h"
#include "SEDebugTools.h"

USEDUMPFLAG;

class SEOpenGLLight : public virtual SELight<GLfloat>, public virtual SEOpenGLRenderObject
{
  public:
    typedef std::map<GLenum,bool> tGlobalIx;

    const GLenum &glIndex;

    virtual void render(const SERenderServiceInternals<GLfloat> &rs) const { if (isOn) SERenderObject<GLfloat>::render(rs); }

    /* desenha um cubo wireframe para identificar a posição da luz */
    virtual void applyMaterial(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLLight::applyMaterial()==="); if (rs.isLightingEnabled) { glDisable(GL_LIGHTING); DUMPONCE("glDisable(GL_LIGHTING)"); } if (rs.isTexturingEnabled) { glDisable(GL_TEXTURE_2D); DUMPONCE("glDisable(GL_TEXTURE_2D)"); } glEnable(GL_COLOR_MATERIAL); DUMPONCE("glEnable(GL_COLOR_MATERIAL)"); glColor3f(1.0,0.0,0.0); DUMPONCE("glColor3f(1.0,0.0,0.0)"); }
    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLLight::draw()===");  glutWireCube(1.0); DUMPONCE("glWireCube(1.0)"); };
    virtual void clearMaterial(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLLight::clearMaterial()==="); if (rs.isLightingEnabled) { glEnable(GL_LIGHTING); DUMPONCE("glEnable(GL_LIGHTING)"); } glDisable(GL_COLOR_MATERIAL); DUMPONCE("glDisable(GL_COLOR_MATERIAL)"); if (rs.isTexturingEnabled) { glEnable(GL_TEXTURE_2D); DUMPONCE("glEnable(GL_TEXTURE_2D)"); } }

    virtual void configure() const =0;

    virtual void enable() const { DUMPONCE("===SEOpenGLLight::enable()==="); glEnable(glIndex_); DUMPONCE("glEnable("<<glIndex_<<")"); }
    virtual void disable() const { DUMPONCE("===SEOpenGLLight::disable()==="); glDisable(glIndex_); DUMPONCE("glDisable("<<glIndex_<<")"); }


  protected:
    SEOpenGLLight(SELightTypes::tLight t) : SELight<GLfloat>(t), SEOpenGLRenderObject(SEROType::LIGHT_RO), SERenderObject<GLfloat>(SEROType::LIGHT_RO), glIndex(glIndex_) { glIndex_=getNextIndex(); }
    virtual ~SEOpenGLLight() { disable(); globalIx[glIndex_]=false; }

    static GLenum getNextIndex() { for (GLenum e=GL_LIGHT0;e<(GL_LIGHT0+GL_MAX_LIGHTS);++e) { if (!globalIx[e]) { globalIx[e]=true; return e; } } return -1; }

  private:
    GLenum glIndex_;

    static tGlobalIx globalIx;
    static tGlobalIx initGlobalIx() { tGlobalIx t; for (int i=0;i<GL_MAX_LIGHTS;++i) { t[(GL_LIGHT0+i)]=false; } return t; }
};


class SEOpenGLAmbientLight : public SEAmbientLight<GLfloat>, public SEOpenGLLight
{
  public:
    SEOpenGLAmbientLight() :
        SEAmbientLight<GLfloat>(),
        SELight<GLfloat>(SELightTypes::AMBIENT, 0.2, 0.2, 0.2, 1.0),
        SEOpenGLLight(SELightTypes::AMBIENT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    SEOpenGLAmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
        SEAmbientLight<GLfloat>(r, g, b, a),
        SELight<GLfloat>(SELightTypes::AMBIENT, r, g, b, a),
        SEOpenGLLight(SELightTypes::AMBIENT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    virtual ~SEOpenGLAmbientLight() {}

    virtual void render(const SERenderServiceInternals<GLfloat> &rs) const {} // nada a renderizar em luz ambiente

    virtual void configure() const { DUMPONCE("===SEOpenGLAmbientLight::configure()==="); glLightfv(glIndex,GL_AMBIENT_AND_DIFFUSE,color.multColor(intensity).c); DUMPONCE("glLightfv("<<glIndex<<",GL_AMBIENT_AND_DIFFUSE, "<<color.multColor(intensity)<<")"); }

};

class SEOpenGLSpotLight : public SESpotLight<GLfloat>, public SEOpenGLLight
{
  public:
    SEOpenGLSpotLight() :
        SESpotLight<GLfloat>(),
        SELight<GLfloat>(SELightTypes::SPOT),
        SEOpenGLLight(SELightTypes::SPOT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    SEOpenGLSpotLight(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
        SESpotLight<GLfloat>(r, g, b, a),
        SELight<GLfloat>(SELightTypes::SPOT, r, g, b, a),
        SEOpenGLLight(SELightTypes::SPOT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    SEOpenGLSpotLight(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat c) :
        SESpotLight<GLfloat>(r, g, b, a, c),
        SELight<GLfloat>(SELightTypes::SPOT, r, g, b, a),
        SEOpenGLLight(SELightTypes::SPOT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    virtual ~SEOpenGLSpotLight() {}

    virtual void configure() const { DUMPONCE("===SEOpenGLSpotLight::configure()===");
                                     glLightfv(glIndex,GL_DIFFUSE,color.multColor(intensity).c);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_DIFFUSE,"<<color.multColor(intensity)<<")");
                                     glLightfv(glIndex,GL_POSITION,translation.v);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_POSITION,"<<translation<<")");
                                     glLightfv(glIndex,GL_SPOT_DIRECTION,(direction*rotation).v);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_SPOT_DIRECTION,"<<(direction*rotation)<<")");
                                     glLightf(glIndex,GL_SPOT_CUTOFF,cutoff);
                                     DUMPONCE("glLightf("<<glIndex<<",GL_SPOT_CUTOFF,"<<cutoff<<")"); }
                                     //clearTransformation(); }
};

class SEOpenGLPointLight : public SEPointLight<GLfloat>, public SEOpenGLLight
{
  public:
    SEOpenGLPointLight() :
        SEPointLight<GLfloat>(),
        SELight<GLfloat>(SELightTypes::POINT),
        SEOpenGLLight(SELightTypes::POINT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    SEOpenGLPointLight(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
        SEPointLight<GLfloat>(r, g, b, a),
        SELight<GLfloat>(SELightTypes::POINT, r, g, b, a),
        SEOpenGLLight(SELightTypes::POINT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    virtual ~SEOpenGLPointLight() {}

    virtual void configure() const { DUMPONCE("===SEOpenGLPointLight::configure()===");
                                     glLightfv(glIndex,GL_DIFFUSE,color.multColor(intensity).c);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_DIFFUSE,"<<color.multColor(intensity)<<")");
                                     glLightfv(glIndex,GL_POSITION,translation.v);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_POSITION,"<<translation<<")"); }
};

class SEOpenGLDirectionalLight : public SEDirectionalLight<GLfloat>, public SEOpenGLLight
{
  public:
    SEOpenGLDirectionalLight() :
        SEDirectionalLight<GLfloat>(),
        SELight<GLfloat>(SELightTypes::DIRECTIONAL),
        SEOpenGLLight(SELightTypes::DIRECTIONAL),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    SEOpenGLDirectionalLight(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
        SEDirectionalLight<GLfloat>(r, g, b, a),
        SELight<GLfloat>(SELightTypes::DIRECTIONAL, r, g, b, a),
        SEOpenGLLight(SELightTypes::DIRECTIONAL),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    {}
    virtual ~SEOpenGLDirectionalLight() {}

    virtual void render(const SERenderServiceInternals<GLfloat> &rs) const {} // nada a renderizar em luz direcional

    virtual void configure() const { DUMPONCE("===SEOpenGLDirectionalLight::configure()===");
                                     glLightfv(glIndex,GL_AMBIENT_AND_DIFFUSE,color.multColor(intensity).c);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_AMBIENT_AND_DIFFUSE,"<<color.multColor(intensity)<<")");
                                     glLightfv(glIndex,GL_POSITION,(-direction).v);
                                     DUMPONCE("glLightfv("<<glIndex<<",GL_POSITION,"<<(-direction)<<")"); }
};

#endif // __SEOPENGLLIGHT_H__
