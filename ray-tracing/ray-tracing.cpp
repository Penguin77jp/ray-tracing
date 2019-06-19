#include "output.h"
#include "render.h"
#include "debug.h"
#include <Windows.h>
#include <tchar.h>
#include <string>
// #include "cpplinq/CppLinq/cpplinq.hpp"

int main()
{
	const int w = 1920 * 0.5;
	const int h = 1080 * 0.5;
	const double cameraDistance = 5;
	const V cameraRay_center = V();
	const V cameraRay_foward = V(0, 0, 1);
	const V cameraRay_up =  V(0, 1, 0);
	/*std::vector<Sphere> spheres = {
	Sphere( V(1e5 + 1, 40.8, 81.6),1e5, Color(),      Color(0.75, 0.25, 0.25)), // 左
	Sphere( V(-1e5 + 99, 40.8, 81.6),1e5,Color(),      Color(0.25, 0.25, 0.75)), // 右
	Sphere( V(50, 40.8, 1e5),1e5,     Color(),      Color(0.75, 0.75, 0.75)), // 奥
	Sphere(V(50, 40.8, -1e5 + 250),1e5,  Color(),      Color()), // 手前
	Sphere(V(50, 1e5, 81.6),1e5,       Color(),      Color(0.75, 0.75, 0.75)), // 床
	Sphere(V(50, -1e5 + 81.6, 81.6),1e5, Color(),      Color(0.75, 0.75, 0.75)), // 天井
	Sphere(V(65, 20, 20),20,           Color(),      Color(0.25, 0.75, 0.25)), // 緑球
	Sphere(V(27, 16.5, 47),16.5,       Color(),      Color(0.99, 0.99, 0.99)), // 鏡
	Sphere(V(77, 16.5, 78),16.5,       Color(),      Color(0.99, 0.99, 0.99)), //ガラス
	Sphere(V(50.0, 90.0, 81.6),15.0,   Color(36,36,36), Color()), //照明
	};*/
	std::vector<Sphere> spheres = { Sphere(V(0, 0, 5), 6, Color(0, 0, 255), Color(0, 0, 0)), Sphere(V(0, -300, 150), 100, Color(0, 0, 255), Color(255, 255, 255)) ,Sphere(V(300, 0, 150), 100, Color(0, 0, 255), Color(0, 255, 0)),
	Sphere(V(500, -300, 150), 100, Color(0, 0, 255), Color(0, 0, 0)) };
	Screen screen = Screen(w, h,cameraDistance, cameraRay_center,cameraRay_foward, cameraRay_up, spheres);
	render(screen);
	output(screen);
	//system("open result.ppm");
	LogColorful("Finished!", LogColor_enum::ErrorHighLight);
	return 0;
}