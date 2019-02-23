#pragma once
#include <optional>

#include "def.h"

Color RayHit(Screen &, const Ray &,  double,int);

void render(Screen &);