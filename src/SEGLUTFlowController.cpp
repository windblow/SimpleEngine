#include "../inc/SEGLUTFlowController.h"
#include "../inc/SimpleEngine.h"

#include <iostream>

#define DUMPONCE(x) if (dumpOnce) std::cout << x << std::endl

bool dumpOnce;

SEGLUTFlowController::SEGLUTFlowController()
 : SEFlowController(SEFlowController::GLUT_FC)
{
    //bindCallbacks(); // postergado para após a criação da janela
}

void SEGLUTFlowController::bindCallbacks()
{
    //Associa os callbacks do GLUT aos do engine
    glutReshapeFunc(SimpleEngine::reshape);
    glutDisplayFunc(SimpleEngine::display);
    glutIdleFunc(SimpleEngine::idle);
    glutKeyboardFunc(SimpleEngine::key);
   	glutSpecialFunc(SimpleEngine::pressFuncKey);
	glutSpecialUpFunc(SimpleEngine::releaseFuncKey);

}

void SEGLUTFlowController::mainLoop()
{
    dumpOnce = true;
    while (SimpleEngine::app()->isRunning)
    {
        glutMainLoopEvent();
        glutSwapBuffers();
        dumpOnce=false;
    }
}
