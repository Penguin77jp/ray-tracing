#include <vector>
#include <cmath>
#include <iostream>
#include <optional>
#include "def.h"
#include "render.h"


void render(Screen &getScreen) {
	std::vector<Ray> rays;
	for (int i = 0; i < getScreen.w * getScreen.h; i++) {
		double x = getScreen.GetWidth(i) - getScreen.w * 0.5;
		double y = getScreen.GetHigh(i) - getScreen.h * 0.5;

		rays.push_back(Ray(getScreen.cameraRay.o, getScreen.cameraRay.d + V(x * 0.01, y * 0.01, 0)));
	}
	int parsentRenderringKeep = 0;
	for (int i = 0; i < rays.size(); i++) {
		double parsentRenderring = (double)i / (double)rays.size()*10.0;
		std::cout << i << std::endl;
		if (parsentRenderringKeep != (int)parsentRenderring) {
			std::cout << parsentRenderring << std::endl;
			//std::cout << "Rendering:" << (float)i / rays.size()*100.0 << "%" << std::endl;
			parsentRenderringKeep = parsentRenderring;
		}
			auto info = RayHit(getScreen, rays[i]);
			if (info && info.value().dot > 0) {
				//std::cout << info.value().dot << std::endl;
				getScreen.colors[i] = getScreen.spheres[0].color * info.value().dot;
				//rays.push_back(Ray(info.value().position, info.value().position - info.value().hitObject.p));
			}
	}
}

std::optional<HitInfo> RayHit(Screen &getScreen, Ray &getRay) {
	for (int s = 0; s < getScreen.spheres.size(); s++) {

		double dotA = Dot(getRay.d, getRay.d);
		double dotB = Dot(getRay.d, getScreen.spheres[s].p - getRay.o);
		double dotC = Dot(getScreen.spheres[s].p - getRay.o, getScreen.spheres[s].p - getRay.o) -
			std::pow(getScreen.spheres[s].r, 2);
		V Q1 = getRay.o + ((dotB - std::pow(std::pow(dotB, 2) - (dotA * dotC), 0.5)) / dotA * getRay.d);
		double root = std::pow(dotB, 2) - dotA * dotC;
		if (root >= 0) {
			HitInfo hit;
			hit.hitObject = getScreen.spheres[s];
			hit.position = Q1;
			hit.hitObjectNormal = Q1 - getScreen.spheres[s].p;
			hit.dot = Dot(hit.position, hit.hitObject.p) / Magnitude(hit.position) / Magnitude(hit.hitObject.p);
			return hit;
		}
		else {
			return std::nullopt;
		}
	}
}