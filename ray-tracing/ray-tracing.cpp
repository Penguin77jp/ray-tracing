#include "output.h"
#include "render.h"
// #include "cpplinq/CppLinq/cpplinq.hpp"

int main()
{
	const int w = 80;
	const int h = 48;
	Ray cameraRay = Ray(V(), V(0, 0, 1));
	std::vector<Sphere> spheres = { Sphere(V(0, 0, 150), 100, ColorPix(0, 0, 255), ColorPix(0, 0, 0)), Sphere(V(0, 200, 150), 100, ColorPix(0, 0, 255), ColorPix(255, 255, 255)) };
	Screen screen = Screen(w, h, cameraRay, spheres);
	render(screen);
	output(&screen);
	//    system("open result.ppm");
	return 0;
}