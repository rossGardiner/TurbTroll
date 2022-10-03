#define DEBUG 1

#if DEBUG == 1
#include <LibPrintf.h>
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif 

