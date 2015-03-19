#ifndef __SEOPENGLPRIMITIVE_H__
#define __SEOPENGLPRIMITIVE_H__

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "SEOpenGLRenderObject.h"
#include "SEPrimitive.h"

class SEOpenGLSphere : public SESphere<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLSphere()                    : SESphere<GLfloat>(),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLSphere(tState s)            : SESphere<GLfloat>(s),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLSphere(GLfloat r)           : SESphere<GLfloat>(r),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLSphere(GLfloat r, tState s) : SESphere<GLfloat>(r, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    ~SEOpenGLSphere() {}

    virtual void draw() const { if (state==SOLID_ST) glutSolidSphere(radius, slices, stacks); else glutWireSphere(radius, slices, stacks);  }
};

class SEOpenGLCube : public SECube<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLCube()                      : SECube<GLfloat>(),       SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCube(tState st)             : SECube<GLfloat>(st),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCube(GLfloat sz)            : SECube<GLfloat>(sz),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCube(GLfloat sz, tState st) : SECube<GLfloat>(sz, st), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    ~SEOpenGLCube() {}

    virtual void draw() const { if (state==SOLID_ST) glutSolidCube(size); else glutWireCube(size);  }
};

class SEOpenGLCone : public SECone<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLCone()                               : SECone<GLfloat>(),        SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCone(tState s)                       : SECone<GLfloat>(s),       SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCone(GLfloat b, GLfloat h)           : SECone<GLfloat>(b, h),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLCone(GLfloat b, GLfloat h, tState s) : SECone<GLfloat>(b, h, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    ~SEOpenGLCone() {}

    virtual void draw() const { if (state==SOLID_ST) glutSolidCone(base, height, slices, stacks); else glutWireCone(base, height, slices, stacks);  }
};

class SEOpenGLTorus : public SETorus<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLTorus()                               : SETorus<GLfloat>(),        SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTorus(tState s)                       : SETorus<GLfloat>(s),       SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTorus(GLfloat i, GLfloat o)           : SETorus<GLfloat>(i, o),    SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTorus(GLfloat i, GLfloat o, tState s) : SETorus<GLfloat>(i, o, s), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    ~SEOpenGLTorus() {}

    virtual void draw() const { if (state==SOLID_ST) glutSolidTorus(inner_radius, outer_radius, sides, rings); else glutWireTorus(inner_radius, outer_radius, sides, rings);  }
};

class SEOpenGLTeapot : public SETeapot<GLfloat>, public SEOpenGLRenderObject
{
  public:
    SEOpenGLTeapot()                      : SETeapot<GLfloat>(),       SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTeapot(tState st)             : SETeapot<GLfloat>(st),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTeapot(GLfloat sz)            : SETeapot<GLfloat>(sz),     SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    SEOpenGLTeapot(GLfloat sz, tState st) : SETeapot<GLfloat>(sz, st), SEOpenGLRenderObject(SEROType::PRIMITIVE_RO), SERenderObject<GLfloat>(SEROType::PRIMITIVE_RO) {}
    ~SEOpenGLTeapot() {}

    virtual void draw() const { if (state==SOLID_ST) glutSolidTeapot(size); else glutWireTeapot(size);  }
};

#endif // __SEOPENGLPRIMITIVE_H__
