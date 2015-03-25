#ifndef __SEOPENGLLIGHT_H__
#define __SEOPENGLLIGHT_H__

#include <map>

#include <GL/gl.h>

#include "SELight.h"
#include "SEOpenGLRenderObject.h"

#define DUMPONCE(x) if (dumpOnce) std::cout << x << std::endl

extern bool dumpOnce;

class SEOpenGLLight : public virtual SELight<GLfloat>, public virtual SEOpenGLRenderObject
{
  public:
    typedef std::map<GLenum,bool> tGlobalIx;

    const GLenum &glIndex;

    virtual void draw() const {};
    virtual void configure() const =0;

    virtual void enable() const { glEnable(glIndex_); DUMPONCE("glEnable("<<glIndex_<<")"); }
    virtual void disable() const { glDisable(glIndex_); DUMPONCE("glDisable("<<glIndex_<<")"); }


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
        SELight<GLfloat>(SELightTypes::AMBIENT),
        SEOpenGLLight(SELightTypes::AMBIENT),
        SEOpenGLRenderObject(SEROType::LIGHT_RO),
        SERenderObject<GLfloat>(SEROType::LIGHT_RO)
    { setColor(1,1,1); setIntensity(0.5); }
    virtual ~SEOpenGLAmbientLight() {}

    virtual void configure() const { GLfloat c[4]={r*intensity,g*intensity,b*intensity,1.0}; glLightfv(glIndex,GL_AMBIENT_AND_DIFFUSE,c); DUMPONCE("glLightfv("<<glIndex<<",GL_AMBIENT_AND_DIFFUSE, {"<<*c<<","<<c[1]<<","<<c[2]<<","<<c[3]<<"} )"); }

};

#endif // __SEOPENGLLIGHT_H__
