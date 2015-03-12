#include "../inc/SEGLUTFlowController.h"
#include "../inc/SimpleEngine.h"

SEGLUTFlowController::SEGLUTFlowController()
 : SEFlowController(SEFlowController::GLUT_FC)
{
    //Associa os callbacks do GLUT aos do engine
    glutReshapeFunc(SimpleEngine::reshape);
    glutDisplayFunc(SimpleEngine::display);
    glutIdleFunc(SimpleEngine::idle);
    glutKeyboardFunc(SimpleEngine::key);
   	glutSpecialFunc(SimpleEngine::pressFuncKey);
	glutSpecialUpFunc(SimpleEngine::releaseFuncKey);

}
