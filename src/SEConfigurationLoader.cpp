#include "../inc/SEConfigurationLoader.h"
#include "../inc/json.h"

#include <fstream>

void SEConfigurationLoader::load( const char *f )
{
  
     loadDefaults(); // Carrega configurações padrão ANTES de ler do arquivo,
                     // assim valores omitidos do arquivo serão inicializados.

     std::ifstream f_(f, std::ifstream::in);

     if (f_.good())
     {
         std::string s = "";
         
         char c = f_.get();
         while (f_.good())
         {
             s += c;
             c = f_.get();
         }
         
         json::Value conf = json::Deserialize(s);
         
         if (conf.GetType() == json::ObjectVal)
         {
             json::Object o = conf.ToObject(); // É necessario chamar ToObject uma única vez e buscar os iteradores do resultado.
                                               // A tentativa de usar conf.ToObject().begin() e conf.ToObject().end() dentro do for
                                               // estava gerando vazamento de memória.
            
             for (json::Object::ValueMap::const_iterator it = o.begin(); it != o.end(); it++)
             {
                 switch (it->second.GetType())
                 {
                     case json::StringVal    :    strncpy(m_[it->first].s, (char *)it->second.ToString().c_str(), MAX_STR_SIZE); break;
                     case json::IntVal       :    m_[it->first].i =    (int)it->second.ToInt(); break;
                     case json::FloatVal     :    m_[it->first].f =  (float)it->second.ToFloat(); break;
                     case json::DoubleVal    :    m_[it->first].d = (double)it->second.ToDouble(); break;
                     case json::BoolVal      :    m_[it->first].b =   (bool)it->second.ToBool(); break;
                     default                 :    break;
                 }
             }
         }
     }

     f_.close();
}

void SEConfigurationLoader::loadDefaults()
{
     // Jogar valores padrão no mapa
     m_["iTestValueA"].i = 10;
     m_["dTestValueB"].d = 20.14;
     strcpy(m_["cTestValueC"].s, "teste");
}

