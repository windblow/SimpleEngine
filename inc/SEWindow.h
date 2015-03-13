#ifndef __SEWINDOW_H__
#define __SEWINDOW_H__

#include <string>

class SEWindowManager;

class SEWindow
{
  protected:
    int w_;
    int h_;
    int px_;
    int py_;
    
    std::string title_;
    int id_;
    
    SEWindow(int w, int h, std::string t = "", int px=0, int py=0) : w_(w), h_(h), title_(t), px_(px), py_(py), id_(-1) {}
    ~SEWindow() {}
      
  public:
    int getWidth() const { return w_; }
    int getHeight() const { return h_; }
    int getPosX() const { return px_; }
    int getPosY() const { return py_; }
    
    int getId() const { return id_; }
    std::string getTitles() const { return title_; }
    const char *getTitlec() const { return title_.c_str(); }
    
    virtual void reshape(int nw, int nh) { w_=nw; h_=nh; }
    virtual void redisplay() {}
    
    virtual void deactivate() {}
    virtual bool activate() { return true; }
      
};

class SENullWindow : public SEWindow
{
    friend class SENullWindowManager;
    
  protected:
    SENullWindow(int w, int h, std::string t = "", int px=0, int py=0) : SEWindow(w, h, t, px, py) { id_=0; }
    ~SENullWindow() {}
  
  public:
    virtual void deactivate() {}
    virtual bool activate() { return true; }
};

#endif
