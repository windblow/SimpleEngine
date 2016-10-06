#ifndef __SEDEBUGTOOLS_H__
#define __SEDEBUGTOOLS_H__

// Definições de macros exclusivas para build de debug.
#ifdef SEDEBUG
  #define DUMPONCE(x) if (dumpOnce) std::cout << x << std::endl
  #define DUMPFLAG(x) dumpOnce = x
  #define USEDUMPFLAG extern bool dumpOnce
  #define SYSTEMPAUSE system("PAUSE")
#else
  #define DUMPONCE(x)
  #define DUMPFLAG(x)
  #define USEDUMPFLAG
  #define SYSTEMPAUSE
#endif



#endif // __SEDEBUGTOOLS_H__
