#define DEBUG_PORT Serial

#define DEBUG_LEVEL 10


#ifdef DEBUG_PORT
  #define DEBUG_BEGIN DEBUG_PORT.begin(9600)
#endif

#if 50 >= DEBUG_LEVEL_ && defined DEBUG_PORT 
  #define DEBUG_CRITICAL(...) DEBUG_PORT.printf_P( __VA_ARGS__ ); DEBUG_PORT.printf_P("\n"); 
#else
  #define DEBUG_CRITICAL(...)
#endif

#if 40 >= DEBUG_LEVEL_ && defined DEBUG_PORT
  #define DEBUG_ERROR(...) DEBUG_PORT.printf_P( __VA_ARGS__ ); DEBUG_PORT.printf_P("\n"); 
#else
  #define DEBUG_ERROR(...)
#endif

#if 30 >= DEBUG_LEVEL_ && defined DEBUG_PORT
  #define DEBUG_WARNING(...) DEBUG_PORT.printf_P( __VA_ARGS__ ); DEBUG_PORT.printf_P("\n");
#else
  #define DEBUG_WARNING(...)
#endif

#if 20 >= DEBUG_LEVEL_ && defined DEBUG_PORT
  #define DEBUG_INFO(...) DEBUG_PORT.printf_P( __VA_ARGS__ ); DEBUG_PORT.printf_P("\n"); 
#else
  #define DEBUG_INFO(...)
#endif

#if 10 >= DEBUG_LEVEL_ && defined DEBUG_PORT
  #define DEBUG_DEBUG(...) DEBUG_PORT.printf_P( __VA_ARGS__ ); DEBUG_PORT.printf_P("\n"); 
#else
  #define DEBUG_DEBUG(...)
#endif

#if 0 >= DEBUG_LEVEL_ && defined DEBUG_PORT
  #define DEBUG_NOSET(...) DEBUG_PORT.printf_P( __VA_ARGS__ ); DEBUG_PORT.printf_P("\n"); 
#else
  #define DEBUG_NOSET(...)
#endif