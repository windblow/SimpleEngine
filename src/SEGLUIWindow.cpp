#include "../inc/SEGLUIWindow.h"

#include <iostream>

SEGLUIWindow::SEGLUIWindow(int w, int h, std::string t, int px, int py)
  : SEWindow(w, h, t, px, py)
{
  glutInitWindowSize(w_, h_);
  glutInitWindowPosition(px_, py_);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE | GLUT_ALPHA | GLUT_MULTISAMPLE);

  id_ = glutCreateWindow(title_.c_str());

}

SEGLUIWindow::~SEGLUIWindow()
{
  // freeglut não destrói imediatamente a janela, então o SimpleEngine a esconde antes de enviar o comando destroy
  long tempId = glutGetWindow();
  glutSetWindow(id_);
  glutHideWindow();
  glutSetWindow(tempId);
  //
  glutDestroyWindow(id_);

}

void SEGLUIWindow::reshape(int nw, int nh)
{
  SEWindow::reshape(nw,nh);
  GLUI_Master.auto_set_viewport();
}

void SEGLUIWindow::redisplay()
{
    glutSetWindow(id_);
    glutPostRedisplay();
}
