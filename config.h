#ifndef H_CONFIG
#define H_CONFIG

#define CONTROLLER_HDWF4

#ifdef CONTROLLER_HDWF4
#include <controller-hd-wf4.h>
// TODO: fix this config stuff
#define matrix matrixWF4
#define controller_setup controllerWF4_setup
#define controller_syncTime controllerWF4_syncTime
#define controller_getTime controllerWF4_getTime
#define controller_hasTime controllerWF4_hasTime
#endif

#ifdef CONTROLLER_PORTALM4
#include <controller-portal-m4.h>
// TODO: fix this config stuff
#define matrix matrixM4
#define controller_setup controllerM4_setup
#define controller_syncTime controllerM4_syncTime
#define controller_getTime controllerM4_getTime
#define controller_hasTime controllerM4_hasTime
#endif

#endif