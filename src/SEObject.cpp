#include <sstream>
#include "../inc/SEObject.h"

uint32_t               SEObjectName::nextAutoIndex = 0x00000000;

SEObjectName::tNameSet SEObjectName::nameSet(SEObjectName::newNameSet());
SEObject::tObjectMap   SEObject::objectMap(SEObject::newObjectMap());

uint32_t SEObjectName::nameToCode(const std::string &n, uint32_t seed)
{
  uint32_t h = seed;

  for (int i=0;i<n.length();++i)
    h=h*101 + n[i];

  return h;
}

void SEObjectName::setName(const std::string &s)
{
  if (nameInUse(s))
    setAutoName();
  else
  {
    n_ = s;
    c_ = nameToCode(n_);
  }
}

void SEObjectName::setAutoName()
{
  n_ = getNextAutoName();
  c_ = nameToCode(n_);
}

std::string SEObjectName::getNextAutoName()
{
    std::ostringstream s, t;

    t.setf(std::ios_base::hex, std::ios_base::basefield);
    t.fill('0');
    t.width(8);

    t << nextAutoIndex;
    s << "SEObj_" << t.str();

    std::string r = s.str();

    do {
      ++nextAutoIndex;
      t << nextAutoIndex;
      s << "SEObj_" << t.str();
    } while (nameInUse(s.str()));

    return(r);
}
