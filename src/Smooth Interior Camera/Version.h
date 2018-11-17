#pragma once

#define CURRENT_VERSION "1.2.1.0"
#define CURRENT_VERSION_SHORT 1210
#define CURRENT_VERSION_NUMBER 1,2,1,0

// Hook Version
// #define HOOK_V1 // for ETS2 1.27 - 1.32 and ATS 1.6+
#define HOOK_V2 // for ETS 1.33+
// ...

#ifdef ETS2
#define GAME_NAME "Euro Truck Simulator 2"
#define GAME_NAME_SHORT "ets2"
#elif defined(ATS)
#define GAME_NAME "American Truck Simulator"
#define GAME_NAME_SHORT "ats"
#endif
