#ifndef __H_MY_DEBUG__
#define __H_MY_DEBUG__

#include <iostream>

#ifndef NDEBUG
#define DEBUG_MSG(str) do { std::cout << str; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#endif