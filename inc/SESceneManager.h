#ifndef __SESCENEMANAGER_H__
#define __SESCENEMANAGER_H__

#include "SEScene.h"

#include <string>
#include <map>

class SESceneManager {

  private:
    typedef std::map<std::string, SEScene*>                 tSceneMap;
    typedef std::map<std::string, SEScene*>::iterator       tSceneMapIt;
    typedef std::map<std::string, SEScene*>::const_iterator tSceneMapCit;

    tSceneMap          s_;
    SEScene           *cs_;

  public:
    SESceneManager() : cs_(NULL) {}
    ~SESceneManager() { s_.clear(); }
    
    bool sceneLoaded(const std::string &n) { tSceneMapCit it=s_.find(n); if (it==s_.end()) return false; else return true; }

    void loadScene(const std::string &n, SEScene *s, bool initialize = false) { if (!sceneLoaded(n)) { s_[n] = s; if (initialize) s_[n]->init(); } }
    void initScene(const std::string &n) { if (sceneLoaded(n)) s_[n]->init(); }
    void unloadScene(const std::string &n) { if (sceneLoaded(n)) { if (cs_==s_[n]) cs_=NULL; s_.erase(n); } }
    
    void setCurrentScene(const std::string &n) { if (sceneLoaded(n)) cs_=s_[n]; }
    
    std::string currentScene() const { if (cs_==NULL) return (0); for (tSceneMapCit it=s_.begin();it!=s_.end();++it) if ((*it).second==cs_) return((*it).first); return(0); }
};

#endif
