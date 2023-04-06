#include "Config.h"

#if DEBUG == 1
#include <LibPrintf.h>
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif 

