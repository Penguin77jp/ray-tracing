#pragma once
#include <optional>

#include "def.h"

std::optional<HitInfo> RayHit(Screen &, const Ray &,  double);

void render(Screen &);