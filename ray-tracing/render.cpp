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

std::optional<HitInfo> RayHit(Screen &getScreen, Ray &getRay,  double rayPower=1.0) {
	for (int s = 0; s < getScreen.spheres.size(); s++) {

		double dotA = Dot(getRay.d, getRay.d);
		double dotB = Dot(getRay.d, getScreen.spheres[s].p - getRay.o);
		double dotC = Dot(getScreen.spheres[s].p - getRay.o, getScreen.spheres[s].p - getRay.o) -
			std::pow(getScreen.spheres[s].r, 2);
		V Q1 = getRay.o + ((dotB - std::pow(std::pow(dotB, 2) - (dotA * dotC), 0.5)) / dotA * getRay.d);
		double root = std::pow(dotB, 2) - dotA * dotC;

		//Ä‹A’†~
		if (root < 0 || rayPower< 0.01) {
			return std::nullopt;
		}

		if (root >= 0) {
			HitInfo hit;
			hit.hitObject = getScreen.spheres[s];
			hit.position = Q1;
			hit.hitObjectNormal = Normalize(Q1 - getScreen.spheres[s].p);   
			hit.dot = Dot(hit.position, hit.hitObject.p) / Magnitude(hit.position) / Magnitude(hit.hitObject.p);
			//hit.ray = Ray(hit.position, Normalize(getRay.d) + hit.hitObjectNormal);
			auto hitRecursive = RayHit(getScreen , Ray(hit.position, Normalize(getRay.d) + hit.hitObjectNormal),rayPower*hit.dot);
			if (hitRecursive && hit.dot*hitRecursive.value().dot > 0.01) {
				if (hit.hitObject.emission.Power() > 0) {
					hit.color = hitRecursive.value().dot * hitRecursive.value().hitObject.emission;
				}
				else {
					hit.color = hitRecursive.value().color * hit.dot;
				}
			}
			else {
				//F‚Ì‰e‹¿‚ª‚²‚­‚í‚¸‚©‚Å‚ ‚é
				//‚ ‚é‚¢‚ÍAray‚ªÚG‚µ‚È‚©‚Á‚½
				hit.color = ColorPix(0,0,0);
			}
			return hit;
		}
	}
}