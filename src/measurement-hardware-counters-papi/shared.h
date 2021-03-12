#include <papi.h>

#define quote(num) requote(num)
#define requote(num) #num

#define checked(code) do { if ((code) != PAPI_OK) { PAPI_perror (__FILE__ ":" quote (__LINE__)); exit (1); }} while (0)
