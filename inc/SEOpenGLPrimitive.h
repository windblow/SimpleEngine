#ifndef __SEOPENGLPRIMITIVE_H__
#define __SEOPENGLPRIMITIVE_H__

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "SEOpenGLRenderObject.h"
#include "SEPrimitive.h"
#include "SEDebugTools.h"

#include <iostream>

USEDUMPFLAG;

class SEOpenGLPrimitive : public virtual SEPrimitive<GLfloat>, public virtual SEOpenGLRenderObject
{
  public:
    virtual void applyMaterial(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLPrimitive::applyMaterial()==="); glEnable(GL_COLOR_MATERIAL); DUMPONCE("glEnable(GL_COLOR_MATERIAL)"); glColorMaterial(GL_FRONT,GL_DIFFUSE); DUMPONCE("glColorMaterial(GL_FRONT,GL_DIFFUSE)"); glColor3f(color.x,color.y,color.z); DUMPONCE("glColor3f("<<color<<")"); }
    virtual void clearMaterial(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLPrimitive::clearMaterial()===");glDisable(GL_COLOR_MATERIAL); DUMPONCE("glDisable(GL_COLOR_MATERIAL)"); }

  protected:
    SEOpenGLPrimitive(SEPrimTypes::tPrimitive t)                        : SEPrimitive<GLfloat>(t),    SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO) {}
    SEOpenGLPrimitive(SEPrimTypes::tPrimitive t, SEPrimTypes::tState s) : SEPrimitive<GLfloat>(t, s), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO) {}
    virtual ~SEOpenGLPrimitive() {}
};

class SEOpenGLSphere : public SESphere<GLfloat>, public SEOpenGLPrimitive
{
  public:
    SEOpenGLSphere()                                 : SESphere<GLfloat>(),     SEPrimitive<GLfloat>(SEPrimTypes::SPHERE_PRIM),    SEOpenGLPrimitive(SEPrimTypes::SPHERE_PRIM),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLSphere(SEPrimTypes::tState s)            : SESphere<GLfloat>(s),    SEPrimitive<GLfloat>(SEPrimTypes::SPHERE_PRIM, s), SEOpenGLPrimitive(SEPrimTypes::SPHERE_PRIM, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLSphere(GLfloat r)                        : SESphere<GLfloat>(r),    SEPrimitive<GLfloat>(SEPrimTypes::SPHERE_PRIM),    SEOpenGLPrimitive(SEPrimTypes::SPHERE_PRIM),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLSphere(GLfloat r, SEPrimTypes::tState s) : SESphere<GLfloat>(r, s), SEPrimitive<GLfloat>(SEPrimTypes::SPHERE_PRIM, s), SEOpenGLPrimitive(SEPrimTypes::SPHERE_PRIM, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    virtual ~SEOpenGLSphere() {}

    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLSphere::draw()==="); if (state==SEPrimTypes::SOLID_ST) { glutSolidSphere(radius, slices, stacks); DUMPONCE("glutSolidSphere("<<radius<<", "<<slices<<", "<<stacks<<")"); } else { glutWireSphere(radius, slices, stacks); DUMPONCE("glutWireSphere("<<radius<<", "<<slices<<", "<<stacks<<")"); } }
};

class SEOpenGLCube : public SECube<GLfloat>, public SEOpenGLPrimitive
{
  public:
    SEOpenGLCube()                                   : SECube<GLfloat>(),       SEPrimitive<GLfloat>(SEPrimTypes::CUBE_PRIM),     SEOpenGLPrimitive(SEPrimTypes::CUBE_PRIM),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCube(SEPrimTypes::tState st)             : SECube<GLfloat>(st),     SEPrimitive<GLfloat>(SEPrimTypes::CUBE_PRIM, st), SEOpenGLPrimitive(SEPrimTypes::CUBE_PRIM, st), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCube(GLfloat sz)                         : SECube<GLfloat>(sz),     SEPrimitive<GLfloat>(SEPrimTypes::CUBE_PRIM),     SEOpenGLPrimitive(SEPrimTypes::CUBE_PRIM),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCube(GLfloat sz, SEPrimTypes::tState st) : SECube<GLfloat>(sz, st), SEPrimitive<GLfloat>(SEPrimTypes::CUBE_PRIM, st), SEOpenGLPrimitive(SEPrimTypes::CUBE_PRIM, st), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    virtual ~SEOpenGLCube() {}

    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLCube::draw()==="); if (state==SEPrimTypes::SOLID_ST) { glutSolidCube(size); DUMPONCE("glutSolidCube("<<size<<")"); } else { glutWireCube(size); DUMPONCE("glutWireCube("<<size<<")"); } }
};

class SEOpenGLCone : public SECone<GLfloat>, public SEOpenGLPrimitive
{
  public:
    SEOpenGLCone()                                            : SECone<GLfloat>(),        SEPrimitive<GLfloat>(SEPrimTypes::CONE_PRIM),    SEOpenGLPrimitive(SEPrimTypes::CONE_PRIM),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCone(SEPrimTypes::tState s)                       : SECone<GLfloat>(s),       SEPrimitive<GLfloat>(SEPrimTypes::CONE_PRIM, s), SEOpenGLPrimitive(SEPrimTypes::CONE_PRIM, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCone(GLfloat b, GLfloat h)                        : SECone<GLfloat>(b, h),    SEPrimitive<GLfloat>(SEPrimTypes::CONE_PRIM),    SEOpenGLPrimitive(SEPrimTypes::CONE_PRIM),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCone(GLfloat b, GLfloat h, SEPrimTypes::tState s) : SECone<GLfloat>(b, h, s), SEPrimitive<GLfloat>(SEPrimTypes::CONE_PRIM, s), SEOpenGLPrimitive(SEPrimTypes::CONE_PRIM, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    virtual ~SEOpenGLCone() {}

    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLCone::draw()==="); if (state==SEPrimTypes::SOLID_ST) { glutSolidCone(base, height, slices, stacks); DUMPONCE("glutSolidCone("<<base<<", "<<height<<", "<<slices<<", "<<stacks<<")"); } else { glutWireCone(base, height, slices, stacks); DUMPONCE("glutWireCone("<<base<<", "<<height<<", "<<slices<<", "<<stacks<<")"); } }
};

class SEOpenGLTorus : public SETorus<GLfloat>, public SEOpenGLPrimitive
{
  public:
    SEOpenGLTorus()                                            : SETorus<GLfloat>(),        SEPrimitive<GLfloat>(SEPrimTypes::TORUS_PRIM),    SEOpenGLPrimitive(SEPrimTypes::TORUS_PRIM),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTorus(SEPrimTypes::tState s)                       : SETorus<GLfloat>(s),       SEPrimitive<GLfloat>(SEPrimTypes::TORUS_PRIM, s), SEOpenGLPrimitive(SEPrimTypes::TORUS_PRIM, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTorus(GLfloat i, GLfloat o)                        : SETorus<GLfloat>(i, o),    SEPrimitive<GLfloat>(SEPrimTypes::TORUS_PRIM),    SEOpenGLPrimitive(SEPrimTypes::TORUS_PRIM),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTorus(GLfloat i, GLfloat o, SEPrimTypes::tState s) : SETorus<GLfloat>(i, o, s), SEPrimitive<GLfloat>(SEPrimTypes::TORUS_PRIM, s), SEOpenGLPrimitive(SEPrimTypes::TORUS_PRIM, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    virtual ~SEOpenGLTorus() {}

    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLTorus::draw()==="); if (state==SEPrimTypes::SOLID_ST) { glutSolidTorus(inner_radius*scale, outer_radius*scale, sides, rings); DUMPONCE("glutSolidTorus("<<inner_radius*scale<<", "<<outer_radius*scale<<", "<<sides<<", "<<rings<<")"); } else { glutWireTorus(inner_radius, outer_radius, sides, rings); DUMPONCE("glutWireTorus("<<inner_radius*scale<<", "<<outer_radius*scale<<", "<<sides<<", "<<rings<<")"); } }
};

class SEOpenGLTeapot : public SETeapot<GLfloat>, public SEOpenGLPrimitive
{
  public:
    SEOpenGLTeapot()                                   : SETeapot<GLfloat>(),       SEPrimitive<GLfloat>(SEPrimTypes::TEAPOT_PRIM),     SEOpenGLPrimitive(SEPrimTypes::TEAPOT_PRIM),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTeapot(SEPrimTypes::tState st)             : SETeapot<GLfloat>(st),     SEPrimitive<GLfloat>(SEPrimTypes::TEAPOT_PRIM, st), SEOpenGLPrimitive(SEPrimTypes::TEAPOT_PRIM, st), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTeapot(GLfloat sz)                         : SETeapot<GLfloat>(sz),     SEPrimitive<GLfloat>(SEPrimTypes::TEAPOT_PRIM),     SEOpenGLPrimitive(SEPrimTypes::TEAPOT_PRIM),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTeapot(GLfloat sz, SEPrimTypes::tState st) : SETeapot<GLfloat>(sz, st), SEPrimitive<GLfloat>(SEPrimTypes::TEAPOT_PRIM, st), SEOpenGLPrimitive(SEPrimTypes::TEAPOT_PRIM, st), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    virtual ~SEOpenGLTeapot() {}

    virtual void draw(const SERenderServiceInternals<GLfloat> &rs) const { DUMPONCE("===SEOpenGLTeapot::draw()==="); if (state==SEPrimTypes::SOLID_ST) { glutSolidTeapot(size); DUMPONCE("glutSolidTeapot("<<size<<")"); } else { glutWireTeapot(size); DUMPONCE("glutWireTeapot("<<size<<")"); }  }
};

#endif // __SEOPENGLPRIMITIVE_H__
