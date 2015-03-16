#include "../inc/SEOpenGLRenderService.h"

int SEOpenGLRenderService::startup()
{
}

int SEOpenGLRenderService::shutdown()
{
}

uint32_t SEOpenGLRenderService::pushComponent(SERenderComponent *c)
{

}

void SEOpenGLRenderService::popComponent(uint32_t i)
{

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
