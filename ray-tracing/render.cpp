#include <vector>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <optional>
#include <time.h>

#include "def.h"
#include "render.h"
#include "debug.h"
#include "output.h"

#define _DEGREE_DETAIL 0.01

void render(Screen &getScreen) {
	LogColorful("Start redering", LogColor_enum::Error);
	std::vector<Ray> rays;
	for (int i = 0; i < getScreen.w * getScreen.h; i++) {
		double x = getScreen.GetWidth(i) - getScreen.w * 0.5;
		double y = getScreen.GetHigh(i) - getScreen.h * 0.5;

		rays.push_back(Ray(getScreen.cameraRay.o, getScreen.cameraRay.d + V(x * getScreen.pov, y * getScreen.pov, 0)));
	}
	int _clockKeep = clock()*0.001;//msc -> sc
	for (int i = 0; i < rays.size(); i++) {
		if (_clockKeep != (int)(clock()*0.001)) {
			std::cout << "Rendering:" << (float)i / rays.size()*100.0 << "%" << std::endl;
			_clockKeep = clock()*0.001;
		}
		auto info = RayHit(getScreen, rays[i], 1.0,0);
		if (info) {
			getScreen.colors[i] = info.value().color;
		}
	}
}

std::optional<HitInfo> RayHit(Screen &getScreen, const Ray &getRay, double rayPower,int depth) {
	//再帰中止
	if (rayPower < 0.01 || depth >= 64) {
		return std::nullopt;
	}

	for (int s = 0; s < getScreen.spheres.size(); s++) {
		double dotA = Dot(getRay.d, getRay.d);
		double dotB = -2 * Dot(getRay.d, getScreen.spheres[s].p - getRay.o);
		double dotC = Dot(getScreen.spheres[s].p - getRay.o, getScreen.spheres[s].p - getRay.o) - std::pow(getScreen.spheres[s].r, 2);
		double D_4 = (std::pow(dotB, 2) - 4 * dotA*dotC) / 4;
		double t1 = (-dotB / 2 + std::pow(D_4, 0.5)) / dotA;
		double t2 = (-dotB / 2 - std::pow(D_4, 0.5)) / dotA;
		if (t1 >= DBL_EPSILON) {
			for (double deg1 = 0; deg1 <= 2 * M_PI; deg1 += _DEGREE_DETAIL) {
				for (double deg2 = -M_PI; deg2 <= M_PI ; deg2 += _DEGREE_DETAIL) {
			//for (double deg1 = 0; deg1 <= 2 * M_PI; deg1 += _DEGREE_DETAIL) {
				//for (double deg2 = deg1 == 0 ? -M_PI : M_PI + _DEGREE_DETAIL; deg2 <= deg1 == 0 ? M_PI : M_PI - _DEGREE_DETAIL; deg2 += _DEGREE_DETAIL) {
					V Q1 = V(getRay.o + t1 * getRay.d);
					HitInfo hit;
					hit.hitObject = getScreen.spheres[s];
					hit.position = Q1;
					hit.hitObjectNormal = Normalize(Q1 - getScreen.spheres[s].p);
					hit.dot = Dot(hit.position, hit.hitObject.p) / Magnitude(hit.position) / Magnitude(hit.hitObject.p);
					hit.ray = Ray(hit.position, Normalize(getRay.d) + hit.hitObjectNormal);
					V diffusionRay_direction = Normalize(V(std::cos(deg1)*std::sin(deg2), std::sin(deg1)*std::sin(deg2), std::cos(deg2)));
					auto dot = Dot(hit.hitObjectNormal,diffusionRay_direction);
					//貫通レイはなし(後々、ガラスで使う)
					if (dot < 0) {
						continue;
					}
					//光源の場合、直ちに光を反映
					if (hit.hitObject.emission.Power() > 0) {
						hit.color = hit.dot* hit.hitObject.emission;
						return hit;
					}
					//std::cout << V2string(Normalize(getRay.d + diffusionRay_direction)) << std::endl;
					auto hitRecursive = RayHit(getScreen, Ray(hit.position, Normalize(getRay.d+diffusionRay_direction)), rayPower*hit.dot,depth+1);
					if (hitRecursive) {
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
						hit.color = Color(0, 0, 0);
					}
					return hit;
				}
			}
		}
	}
	//結果衝突を検出出来なかった
	return std::nullopt;
}