#include <se.h>

class SETestApp1 : public SEApplication<GLfloat>
{
  private:
    int obj_;
    SETimer<GLfloat> t_;

  public:
    SETestApp1() :
      SEApplication<GLfloat>("SETestApp1"),
      obj_(0),
      t_()
    {
      // Construtor
    }

    virtual ~SETestApp1()
    {
      // Destrutor
    }

    virtual void init(int argc, char **argv)
    {
      SEApplication<GLfloat>::init(argc, argv);

      obj_ = rs_->createRO(SEROType::LIGHT_RO, SELightTypes::DIRECTIONAL);
      SEDirectionalLight<GLfloat>* l = dynamic_cast<SEDirectionalLight<GLfloat>*>(rs_->getLight(obj_));
      l->setDirection(1,-1,-1);
      l->toggle();

      obj_ = rs_->createRO(SEROType::PRIMITIVE_RO, SEPrimTypes::TEAPOT_PRIM);
      SETeapot<GLfloat>* t = dynamic_cast<SETeapot<GLfloat>*>(rs_->getObject(obj_));
      t->setSize(5.0);

      t_.setSpeedFactor(0.1);
    }

    virtual void run()
    {
      t_.reset();

      SEApplication<GLfloat>::run();
    }

    virtual void quit()
    {
      SEApplication<GLfloat>::quit();
    }

    virtual void update()
    {
      rs_->getObject(obj_)->rotateByDegrees(0,1,0,t_.getInterval());
    }

    virtual void display()
    {
      SEApplication<GLfloat>::display();
    }

    virtual void key(unsigned char key, int x, int y)
    {
        switch(key)
        {
        case '=':
        case '+':
            t_.setSpeedFactor(t_.speed * 1.1);
            break;
        case '-':
        case '_':
            t_.setSpeedFactor(t_.speed / 1.1);
            break;
        default:
            SEApplication<GLfloat>::key(key,x,y);
        }
    }
};

int main(int argc, char *argv[])
{
    SimpleEngine::startup(argc, argv);

    SimpleEngine::loadApp(new SETestApp1());

    SimpleEngine::runApp();

    SimpleEngine::quit();

    return EXIT_SUCCESS;
}
