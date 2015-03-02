#ifndef __SIMPLEENGINE_H__
#define __SIMPLEENGINE_H__

#include <stdlib.h>
#include <time.h>
#include <list>

#include "SEConfigurationLoader.h"
#include "SEServiceLocator.h"
#include "SEApplication.h"


/*
 * Classe: SimpleEngine
 *
 *   Classe estática que implementa a interface principal da Simple Engine com o C++
 *
*/

class SimpleEngine
{
/**** Novo ****/
  private:
    static bool appLoaded_;

    static SEConfigurationLoader *cl_;
    static SEServiceLocator *sl_;
    
    static SEApplication *app_;
    
    static int argc_;
    static char **argv_;
        
	public:
    static void startup(int argc, char **argv);
    
    static void loadApp(SEApplication *app);
    static void unloadApp();
    
    static bool appLoaded() { return appLoaded_; }
    static bool isAppLoaded() { return appLoaded(); }
    
    static SEConfigurationLoader *cl() { return cl_; }
    static SEConfigurationLoader *configurationLoader() { return cl(); }
    static SEConfigurationLoader *getConfigurationLoader() { return cl(); }
    static SEServiceLocator *sl() { return sl_; }
    static SEServiceLocator *serviceLocator() { return sl(); }
    static SEServiceLocator *getServiceLocator() { return sl(); }

    static SEWindowManager *wm() { if (appLoaded()) return app_->wm(); return (NULL); }
    static SEWindowManager *windowManager() { return wm(); }
    static SEWindowManager *getWindowManager() { return wm(); }
    static SERenderService *rs() { if (appLoaded()) return app_->rs(); return (NULL); }
    static SERenderService *renderService() { return rs(); }
    static SERenderService *getRenderService() { return rs(); }

    static SEApplication *app() { return app_; }
    static SEApplication *application() { return app(); }
    static SEApplication *getApplication() { return app(); }

		static void init();
		static void quit();
		
		static void reset();
		
		static void runApp();
 
 		// Funções de callback
		static void reshape(int width, int height)                      { wm()->reshapeActive(width, height); app()->reshape(width, height); }
		static void display()                                           { rs()->startFrame(); app()->display(); rs()->endFrame(); }
		static void key(unsigned char key, int x, int y)                { app()->key(key, x, y); }
		static void pressFuncKey(int key, int x1, int y1)               { app()->pressFuncKey(key, x1, y1); }
		static void releaseFuncKey(int key, int x, int y)               { app()->releaseFuncKey(key, x, y); }
		static void mouseMotion(int x, int y)                           { app()->mouseMotion(x, y); }
		static void mousePassiveMotion(int x, int y)                    { app()->mousePassiveMotion(x, y); }
		static void mouseButton(int button, int state, int x, int y)    { app()->mouseButton(button, state, x, y); }
		static void idle()                                              { app()->idle(); wm()->redisplayActive(); }
		
		static void quitProgram();
		
};

#endif
