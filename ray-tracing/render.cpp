#include <vector>
#include <cmath>
#include <iostream>
#include <optional>
#include <time.h>
#include "def.h"
#include "render.h"


void render(Screen &getScreen) {
	std::vector<Ray> rays;
	for (int i = 0; i < getScreen.w * getScreen.h; i++) {
		double x = getScreen.GetWidth(i) - getScreen.w * 0.5;
		double y = getScreen.GetHigh(i) - getScreen.h * 0.5;

		rays.push_back(Ray(getScreen.cameraRay.o, getScreen.cameraRay.d + V(x * getScreen.pov, y * getScreen.pov, 0)));
	}
	int _clockKeep = clock()*0.001;//msc -> sc
	for (int i = 0; i < rays.size(); i++) {
		double _clock = clock();
		if (_clockKeep != (int)(_clock*0.001)) {
			std::cout << "Rendering:" << (float)i / rays.size()*100.0 << "%" << std::endl;
			_clockKeep = clock()*0.001;
		}
		auto info = RayHit(getScreen, rays[i], 1.0);
			if (info) {
				getScreen.colors[i] = ColorPix(255,255,255);
			}
			//if (info && info.value().dot > 0) {
				//getScreen.colors[i] = info.value().color;
			//}
	}
}

std::optional<HitInfo> RayHit(Screen &getScreen, const Ray &getRay,  double rayPower) {
	for (int s = 0; s < getScreen.spheres.size(); s++) {
		double dotA = Dot(getRay.d, getRay.d);
		double dotB = Dot(getRay.d, getScreen.spheres[s].p - getRay.o);
		double dotC = Dot(getScreen.spheres[s].p - getRay.o, getScreen.spheres[s].p - getRay.o) -
			std::pow(getScreen.spheres[s].r, 2);
		V Q1 = getRay.o + ((dotB - std::pow(std::pow(dotB, 2) - (dotA * dotC), 0.5)) / dotA * getRay.d);
		double root = std::pow(dotB, 2) - dotA * dotC;

		//再帰中止
		if (rayPower< 0.01) {
			return std::nullopt;
		}
		//別のオブジェをチェック
		if (root < 0) {
			continue;
		}

		if (root >= 0) {
			HitInfo hit;
			return hit;
			hit.hitObject = getScreen.spheres[s];
			hit.position = Q1;
			hit.hitObjectNormal = Normalize(Q1 - getScreen.spheres[s].p);   
			hit.dot = Dot(hit.position, hit.hitObject.p) / Magnitude(hit.position) / Magnitude(hit.hitObject.p);
			//hit.ray = Ray(hit.position, Normalize(getRay.d) + hit.hitObjectNormal);
			auto hitRecursive = RayHit(getScreen , Ray(hit.position, Normalize(getRay.d) + hit.hitObjectNormal),rayPower*hit.dot);
			if (hitRecursive && hit.dot*hitRecursive.value().dot > 0.01) {
				if (hitRecursive.value().hitObject.emission.Power() > 0) {
					hit.color = hitRecursive.value().dot * hitRecursive.value().hitObject.emission;
				}
				else {
					hit.color = hitRecursive.value().color * hit.dot;
				}
			}
			else {
				//色の影響がごくわずかである
				//あるいは、rayが接触しなかった
				hit.color = ColorPix(0,0,0);
			}
			return hit;
		}
	}
	//結果衝突を検出出来なかった
	return std::nullopt;
}