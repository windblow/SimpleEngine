#include "../inc/SEGLUTFlowController.h"
#include "../inc/SimpleEngine.h"
#include "../inc/SEDebugTools.h"

#include <iostream>

USEDUMPFLAG;

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

    while (SimpleEngine::app()->isRunning)
    {
        glutMainLoopEvent();
        glutSwapBuffers();
        DUMPFLAG(false);
    }
}
