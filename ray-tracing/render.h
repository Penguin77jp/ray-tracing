#pragma once
#include <optional>

#include "def.h"

std::optional<HitInfo> RayHit(Screen &, const Ray &,  double,int);

void render(Screen &);