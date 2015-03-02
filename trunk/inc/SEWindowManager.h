#ifndef __SEWINDOWMANAGER_H__
#define __SEWINDOWMANAGER_H__

#include <map>
#include <string>

#include "SEWindow.h"

class SEServiceLocator;

class SEWindowManager
{
  public:
         typedef enum { GLEW_WM, GLUI_WM, GLUT_WM, NULL_WM, NUM_WMS } tWindowManager;
         typedef std::map<long, SEWindow*>                            tWindowList;
         typedef std::map<long, SEWindow*>::iterator                  tWindowList_iterator;
         typedef std::map<long, SEWindow*>::const_iterator            tWindowList_const_iterator;

  protected:
         tWindowManager type_;
         long currentId_;
          
         tWindowList w_;      
         
         SEWindowManager(tWindowManager t) : type_(t), currentId_(-1) {}
         SEWindowManager(tWindowManager t, int argc, char **argv) : type_(t), currentId_(-1) {}
         
         void adjustCurrentId() { if (w_.size()==0) currentId_=-1; else currentId_=w_.begin()->first; }

  public:         
         ~SEWindowManager() { w_.clear(); }
         
         virtual long createNewWindow(int w, int h, std::string t = "", int posx = 5, int posy = 5) = 0;
         
         virtual void reshapeActive(int w, int h) { w_[currentId_]->reshape(w,h); }
         virtual void redisplayActive() { w_[currentId_]->redisplay(); }

         virtual void registerDisplayFunction(void (*f)(void)) = 0;
         virtual void registerReshapeFunction(void (*f) (int, int)) = 0;
         virtual void registerIdleFunction(void (*f) (void)) = 0;

         tWindowManager getType() const { return type_; }
         
         long getCurrentWindowID() const { return currentId_; }
         const SEWindow *getCurrentWindow() const { if (currentId_ < 0) return 0; else { tWindowList_const_iterator it = w_.find(currentId_); return (it->second); } }
         
         bool setActive(long id) { if (w_.find(id) != w_.end()) { w_[currentId_]->deactivate(); currentId_ = id; return w_[currentId_]->activate(); } else return false; }
         bool isActive(long id) const { return (currentId_==id); }

         void destroyWindow(int id) { w_.erase(id); adjustCurrentId(); }
         void destroyWindow(tWindowList_iterator i) { w_.erase(i); adjustCurrentId(); }         
};

class SENullWindowManager : public SEWindowManager
{
  friend class SEServiceLocator;
  
  protected:
         SENullWindowManager() : SEWindowManager(NULL_WM) {}
         SENullWindowManager(int argc, char **argv)  : SEWindowManager(NULL_WM, argc, argv) {}
         ~SENullWindowManager() {}
         
  public:
         virtual long createNewWindow(int w, int h, std::string t = "", int posx = 0, int posy = 0) { SENullWindow *nw = new SENullWindow(0,0); currentId_=nw->getId(); w_[currentId_]=nw;  }
         
         virtual void reshapeActive(int w, int h) {}
         virtual void redisplayActive() {}
         
         virtual void registerDisplayFunction(void (*f)(void)) {};
         virtual void registerReshapeFunction(void (*f) (int, int)) {};
         virtual void registerIdleFunction(void (*f) (void)) {};
         
         bool setActive(long id) { return true; }
         bool isActive(long id) const { return false; }
};

#endif
