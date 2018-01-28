/*
*********************************************************************
* File			: resource.h
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Resource.rc

// Next default values for new objects
// 

// define ETS2_R if compiling for ETS 2
//#define ETS2_R
// or define ATS_R if compiling for ATS
#define ATS_R

#define CURRENT_VERSION "1.2.0.0"
#define CURRENT_VERSION_SHORT 1200
#define CURRENT_VERSION_NUMBER 1,2,0,0

#ifdef ETS2_R
#define GAME_NAME "Euro Truck Simulator 2"
#define GAME_NAME_SHORT "ets2"
#define SUPPORTED_VERSION "1.27.xs and newer"
#elif defined(ATS_R)
#define GAME_NAME "American Truck Simulator"
#define GAME_NAME_SHORT "ats"
#define SUPPORTED_VERSION "1.6.xs and newer"
#endif

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
