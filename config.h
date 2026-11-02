#ifndef H_CONFIG
#define H_CONFIG

#define CONTROLLER_HDWF4

#ifdef CONTROLLER_HDWF4
#include <controller-hd-wf4.h>
#define controller_setup controllerWF4_setup
#define controller_syncTime controllerWF4_syncTime
#endif

#ifdef CONTROLLER_PORTALM4
#include <controller-portal-m4.h>
#define controller_setup controllerM4_setup
#define controller_syncTime controllerM4_syncTime
#endif

#endif