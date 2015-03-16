#ifndef __SECONFIGURATIONLOADER_H__
#define __SECONFIGURATIONLOADER_H__

#include <string>
#include <map>

class SEConfigurationLoader 
{
      private:
             static const size_t MAX_STR_SIZE = 25;
              
      public:
             typedef union {
                       int          i;
                       float        f;
                       double       d;
                       char         s[MAX_STR_SIZE];
                       bool         b;
                   } SEConfigKey;
             
             typedef std::map<const std::string, SEConfigKey> tKeymap;

      private:
            tKeymap m_;
 
      public:
             
             SEConfigurationLoader() { loadDefaults(); }
             SEConfigurationLoader(const char *f) { load(f); }
             ~SEConfigurationLoader() {}
             
             void load(const char *f);
             void loadDefaults();
             
             int          getKeyi(std::string s)       { return (m_[s].i); }
             float        getKeyf(std::string s)       { return (m_[s].f); }
             double       getKeyd(std::string s)       { return (m_[s].d); }
             bool         getKeyb(std::string s)       { return (m_[s].b); }
             const char * getKeyc(std::string s)       { return (m_[s].s); }
             std::string  getKeys(std::string s)       { std::string ss(m_[s].s); return(ss); }
      
};

#endif
