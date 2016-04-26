
#pragma once 
#include <structure/Point.h>

#define CLOCKWISE_FOR(VALUE) \
for(Point VALUE:{Point(0,1),Point(1,0),Point(0,-1),Point(-1,0)})

#define COUNTERCLOCKWISE_FOR(VALUE) \
for(Point VALUE:{Point(0,1),Point(-1,0),Point(0,-1),Point(1,0)})

#define CWFor  CLOCKWISE_FOR
#define CCWFor COUNTERCLOCKWISE_FOR


