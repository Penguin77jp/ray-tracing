#pragma once
#include <optional>

#include "def.h"

Color RayHit(Screen &, const Ray &,int);

void render(Screen &);