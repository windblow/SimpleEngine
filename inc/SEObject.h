#ifndef __SEOBJECT_H__
#define __SEOBJECT_H__

#include <string>
#include <set>
#include <map>

class SEObjectName {
  public:
    typedef std::set<std::string>  tNameSet;

    const   std::string &str;
    const   uint32_t    &code;

                         SEObjectName()                     : str(n_), code(c_) { setAutoName(); }
                         SEObjectName(const std::string &s) : str(n_), code(c_) { setName(s); }
                        ~SEObjectName()                                         { freeName(n_); }

    static  bool         nameInUse(const std::string &n) { if (nameSet.count(n) > 0) return true; else return false; }
    static  uint32_t     nameToCode(const std::string &n, uint32_t seed=0);

  private:
            void         setName(const std::string &s);
            void         setAutoName();

            std::string  n_;
            uint32_t     c_;

    static  tNameSet     nameSet;
    static  uint32_t     nextAutoIndex;

    static  tNameSet     newNameSet() { tNameSet s; return s; } // inicializador estático do set

    static  std::string  getNextAutoName();
    static  void         freeName(const std::string &n) { nameSet.erase(n); }
};

class SEObject {
  public:
    typedef std::map<uint32_t, SEObject*> tObjectMap;

    const  SEObjectName &name;

    const  SEObject     *getConstPtr() const { return const_cast<SEObject*>(this); }
           SEObject     *getPtr() { return (this); }

  protected:
                         SEObject()                     : name_(),  name(name_) { registerObject(this); }
                         SEObject(const std::string &n) : name_(n), name(name_) { registerObject(this); }
                        ~SEObject()                                             { unregisterObject(getConstPtr()); }

    static void          registerObject(SEObject* o)   { objectMap[o->name.code] = o; }
    static void          unregisterObject(const SEObject* o) { objectMap.erase(o->name.code); }

    static SEObject     *getObjectByName(const std::string &n) { if (objectExists(n)) return objectMap[SEObjectName::nameToCode(n)]; else return(NULL); }
    static SEObject     *getObjectByCode(uint32_t c)           { if (objectExists(c)) return objectMap[c]; else return (NULL); }

    static bool          objectExists(const std::string &n) { return (SEObjectName::nameInUse(n)); }
    static bool          objectExists(uint32_t c)           { return (objectMap.count(c) > 0); }

    static int           activeObjectCount() { return objectMap.size(); }

  private:
           SEObjectName  name_;

    static tObjectMap objectMap;
    static tObjectMap newObjectMap() { tObjectMap m; return m; } // inicializador estático do map


};

#endif
