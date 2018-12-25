#pragma once
#include <optional>

#include "def.h"

std::optional<HitInfo> RayHit(Screen &, Ray &);

void render(Screen &);